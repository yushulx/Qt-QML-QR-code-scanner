// FrameProcessor.cpp

#include "FrameProcessor.h"
#include <QDebug>
#include <QThread>

#include "DynamsoftBarcodeReader.h"

FrameProcessor::FrameProcessor(QObject *parent) : QObject(parent)
{
    m_isAvailable = true;
    char errorMsgBuffer[512];
    // Click https://www.dynamsoft.com/customer/license/trialLicense/?product=dbr to get a trial license.
    DBR_InitLicense("DLS2eyJoYW5kc2hha2VDb2RlIjoiMjAwMDAxLTE2NDk4Mjk3OTI2MzUiLCJvcmdhbml6YXRpb25JRCI6IjIwMDAwMSIsInNlc3Npb25QYXNzd29yZCI6IndTcGR6Vm05WDJrcEQ5YUoifQ==", errorMsgBuffer, 512);
    printf("DBR_InitLicense: %s\n", errorMsgBuffer);

    const char *version = DBR_GetVersion();
    m_displayString = QString(version);

    ImageProcessor *processor = new ImageProcessor();
    QThread *workerThread = new QThread();

    processor->moveToThread(workerThread);
    connect(workerThread, &QThread::finished, processor, &QObject::deleteLater);
    connect(this, &FrameProcessor::newFrameAvailable, processor, &ImageProcessor::processImage);
    connect(processor, &ImageProcessor::imageProcessed, this, &FrameProcessor::onImageProcessed);
    workerThread->start();
}

FrameProcessor::~FrameProcessor()
{
    // workerThread->quit();
    // workerThread->wait();
    delete workerThread;
}

QVideoSink *FrameProcessor::videoSink() const
{
    return m_videoSink;
}

void FrameProcessor::setVideoSink(QVideoSink *sink)
{
    if (m_videoSink != sink)
    {
        m_videoSink = sink;
        connect(m_videoSink, &QVideoSink::videoFrameChanged, this, &FrameProcessor::processFrame);
    }
}

void FrameProcessor::processFrame(const QVideoFrame &frame)
{
    if (!frame.isValid() || !m_isAvailable)
        return;

    m_isAvailable = false;
    QImage image = frame.toImage();
    emit newFrameAvailable(image);
}

QString FrameProcessor::displayString() const
{
    return m_displayString;
}

void FrameProcessor::onImageProcessed(const QString &out) {
    emit barcodeDetected(out);
    m_isAvailable = true;
}
