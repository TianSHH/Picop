#ifndef FORMATMETHOD_H
#define FORMATMETHOD_H

#include <QtCore/QDebug>
#include <QtGui/QImage>
#include <opencv2/imgproc/imgproc.hpp>

class FormatMethod
{
public:
    cv::Mat toMat(const QImage &image);
    QImage toQImage(const cv::Mat &mat);
};

#endif // FORMATMETHOD_H