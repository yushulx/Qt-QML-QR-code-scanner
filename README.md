# Qt Demo: QR Code Scanner

A QR code scanner demo for **Windows** and **Android** developed by Qt QML.

## Requirements
- [Dynamsoft C++ Barcode SDK](https://www.dynamsoft.com/barcode-reader/downloads//#desktop)
- [Dynamsoft Android Barcode SDK](https://www.dynamsoft.com/barcode-reader/downloads//#mobile)

[![](https://img.shields.io/badge/Get-30--day%20FREE%20Trial%20License-blue)](https://www.dynamsoft.com/customer/license/trialLicense/?product=dbr)

## Usage
1. Load the project to QtCreator and configure the build environment as follows:

    ![Qt project for Windows and Android](https://www.dynamsoft.com/blog/wp-content/uploads/2021/11/qt-qr-code-scanner-config.jpg)
    
2. Run the project.

    **Windows**
    
    <img src="https://www.dynamsoft.com/blog/wp-content/uploads/2021/11/qt-qr-code-scanner-windows.jpg" width="600" alt="Qt QR Code scanner for Windows">
    
    **Android**
    
    <img src="https://www.dynamsoft.com/blog/wp-content/uploads/2021/11/qt-qr-code-scanner-android.jpg" width="250" alt="Qt QR Code scanner for Android">

## What If QR Recognition Failed
If the code cannot work for you, please check the frame pixel format and then update the code accordingly.

```cpp
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
```
