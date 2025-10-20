#include "ImageProcessor.h"
#ifdef Q_OS_IOS
#include "libs/ios/framework/bridge.h"
#else
#include "DynamsoftBarcodeReader.h"
#endif

#include <QImage>

#include <string>
#include <chrono>

const std::string kJson = R"JSON(
{
  "FormatSpecificationArray": [
    {
      "AllModuleDeviation": 0,
      "AustralianPostEncodingTable": "C",
      "BarcodeAngleRangeArray": null,
      "BarcodeBytesLengthRangeArray": [
        {
          "MaxValue": 2147483647,
          "MinValue": 0
        }
      ],
      "BarcodeBytesRegExPattern": "",
      "BarcodeComplementModes": null,
      "BarcodeFormatIds": [
        "BF_DATAMATRIX"
      ],
      "BarcodeFormatIds_2": [
        "BF2_NULL"
      ],
      "BarcodeHeightRangeArray": null,
      "BarcodeTextLengthRangeArray": [
        {
          "MaxValue": 2147483647,
          "MinValue": 0
        }
      ],
      "BarcodeTextRegExPattern": "",
      "BarcodeWidthRangeArray": null,
      "BarcodeZoneBarCountRangeArray": null,
      "BarcodeZoneMinDistanceToImageBorders": 0,
      "Code128Subset": "",
      "DeblurLevel": 9,
      "DeformationResistingModes": null,
      "EnableDataMatrixECC000-140": 1,
      "EnableQRCodeModel1": 0,
      "FindUnevenModuleBarcode": 1,
      "HeadModuleRatio": "",
      "MSICodeCheckDigitCalculation": "MSICCDC_MOD_10",
      "MinQuietZoneWidth": 4,
      "MinRatioOfBarcodeZoneWidthToHeight": 0,
      "MinResultConfidence": 30,
      "MirrorMode": "MM_BOTH",
      "ModuleSizeRangeArray": null,
      "Name": "IP1_BF_DATAMATRIX",
      "PartitionModes": [
        "PM_WHOLE_BARCODE",
        "PM_ALIGNMENT_PARTITION"
      ],
      "PatchCodeSearchingMargins": {
        "Bottom": 20,
        "Left": 20,
        "MeasuredByPercentage": 1,
        "Right": 20,
        "Top": 20
      },
      "RequireStartStopChars": 1,
      "ReturnPartialBarcodeValue": 1,
      "StandardFormat": "",
      "TailModuleRatio": "",
      "VerifyCheckDigit": 0
    },
    {
      "AllModuleDeviation": 0,
      "AustralianPostEncodingTable": "C",
      "BarcodeAngleRangeArray": null,
      "BarcodeBytesLengthRangeArray": [
        {
          "MaxValue": 2147483647,
          "MinValue": 0
        }
      ],
      "BarcodeBytesRegExPattern": "",
      "BarcodeComplementModes": null,
      "BarcodeFormatIds": [
        "BF_ALL"
      ],
      "BarcodeFormatIds_2": [
        "BF2_ALL"
      ],
      "BarcodeHeightRangeArray": null,
      "BarcodeTextLengthRangeArray": [
        {
          "MaxValue": 2147483647,
          "MinValue": 0
        }
      ],
      "BarcodeTextRegExPattern": "",
      "BarcodeWidthRangeArray": null,
      "BarcodeZoneBarCountRangeArray": null,
      "BarcodeZoneMinDistanceToImageBorders": 0,
      "Code128Subset": "",
      "DeblurLevel": 9,
      "DeformationResistingModes": null,
      "EnableDataMatrixECC000-140": 0,
      "EnableQRCodeModel1": 0,
      "FindUnevenModuleBarcode": 1,
      "HeadModuleRatio": "",
      "MSICodeCheckDigitCalculation": "MSICCDC_MOD_10",
      "MinQuietZoneWidth": 4,
      "MinRatioOfBarcodeZoneWidthToHeight": 0,
      "MinResultConfidence": 30,
      "MirrorMode": "MM_NORMAL",
      "ModuleSizeRangeArray": null,
      "Name": "defaultFormatParameterForAllBarcodeFormat",
      "PartitionModes": [
        "PM_WHOLE_BARCODE",
        "PM_ALIGNMENT_PARTITION"
      ],
      "PatchCodeSearchingMargins": {
        "Bottom": 20,
        "Left": 20,
        "MeasuredByPercentage": 1,
        "Right": 20,
        "Top": 20
      },
      "RequireStartStopChars": 1,
      "ReturnPartialBarcodeValue": 1,
      "StandardFormat": "",
      "TailModuleRatio": "",
      "VerifyCheckDigit": 0
    }
  ],
  "ImageParameter": {
    "BarcodeColourModes": [
      {
        "LibraryFileName": "",
        "LibraryParameters": "",
        "LightReflection": 1,
        "Mode": "BICM_DARK_ON_LIGHT"
      }
    ],
    "BarcodeComplementModes": [
      {
        "Mode": "BCM_SKIP"
      }
    ],
    "BarcodeFormatIds": [
      "BF_DATAMATRIX"
    ],
    "BarcodeFormatIds_2": [
      "BF2_NULL"
    ],
    "BinarizationModes": [
      {
        "BlockSizeX": 0,
        "BlockSizeY": 0,
        "EnableFillBinaryVacancy": 1,
        "ImagePreprocessingModesIndex": -1,
        "LibraryFileName": "",
        "LibraryParameters": "",
        "Mode": "BM_LOCAL_BLOCK",
        "ThresholdCompensation": 10
      },
      {
        "BlockSizeX": 0,
        "BlockSizeY": 0,
        "EnableFillBinaryVacancy": 0,
        "ImagePreprocessingModesIndex": -1,
        "LibraryFileName": "",
        "LibraryParameters": "",
        "Mode": "BM_LOCAL_BLOCK",
        "ThresholdCompensation": 15
      }
    ],
    "ColourClusteringModes": [
      {
        "Mode": "CCM_SKIP"
      }
    ],
    "ColourConversionModes": [
      {
        "BlueChannelWeight": -1,
        "GreenChannelWeight": -1,
        "LibraryFileName": "",
        "LibraryParameters": "",
        "Mode": "CICM_GENERAL",
        "RedChannelWeight": -1
      }
    ],
    "DPMCodeReadingModes": [
      {
        "LibraryFileName": "",
        "LibraryParameters": "",
        "Mode": "DPMCRM_GENERAL"
      }
    ],
    "DeblurLevel": 3,
    "DeblurModes": null,
    "DeformationResistingModes": [
      {
        "Level": 5,
        "LibraryFileName": "",
        "LibraryParameters": "",
        "Mode": "DRM_GENERAL"
      }
    ],
    "Description": "",
    "ExpectedBarcodesCount": 0,
    "FormatSpecificationNameArray": [
      "IP1_BF_DATAMATRIX",
      "defaultFormatParameterForAllBarcodeFormat"
    ],
    "GrayscaleTransformationModes": [
      {
        "LibraryFileName": "",
        "LibraryParameters": "",
        "Mode": "GTM_ORIGINAL"
      }
    ],
    "ImagePreprocessingModes": [
      {
        "LibraryFileName": "",
        "LibraryParameters": "",
        "Mode": "IPM_GENERAL"
      }
    ],
    "IntermediateResultSavingMode": {
      "Mode": "IRSM_MEMORY"
    },
    "IntermediateResultTypes": [
      "IRT_NO_RESULT"
    ],
    "LocalizationModes": [
      {
        "IsOneDStacked": 0,
        "LibraryFileName": "",
        "LibraryParameters": "",
        "Mode": "LM_SCAN_DIRECTLY",
        "ScanDirection": 0,
        "ScanStride": 0
      },
      {
        "LibraryFileName": "",
        "LibraryParameters": "",
        "Mode": "LM_STATISTICS_MARKS"
      }
    ],
    "MaxAlgorithmThreadCount": 1,
    "Name": "default",
    "PDFRasterDPI": 300,
    "PDFReadingMode": {
      "Mode": "PDFRM_AUTO"
    },
    "Pages": "",
    "RegionDefinitionNameArray": null,
    "RegionPredetectionModes": [
      {
        "LibraryFileName": "",
        "LibraryParameters": "",
        "Mode": "RPM_GENERAL"
      }
    ],
    "ResultCoordinateType": "RCT_PIXEL",
    "ReturnBarcodeZoneClarity": 0,
    "ScaleDownThreshold": 2300,
    "ScaleUpModes": [
      {
        "Mode": "SUM_AUTO"
      }
    ],
    "TerminatePhase": "TP_BARCODE_RECOGNIZED",
    "TextAssistedCorrectionMode": {
      "Mode": "TACM_SKIP"
    },
    "TextFilterModes": [
      {
        "LibraryFileName": "",
        "LibraryParameters": "",
        "MinImageDimension": 65536,
        "Mode": "TFM_GENERAL_CONTOUR",
        "Sensitivity": 0
      }
    ],
    "TextResultOrderModes": [
      {
        "Mode": "TROM_CONFIDENCE"
      },
      {
        "Mode": "TROM_POSITION"
      },
      {
        "Mode": "TROM_FORMAT"
      }
    ],
    "TextureDetectionModes": [
      {
        "LibraryFileName": "",
        "LibraryParameters": "",
        "Mode": "TDM_GENERAL_WIDTH_CONCENTRATION",
        "Sensitivity": 5
      }
    ],
    "Timeout": 10000
  },
  "Version": "3.0"
}
)JSON";

ImageProcessor::ImageProcessor(QObject *parent) : QObject(parent)
{
    reader = DBR_CreateInstance();

    char errorMessage[512];
    DBR_InitRuntimeSettingsWithString(reader, kJson.c_str(), CM_OVERWRITE, errorMessage, 512);
}

ImageProcessor::~ImageProcessor()
{
    if (reader)
        DBR_DestroyInstance(reader);
}

void ImageProcessor::processImage(const QImage &image)
{
    if (!reader)
        return;

    QString out = "";
    double elapsedMs = 0.0;
    if (!image.isNull())
    {
        int width = image.width();
        int height = image.height();

        int bytesPerLine = image.bytesPerLine();

        const uchar *pixelData = image.constBits();
        int ret = 0;

        if (image.format() == QImage::Format_RGBA8888_Premultiplied || image.format() == QImage::Format_RGBA8888)
        {
            auto start = std::chrono::high_resolution_clock::now();
            ret = DBR_DecodeBuffer(reader, pixelData, width, height, bytesPerLine, IPF_ABGR_8888, "");
            auto end = std::chrono::high_resolution_clock::now();

            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            elapsedMs = duration.count() / 1000.0; // Convert microseconds to milliseconds

            printf("API Decode Time: %.2f ms\n", elapsedMs);
        }
    }

    TextResultArray *handler = NULL;
    DBR_GetAllTextResults(reader, &handler);
    TextResult **results = handler->results;
    int count = handler->resultsCount;

    // Add timing information to output
    if (elapsedMs > 0.0)
    {
        out += "API Decode Time: " + QString::number(elapsedMs, 'f', 2) + " ms\n";
        out += "----------------------------------------------------------------------------------------\n";
    }

    for (int index = 0; index < count; index++)
    {
        //        LocalizationResult* localizationResult = results[index]->localizationResult;
        out += "Index: " + QString::number(index) + "\n";
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
