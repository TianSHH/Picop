#include "SharpenMethod.h"

SharpenMethod::SharpenMethod()
{
}

SharpenMethod::~SharpenMethod()
{
}

QImage SharpenMethod::reborts(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行图像锐化"
                       << "方法"
                       << "Reborts算子";

    FilterMethod _filterMethod(nullptr);

    return _filterMethod.reborts(originImage);
} // reborts

QImage SharpenMethod::sobel(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行图像锐化"
                       << "方法"
                       << "Sobel算子";

    FilterMethod _filterMethod(nullptr);

    return _filterMethod.sobel(originImage);
} // sobel

QImage SharpenMethod::laplacian(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行图像锐化"
                       << "方法"
                       << "Laplacian算子";
    FilterMethod _filterMethod(nullptr);

    return _filterMethod.laplacian(originImage);
} // laplacian

QImage SharpenMethod::enhancedLaplacian(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行图像锐化"
                       << "方法"
                       << "增强Laplacian算子";

    FilterMethod _filterMethod(nullptr);

    return _filterMethod.enhancedLaplacian(originImage);
} // enhancedLaplacian