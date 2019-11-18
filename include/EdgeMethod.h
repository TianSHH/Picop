#ifndef EDGEMETHOD_H
#define EDGEMETHOD_H

#include "ColorMethod.h"
#include "FilterMethod.h"
#include "SharpenMethod.h"
#include <QtCore/QDebug>
#include <QtGui/QImage>
#include <QtGui/QPainter>

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