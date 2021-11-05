#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>
#include <QAbstractVideoFilter>
#include <QQmlContext>
#include <QFileInfo>
#include <QImage>
#include <QAbstractVideoBuffer>
#include <QDateTime>
#include <QCamera>
#include "include/DynamsoftCommon.h"
#include "include/DynamsoftBarcodeReader.h"

class QRCodeFilter : public QAbstractVideoFilter
{
    Q_OBJECT

public:
    QVideoFilterRunnable *createFilterRunnable() override;

signals:
    void finished(QObject *result);

private:
    friend class QRCodeFilterRunnable;
};

class QRCodeFilterRunnable : public QVideoFilterRunnable
{
public:
    QRCodeFilterRunnable(QRCodeFilter *filter) : m_filter(filter)
    {
        reader = DBR_CreateInstance();
        char errorMessage[256];
        PublicRuntimeSettings settings;
        DBR_GetRuntimeSettings(reader, &settings);
        //        settings.deblurLevel = 0;
        //        settings.timeout = 50;
        //        settings.expectedBarcodesCount = 1;
//        settings.barcodeFormatIds = BF_QR_CODE;
        DBR_UpdateRuntimeSettings(reader, &settings, errorMessage, 256);
        // Get a trial license from https://www.dynamsoft.com/customer/license/trialLicense?product=dbr
        DBR_InitLicense(reader, "LICENSE-KEY");
    }
    ~QRCodeFilterRunnable() {DBR_DestroyInstance(reader);}
    QVideoFrame run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags) override;

private:
    QRCodeFilter *m_filter;
    void *reader;
};

class QRCodeFilterResult : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ text)

public:
    QString text() const { return m_text; }

private:
    QString m_text;
    friend class QRCodeFilterRunnable;
};

QVideoFilterRunnable *QRCodeFilter::createFilterRunnable()
{
    return new QRCodeFilterRunnable(this);
}

QVideoFrame QRCodeFilterRunnable::run(QVideoFrame *input, const QVideoSurfaceFormat &surfaceFormat, RunFlags flags)
{
    Q_UNUSED(surfaceFormat);
    Q_UNUSED(flags);
    QRCodeFilterResult *result = new QRCodeFilterResult;

    //    if (input->pixelFormat() == QVideoFrame::Format_YUYV)
    //    {
    //        qDebug() << "Format_YUYV";
    //    }

    //    if (input->pixelFormat() == QVideoFrame::Format_BGR32)
    //    {
    //        qDebug() << "Format_BGR32";
    //    }

    //    if (input->pixelFormat() == QVideoFrame::Format_NV21)
    //    {
    //        qDebug() << "Format_NV21";
    //    }

    // Decode QR code
    input->map(QAbstractVideoBuffer::ReadOnly);

    int width = input->width();
    int height = input->height();
    int total = width * height;

#ifdef Q_OS_ANDROID
    // Android
    QDateTime start = QDateTime::currentDateTime();
    int ret = DBR_DecodeBuffer(reader, input->bits(), width, height, input->bytesPerLine(), IPF_ABGR_8888, "");
    QDateTime end = QDateTime::currentDateTime();
#else
    // Windows
    unsigned char* origin = (unsigned char *)input->bits();
    unsigned char* grayscale = new unsigned char[total];
    for (int i = 0; i < total; i++)
    {
        grayscale[i] = origin[i * 2];
    }
    QDateTime start = QDateTime::currentDateTime();
    int ret = DBR_DecodeBuffer(reader, grayscale, width, height, width, IPF_GRAYSCALED, "");
    QDateTime end = QDateTime::currentDateTime();
    delete[] grayscale;
#endif


    // Debug info
    // QString out = QString::number(input->width()) + ", bytesperline: " + QString::number(input->bytesPerLine()) + ", " + QString::number(ret) + ", color format: " + QString::number(input->pixelFormat());
    QString out = "";
    input->unmap();
    TextResultArray *handler = NULL;
    DBR_GetAllTextResults(reader, &handler);
    TextResult **results = handler->results;
    int count = handler->resultsCount;

    for (int index = 0; index < count; index++)
    {
        //        LocalizationResult* localizationResult = results[index]->localizationResult;
        out += "Index: " + QString::number(index) + ", Elapsed time: " + QString::number(start.msecsTo(end)) + "ms\n";
        out += "Barcode format: " + QLatin1String(results[index]->barcodeFormatString) + "\n";
        out += "Barcode value: " + QLatin1String(results[index]->barcodeText) + "\n";
        //                            out += "Bounding box: (" + QString::number(localizationResult->x1) + ", " + QString::number(localizationResult->y1) + ") "
        //                            + "(" + QString::number(localizationResult->x2) + ", " + QString::number(localizationResult->y2) + ") "
        //                            + "(" + QString::number(localizationResult->x3) + ", " + QString::number(localizationResult->y3) + ") "
        //                            + "(" + QString::number(localizationResult->x4) + ", " + QString::number(localizationResult->y4) + ")\n";
        out += "----------------------------------------------------------------------------------------\n";

    }
    DBR_FreeTextResults(&handler);

    result->m_text = out;
    emit m_filter->finished(result);

    return *input;
}

int main(int argc, char* argv[])
{
    QGuiApplication app(argc,argv);
    qmlRegisterType<QRCodeFilter>("com.dynamsoft.barcode", 1, 0, "QRCodeFilter");
    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);
    QObject::connect(view.engine(), &QQmlEngine::quit,
                     qApp, &QGuiApplication::quit);
    view.setSource(QUrl("qrc:///main.qml"));

    // https://doc.qt.io/qt-5/qtglobal.html#Q_OS_ANDROID
#ifdef Q_OS_ANDROID
    QObject *qmlCamera = view.findChild<QObject*>("qrcamera");
    // https://doc.qt.io/qt-5/qml-qtmultimedia-camera.html#viewfinder-prop
    QCamera *camera = qvariant_cast<QCamera *>(qmlCamera->property("mediaObject"));
    // https://doc.qt.io/archives/qt-5.9/qcameraviewfindersettings.html
    QCameraViewfinderSettings viewfinderSettings = camera->viewfinderSettings();
    viewfinderSettings.setResolution(640, 480);
    viewfinderSettings.setMinimumFrameRate(15.0);
    viewfinderSettings.setMaximumFrameRate(30.0);
    //        viewfinderSettings.setPixelFormat(QVideoFrame::Format_NV21); // cannot work
    camera->setViewfinderSettings(viewfinderSettings);
#endif
    view.resize(1280, 720);
    view.show();
    return app.exec();
}

#include "main.moc"
