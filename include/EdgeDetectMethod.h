#ifndef EDGEDETECTMETHOD_H
#define EDGEDETECTMETHOD_H

#include "SharpenMethod.h"
#include <QtCore/QDebug>
#include <QtGui>

class EdgeDetectMethod
{
public:
    EdgeDetectMethod();
    ~EdgeDetectMethod();

public:
    QImage sobel(QImage originImage);
    QImage prewitt(QImage orginImage);
    QImage laplacian(QImage originImage);
};

#endif // EDGEDETECTMETHOD_H