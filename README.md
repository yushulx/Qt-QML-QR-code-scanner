# Qt6 Demo: Barcode QR Code Scanner

A cross-platform demo of a barcode and QR code scanner developed with **Qt6** and [Dynamsoft Barcode Reader](https://www.dynamsoft.com/barcode-reader/sdk-mobile/?utm_content=nav-products).

## Supported Platforms
- Windows
- Android
- iOS (Contact support@dynamsoft.com to get the shared libraries)

## Prerequisites
- [Qt Online Installer](https://www.qt.io/download-qt-installer-oss)
- [Dynamsoft Barcode Reader Trial License](https://www.dynamsoft.com/customer/license/trialLicense/?product=dbr)


## Usage
1. Load the project into Qt Creator (**Windows** or **macOS**) via `CMakeLists.txt` and configure the build environment as follows:

    ![Qt project for Windows and Android](https://www.dynamsoft.com/codepool/img/2024/04/qt6-cmake-config.png)
   
2. Set the license key in `FrameProcessor.cpp`:

    ```cpp
    DBR_InitLicense("LICENSE-KEY", errorMsgBuffer, 512);
    ```
 
2. Run the project.

    **Windows**
    
    <img src="https://www.dynamsoft.com/codepool/img/2024/04/qt6-windows-qrcode-scanner.jpg" width="600" alt="Qt QR Code scanner for Windows">
    
    **Android**
    
    <img src="https://www.dynamsoft.com/codepool/img/2024/04/qt6-android-qrcode-scanner.jpg" width="250" alt="Qt QR Code scanner for Android">

    **iOS**
    
    <img src="https://www.dynamsoft.com/codepool/img/2024/04/qt6-ios-qrcode-scanner.png" width="250" alt="Qt QR Code scanner for iOS">

## Blog
[How to Build a QR Code Scanner for Windows and Android with Qt QML](https://www.dynamsoft.com/codepool/qt-qml-qr-code-scanner.html)
