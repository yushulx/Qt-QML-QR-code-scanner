#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#if QT_CONFIG(permissions)
#include <QPermission>
#endif

#include "FrameProcessor.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<FrameProcessor>("com.dynamsoft.barcode", 1, 1, "FrameProcessor");

    QQmlApplicationEngine engine;

    QQuickView view;
    view.setResizeMode(QQuickView::SizeRootObjectToView);

    auto setupView = [&engine, &app]() {
        QObject::connect(
            &engine,
            &QQmlApplicationEngine::objectCreationFailed,
            &app,
            []() { QCoreApplication::exit(-1); },
            Qt::QueuedConnection);
        engine.loadFromModule("qt6project", "Main");
    };

#if QT_CONFIG(permissions)
    QCameraPermission cameraPermission;
    qApp->requestPermission(cameraPermission, [&setupView](const QPermission &permission) {
        if (permission.status() != Qt::PermissionStatus::Granted)
            qWarning("Camera permission is not granted!");
        setupView();
    });
#else
    setupView();
#endif

    return app.exec();
}
