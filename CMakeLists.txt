cmake_minimum_required(VERSION 3.16)

project(qt6project VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(TARGET_NAME appqt6project)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Multimedia)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appqt6project
    main.cpp
)

qt_add_qml_module(appqt6project
    URI qt6project
    VERSION 1.0
    QML_FILES Main.qml
    RESOURCES Info.plist
SOURCES include/DynamsoftBarcodeReader.h include/DynamsoftCommon.h
# RESOURCES libs/android/libDynamsoftBarcodeReaderAndroid.so libs/windows/DBRx64.lib libs/windows/DynamicPdfx64.dll libs/windows/DynamsoftBarcodeReaderx64.dll libs/windows/DynamsoftLicClientx64.dll libs/windows/DynamsoftLicenseClientx64.dll libs/windows/vcomp110.dll
SOURCES FrameProcessor.cpp FrameProcessor.h
SOURCES ImageProcessor.h
SOURCES ImageProcessor.cpp
# RESOURCES libs/ios/DynamsoftBarcodeReader.framework/Modules/module.modulemap libs/ios/DynamsoftBarcodeReader.framework/DynamsoftBarcodeReader libs/ios/DynamsoftBarcodeReader.framework/Info.plist
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appqt6project PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appqt6project
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include_directories("${PROJECT_SOURCE_DIR}/include/")

target_link_libraries(${TARGET_NAME} PRIVATE Qt6::Quick Qt::Multimedia)

# Platform-specific configurations
if(WIN32)
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
        target_link_libraries(${TARGET_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/libs/windows/DynamsoftBarcodeReaderx64.dll")
    else() # Assuming MSVC or other non-GNU compilers
        target_link_libraries(${TARGET_NAME} PRIVATE "DBRx64")
    endif()

    # Copy DLLs to build directory after build
    add_custom_command(TARGET ${TARGET_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${PROJECT_SOURCE_DIR}/libs/windows/"
        $<TARGET_FILE_DIR:${TARGET_NAME}>)
elseif(ANDROID)
    add_library(native-lib SHARED IMPORTED)
    set_target_properties(native-lib PROPERTIES IMPORTED_LOCATION "${PROJECT_SOURCE_DIR}/libs/android/libDynamsoftBarcodeReaderAndroid.so")
    target_link_libraries(${TARGET_NAME} PRIVATE native-lib)
elseif(APPLE)
    add_library(dbr_framework SHARED IMPORTED)
    set_target_properties(dbr_framework PROPERTIES IMPORTED_LOCATION
                           "${PROJECT_SOURCE_DIR}/libs/ios/DynamsoftBarcodeReader.framework"
                          FRAMEWORK TRUE)

    target_link_libraries(${TARGET_NAME} PRIVATE "${PROJECT_SOURCE_DIR}/libs/ios/libcryptoarm64.a" "${PROJECT_SOURCE_DIR}/libs/ios/libsslarm64.a" "${PROJECT_SOURCE_DIR}/libs/ios/libdbrarm64.a")

    # System frameworks
    find_library(UIKIT_FRAMEWORK UIKit)
    if(NOT UIKIT_FRAMEWORK)
        message(FATAL_ERROR "UIKit framework not found")
    endif()

    target_link_libraries(${TARGET_NAME} PRIVATE "${UIKIT_FRAMEWORK}")
endif()


include(GNUInstallDirs)
install(TARGETS appqt6project
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
