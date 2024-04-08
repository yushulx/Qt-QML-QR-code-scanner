#include "bridge.h"
#import <foundation/Foundation.h>
#import <DynamsoftBarcodeReader/DynamsoftBarcodeReader.h>

@interface LicenseVerifier : NSObject <DBRLicenseVerificationListener>
@end

@implementation  LicenseVerifier

- (void)DBRLicenseVerificationCallback:(_Bool)isSuccess error:(NSError *)error {
    NSLog(@"License Verification Success: %d, Error: %@", isSuccess, error.localizedDescription);
}
@end

const char *DBR_GetVersion(void)
{
    NSString *version = [DynamsoftBarcodeReader getVersion];
    return [version UTF8String];
}

int DBR_InitLicense(const char* pLicense, char errorMsgBuffer[], const int errorMsgBufferLen)
{
    @autoreleasepool {
        NSString *licenseKey = [NSString stringWithUTF8String:pLicense];
        LicenseVerifier *verifier = [[LicenseVerifier alloc] init];
        
        [DynamsoftBarcodeReader initLicense:licenseKey verificationDelegate: verifier];
        
        return 0;
    }
    
}

void* DBR_CreateInstance(void)
{
    @autoreleasepool {
        DynamsoftBarcodeReader *barcodeReader = [[DynamsoftBarcodeReader alloc] init];
        
        BarcodeReader *brInstance = malloc(sizeof(BarcodeReader));
        brInstance->instance = (__bridge_retained void*)barcodeReader;
        brInstance->result = NULL; // Initially, there are no results
        
        return brInstance;
    }

}

void DBR_DestroyInstance(void* barcodeReader)
{
    @autoreleasepool {
        if (barcodeReader != NULL) {
            BarcodeReader *brInstance = (BarcodeReader *)barcodeReader;
            DynamsoftBarcodeReader *barcodeReader = (__bridge_transfer DynamsoftBarcodeReader *)brInstance->instance;
            barcodeReader = nil;
        
            if (brInstance->result != NULL) {
                brInstance->result = nil;
            }
            
            free(brInstance); 
        }
    }
}

int DBR_InitRuntimeSettingsWithString(void* barcodeReader, const char* content, const ConflictMode conflictMode, char errorMsgBuffer[], const int errorMsgBufferLen)
{
    @autoreleasepool {
        if (barcodeReader == NULL) return -1;
        
        BarcodeReader *brInstance = (BarcodeReader *)barcodeReader;
        DynamsoftBarcodeReader *reader = (__bridge DynamsoftBarcodeReader*)brInstance->instance;
        NSString *settings = [NSString stringWithUTF8String:content];
        
        NSError *error = nil;
        
        [reader initRuntimeSettingsWithString:settings conflictMode:(EnumConflictMode)conflictMode error:&error];
        
        if (error) {
            return -1;
        }
        
        return 0;
    }
}

int DBR_DecodeBuffer(void* barcodeReader, const unsigned char* pBufferBytes, int width, int height, int stride, ImagePixelFormat format, const char* pTemplateName) {
    @autoreleasepool {
        if (barcodeReader == NULL) return -1;

        BarcodeReader *brInstance = (BarcodeReader *)barcodeReader;
        DynamsoftBarcodeReader *reader = (__bridge DynamsoftBarcodeReader*)brInstance->instance;
        
        NSData *bufferBytes = [NSData dataWithBytes:pBufferBytes length:stride * height]; 
        
//        NSString *templateName = [NSString stringWithUTF8String:pTemplateName];
        
        NSError *error = nil;

        EnumImagePixelFormat objcFormat = (EnumImagePixelFormat)format;
        
        NSArray<iTextResult*>* results = [reader decodeBuffer:bufferBytes withWidth:width height:height stride:stride format:objcFormat error:&error];
        
        brInstance->result = (__bridge_retained void*)results;

        if (error) {
            return -1;
        }

        return 0;
    }
}

int DBR_GetAllTextResults(void *barcodeReader, TextResultArray **pResults) {
    @autoreleasepool {
        if (barcodeReader == NULL || pResults == NULL) return -1;
        
        BarcodeReader *brInstance = (BarcodeReader *)barcodeReader;
//        DynamsoftBarcodeReader *reader = (__bridge DynamsoftBarcodeReader*)brInstance->instance;	
        NSArray<iTextResult*> *results = (__bridge NSArray<iTextResult*>*)brInstance->result;
        
        TextResultArray *resultArray = (TextResultArray *)malloc(sizeof(TextResultArray));
        resultArray->resultsCount = (int)[results count];
        resultArray->results = (TextResult **)malloc(sizeof(TextResult *) * resultArray->resultsCount);
        
        for (NSInteger i = 0; i < [results count]; i++) {
            iTextResult *iResult = [results objectAtIndex:i];
            
            TextResult *textResult = (TextResult *)malloc(sizeof(TextResult));
            textResult->barcodeFormatString = strdup([iResult.barcodeFormatString UTF8String]);
            textResult->barcodeText = strdup([iResult.barcodeText UTF8String]);
            
            LocalizationResult *locResult = (LocalizationResult *)malloc(sizeof(LocalizationResult));
            NSArray *points = iResult.localizationResult.resultPoints;
            if (points) {
                CGPoint point0 = [points[0] CGPointValue];
                locResult->x1 = (int)point0.x;
                locResult->y1 = (int)point0.y;
                
                CGPoint point1 = [points[1] CGPointValue];
                locResult->x2 = (int)point1.x;
                locResult->y2 = (int)point1.y;
                
                CGPoint point2 = [points[2] CGPointValue];
                locResult->x3 = (int)point2.x;
                locResult->y3 = (int)point2.y;
                
                CGPoint point3 = [points[3] CGPointValue];
                locResult->x4 = (int)point3.x;
                locResult->y4 = (int)point3.y;
                
                textResult->localizationResult = locResult;
            }
            
            
            memset(textResult->reserved, 0, sizeof(textResult->reserved));
            
            resultArray->results[i] = textResult;
        }
        
        *pResults = resultArray;
        
        return 0; 
    }
}

void DBR_FreeTextResults(TextResultArray **pResults) {
    if (pResults == NULL || *pResults == NULL) return;
    
    TextResultArray *resultsArray = *pResults;
    
    for (int i = 0; i < resultsArray->resultsCount; i++) {
        TextResult *textResult = resultsArray->results[i];
        
        if (textResult->barcodeFormatString != NULL) {
            free(textResult->barcodeFormatString);
            textResult->barcodeFormatString = NULL;
        }
        
        if (textResult->barcodeText != NULL) {
            free(textResult->barcodeText);
            textResult->barcodeText = NULL;
        }
        
        if (textResult->localizationResult != NULL) {
            free(textResult->localizationResult);
            textResult->localizationResult = NULL;
        }
        
        free(textResult);
        resultsArray->results[i] = NULL;
    }
    
    if (resultsArray->results != NULL) {
        free(resultsArray->results);
        resultsArray->results = NULL;
    }
    
    free(resultsArray);
    *pResults = NULL;
}
