#ifndef SPECTROGRAM_H
#define SPECTROGRAM_H

#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtWidgets/QAction>
#include <opencv4/opencv2/core.hpp>
#include <opencv4/opencv2/highgui.hpp>
#include <opencv4/opencv2/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <opencv4/opencv2/opencv.hpp>

class Spectrogram
{
public:
    Spectrogram();
    ~Spectrogram();

public:
    void displaySpectrogram(QString imagePath);
    cv::Mat QImageToMat(QImage image);
};

#endif // !SPECTROGRAM_H