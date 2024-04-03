// FrameProcessor.h

#ifndef FRAMEPROCESSOR_H
#define FRAMEPROCESSOR_H

#include <QObject>
#include <QVideoSink>
#include <QVideoFrame>
#include "ImageProcessor.h"

class FrameProcessor : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVideoSink *videoSink READ videoSink WRITE setVideoSink NOTIFY videoSinkChanged)
    Q_PROPERTY(QString displayString READ displayString NOTIFY displayStringChanged)

public:
    explicit FrameProcessor(QObject *parent = nullptr);
    ~FrameProcessor();

    QVideoSink *videoSink() const;
    QString displayString() const;
    void setVideoSink(QVideoSink *sink);

signals:
    void videoSinkChanged();
    void displayStringChanged();
    void barcodeDetected(QString result);
    void newFrameAvailable(const QImage &image);

private slots:
    void processFrame(const QVideoFrame &frame);
    void onImageProcessed(const QString &out);

private:
    QVideoSink *m_videoSink;
    QString m_displayString;
    QThread *workerThread;
    bool m_isAvailable;
    ImageProcessor *processor;
};

#endif // FRAMEPROCESSOR_H
