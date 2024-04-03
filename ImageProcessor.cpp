#include "ImageProcessor.h"
#include "DynamsoftBarcodeReader.h"
#include <QImage>

ImageProcessor::ImageProcessor(QObject *parent) : QObject(parent)
{
    // reader = NULL;
    reader = DBR_CreateInstance();

    char errorMessage[256];
    PublicRuntimeSettings settings;
    DBR_GetRuntimeSettings(reader, &settings);
    //        settings.deblurLevel = 0;
    //        settings.timeout = 50;
    // settings.expectedBarcodesCount = 999;
    //        settings.barcodeFormatIds = BF_QR_CODE;
    DBR_UpdateRuntimeSettings(reader, &settings, errorMessage, 256);
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
