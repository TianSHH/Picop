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
    QImage laplace(QImage originImage);
    QImage enhancedLaplace(QImage originImage);
};

#endif SHARPENMETHOD_H