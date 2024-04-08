#include "ImageProcessor.h"
#ifdef Q_OS_IOS
#include "libs/ios/framework/bridge.h"
#else
#include "DynamsoftBarcodeReader.h"
#endif

#include <QImage>

ImageProcessor::ImageProcessor(QObject *parent) : QObject(parent)
{
    reader = DBR_CreateInstance();

    char errorMessage[512];
    DBR_InitRuntimeSettingsWithString(reader, "{\"Version\":\"3.0\", \"ImageParameter\":{\"Name\":\"IP1\", \"BarcodeFormatIds\":[\"BF_ALL\"], \"ExpectedBarcodesCount\":10}}", CM_OVERWRITE, errorMessage, 512);
}

ImageProcessor::~ImageProcessor()
{
    if (reader) DBR_DestroyInstance(reader);
}

void ImageProcessor::processImage(const QImage &image)
{
    if (!reader) return;

    QString out = "";
    if (!image.isNull())
    {
        int width = image.width();
        int height = image.height();

        int bytesPerLine = image.bytesPerLine();

        const uchar *pixelData = image.constBits();
        int ret = 0;

        if (image.format() == QImage::Format_RGBA8888_Premultiplied || image.format() == QImage::Format_RGBA8888)
        {
            ret = DBR_DecodeBuffer(reader, pixelData, width, height, bytesPerLine, IPF_ABGR_8888, "");
        }
    }

    TextResultArray *handler = NULL;
    DBR_GetAllTextResults(reader, &handler);
    TextResult **results = handler->results;
    int count = handler->resultsCount;

    for (int index = 0; index < count; index++)
    {
        //        LocalizationResult* localizationResult = results[index]->localizationResult;
        out += "Index: " + QString::number(index)  + "\n";
        out += "Barcode format: " + QLatin1String(results[index]->barcodeFormatString) + "\n";
        out += "Barcode value: " + QLatin1String(results[index]->barcodeText) + "\n";
        //                            out += "Bounding box: (" + QString::number(localizationResult->x1) + ", " + QString::number(localizationResult->y1) + ") "
        //                            + "(" + QString::number(localizationResult->x2) + ", " + QString::number(localizationResult->y2) + ") "
        //                            + "(" + QString::number(localizationResult->x3) + ", " + QString::number(localizationResult->y3) + ") "
        //                            + "(" + QString::number(localizationResult->x4) + ", " + QString::number(localizationResult->y4) + ")\n";
        out += "----------------------------------------------------------------------------------------\n";
    }
    DBR_FreeTextResults(&handler);

    emit imageProcessed(out);
}
