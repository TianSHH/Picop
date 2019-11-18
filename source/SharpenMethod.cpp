#include "SharpenMethod.h"

SharpenMethod::SharpenMethod()
{
}

SharpenMethod::~SharpenMethod()
{
}

// Reborts 算子
QImage SharpenMethod::reborts(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行图像锐化"
                       << "方法"
                       << "Reborts算子";

    FilterMethod _filterMethod(nullptr);

    QImage middleImage = _filterMethod.reborts(originImage);

    return _filterMethod.adding(originImage, middleImage);
} // reborts

// Sobel 算子
QImage SharpenMethod::sobel(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行图像锐化"
                       << "方法"
                       << "Sobel算子";

    FilterMethod _filterMethod(nullptr);

    QImage middleImage = _filterMethod.sobel(originImage);

    return _filterMethod.adding(originImage, middleImage);
} // sobel

// Laplacian 算子
QImage SharpenMethod::laplacian(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行图像锐化"
                       << "方法"
                       << "Laplacian算子";
    FilterMethod _filterMethod(nullptr);

    QImage middleImage = _filterMethod.laplacian(originImage);

    return _filterMethod.adding(originImage, middleImage);
} // laplacian

// 增强 Laplacian 算子
QImage SharpenMethod::enhancedLaplacian(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行图像锐化"
                       << "方法"
                       << "增强Laplacian算子";

    FilterMethod _filterMethod(nullptr);

    QImage middleImage = _filterMethod.enhancedLaplacian(originImage);

    return _filterMethod.adding(originImage, middleImage);
} // enhancedLaplacian