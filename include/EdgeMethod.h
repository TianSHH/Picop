#ifndef EDGEMETHOD_H
#define EDGEMETHOD_H

#include "ColorMethod.h"
#include "FilterMethod.h"
#include "SharpenMethod.h"
#include <QtCore/QDebug>
#include <QtCore/QThread>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <opencv4/opencv2/core/utility.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/imgcodecs/imgcodecs.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>

using namespace cv;

class EdgeMethod
{
public:
    EdgeMethod();
    ~EdgeMethod();

public:
    QImage sobel(QImage originImage);
    QImage prewitt(QImage orginImage);
    QImage laplacian(QImage originImage);

    // 边缘跟踪
    QImage edgeTracing(QImage originImage);
    QImage lineDetection(QImage originImae);
};

#endif // EDGEMETHOD_H