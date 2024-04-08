//
//  bridge.h
//  bridge
//
//  Created by marketing on 2024/4/3.
//

#ifndef bridge_h
#define bridge_h

#include <stdio.h>
#include <string.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef enum ImagePixelFormat
    {
        /**0:Black, 1:White */
        IPF_BINARY,

        /**0:White, 1:Black */
        IPF_BINARYINVERTED,

        /**8bit gray */
        IPF_GRAYSCALED,

        /**NV21 */
        IPF_NV21,

        /**16bit with RGB channel order stored in memory from high to low address*/
        IPF_RGB_565,

        /**16bit with RGB channel order stored in memory from high to low address*/
        IPF_RGB_555,

        /**24bit with RGB channel order stored in memory from high to low address*/
        IPF_RGB_888,

        /**32bit with ARGB channel order stored in memory from high to low address*/
        IPF_ARGB_8888,

        /**48bit with RGB channel order stored in memory from high to low address*/
        IPF_RGB_161616,

        /**64bit with ARGB channel order stored in memory from high to low address*/
        IPF_ARGB_16161616,

        /**32bit with ABGR channel order stored in memory from high to low address*/
        IPF_ABGR_8888,

        /**64bit with ABGR channel order stored in memory from high to low address*/
        IPF_ABGR_16161616,

        /**24bit with BGR channel order stored in memory from high to low address*/
        IPF_BGR_888

    } ImagePixelFormat;

    typedef struct
    {
        int x1;
        int y1;
        int x2;
        int y2;
        int x3;
        int y3;
        int x4;
        int y4;

    } LocalizationResult;

    typedef struct
    {

        /**Barcode type in BarcodeFormat group 1 as string */
        char *barcodeFormatString;

        /**The barcode text, ends by '\0' */
        char *barcodeText;

        LocalizationResult *localizationResult;

        /**Reserved memory for the struct. The length of this array indicates the size of the memory reserved for this struct. */
        char reserved[44];
    } TextResult;

    typedef struct
    {
        /**The total count of text result */
        int resultsCount;

        /**The text result array */
        TextResult **results;
    } TextResultArray;

    typedef enum ConflictMode
    {
        /**Ignores new settings and inherits the previous settings. */
        CM_IGNORE = 1,

        /**Overwrites the old settings with new settings. */
        CM_OVERWRITE = 2

    } ConflictMode;

    typedef struct
    {
        void *instance;
        void *result;
    } BarcodeReader;

    const char *DBR_GetVersion(void);
    int DBR_InitLicense(const char *pLicense, char errorMsgBuffer[], const int errorMsgBufferLen);
    void *DBR_CreateInstance(void);
    void DBR_DestroyInstance(void *barcodeReader);
    int DBR_InitRuntimeSettingsWithString(void *barcodeReader, const char *content, const ConflictMode conflictMode, char errorMsgBuffer[], const int errorMsgBufferLen);
    int DBR_GetAllTextResults(void *barcodeReader, TextResultArray **pResults);
    void DBR_FreeTextResults(TextResultArray **pResults);
    int DBR_DecodeBuffer(void *barcodeReader, const unsigned char *pBufferBytes, const int width, const int height, const int stride, const ImagePixelFormat format, const char *pTemplateName);

#ifdef __cplusplus
}
#endif

#endif /* bridge_h */
