#ifndef IMAGEPROCESSOR_H
#define IMAGEPROCESSOR_H

#include <QObject>

class ImageProcessor : public QObject {
    Q_OBJECT

public:
    explicit ImageProcessor(QObject *parent = nullptr);
    ~ImageProcessor();

public slots:
    void processImage(const QImage &image);

signals:
    void imageProcessed(const QString &out);

private:
    void *reader;
};


#endif // IMAGEPROCESSOR_H
