#ifndef FILTERMETHOD_H
#define FILTERMETHOD_H

#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtGui>

class FilterMethod
{
public:
    FilterMethod();
    ~FilterMethod();

public:
    QImage filtering(QImage originImage, int filterSize, int *filterMatrix);
};

#endif FILTERMETHOD_H