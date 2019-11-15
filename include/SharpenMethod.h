#ifndef SHARPENMETHOD_H
#define SHARPENMETHOD_H

#include "FilterMethod.h"
#include <QtCore/QDebug>
#include <QtGui>

class SharpenMethod
{
public:
    SharpenMethod();
    ~SharpenMethod();

public:
    QImage reborts(QImage originImage);
    QImage sobel(QImage originImage);
    QImage laplacian(QImage originImage);
    QImage enhancedLaplacian(QImage originImage);
};

#endif // SHARPENMETHOD_H
