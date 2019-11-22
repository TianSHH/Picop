#ifndef SPECTROGRAMMETHOD_H
#define SPECTROGRAMMETHOD_H

#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtWidgets/QAction>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

class SpectrogramMethod
{
public:
    SpectrogramMethod();
    ~SpectrogramMethod();

public:
    void displaySpectrogram(QString imagePath);
    cv::Mat QImageToMat(QImage image);
};

#endif // !SPECTROGRAMMETHOD_H
