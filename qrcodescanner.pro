TEMPLATE=app
TARGET=qrcodescanner

QT += quick qml multimedia

SOURCES += main.cpp
RESOURCES += qrcodescanner.qrc
HEADERS = include/DynamsoftCommon.h \
    include/DynamsoftBarcodeReader.h

target.path = $$PWD
INSTALLS += target

DISTFILES += \
    libs/windows/DynamsoftBarcodeReaderx64.dll \
    libs/windows/vcomp110.dll \
    libs/android/libDynamsoftBarcodeReaderAndroid.so \
    main.qml

win32: LIBS += -L$$PWD/libs/windows -lDynamsoftBarcodeReaderx64
unix: LIBS += -L$$PWD/libs/android -lDynamsoftBarcodeReaderAndroid

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
#    ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
    ANDROID_EXTRA_LIBS = $$PWD/libs/android/libDynamsoftBarcodeReaderAndroid.so
}
