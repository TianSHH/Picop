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

    // csdn
    // int rebortsFx[] = {0, 0, 0,
    //                    0, 1, 0,
    //                    0, 0, -1};
    // int rebortsFy[] = {0, 0, 0,
    //                    0, 0, 1,
    //                    0, -1, 0};

    // 课件
    int rebortsFx[] = {0, 0, 0,
                       0, -1, 0,
                       0, 0, 1};
    int rebortsFy[] = {0, 0, 0,
                       0, 0, -1,
                       0, 1, 0};

    FilterMethod _filterMethod;

    QImage middleImageFx = _filterMethod.filtering(originImage, 3, rebortsFx, false);
    QImage middleImageFy = _filterMethod.filtering(originImage, 3, rebortsFy, false);
    QImage targetImage = QImage(middleImageFx.width(), middleImageFx.height(), QImage ::Format_RGB32);

    for (int i = 0; i < middleImageFx.width(); i++)
    {
        int r = 0;
        int g = 0;
        int b = 0;
        for (int j = 0; j < middleImageFx.height(); j++)
        {
            r = qMax(qRed(middleImageFx.pixel(i, j)), qRed(middleImageFy.pixel(i, j)));
            g = qMax(qGreen(middleImageFx.pixel(i, j)), qGreen(middleImageFy.pixel(i, j)));
            b = qMax(qBlue(middleImageFx.pixel(i, j)), qBlue(middleImageFy.pixel(i, j)));

            targetImage.setPixel(i, j, qRgb(r, g, b));
        }
    }

    return targetImage;
} // reborts

QImage SharpenMethod::sobel(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行图像锐化"
                       << "方法"
                       << "Sobel算子";

    int sobelFx[] = {1, 0, -1,
                     2, 0, -2,
                     1, 0, -1};
    int sobelFy[] = {-1, -2, -1,
                     0, 0, 0,
                     1, 2, 1};

    FilterMethod _filterMethod;

    QImage middleImageFx = _filterMethod.filtering(originImage, 3, sobelFx, false);
    QImage middleImageFy = _filterMethod.filtering(originImage, 3, sobelFy, false);
    QImage targetImage = QImage(middleImageFx.width(), middleImageFx.height(), QImage ::Format_RGB32);

    for (int i = 0; i < middleImageFx.width(); i++)
    {
        int r = 0;
        int g = 0;
        int b = 0;
        for (int j = 0; j < middleImageFx.height(); j++)
        {
            r = qMax(qRed(middleImageFx.pixel(i, j)), qRed(middleImageFy.pixel(i, j)));
            g = qMax(qGreen(middleImageFx.pixel(i, j)), qGreen(middleImageFy.pixel(i, j)));
            b = qMax(qBlue(middleImageFx.pixel(i, j)), qBlue(middleImageFy.pixel(i, j)));

            targetImage.setPixel(i, j, qRgb(r, g, b));
        }
    }

    return targetImage;
} // sobel

QImage SharpenMethod::laplace(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行图像锐化"
                       << "方法"
                       << "Laplace算子";

    int laplace[] = {0, -1, 0,
                     -1, 4, -1,
                     0, -1, 0};

    FilterMethod _filterMethod;

    return _filterMethod.filtering(originImage, 3, laplace, false);
} // laplace

QImage SharpenMethod::enhancedLaplace(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行图像锐化"
                       << "方法"
                       << "增强Laplace算子";

    // int enhancedLaplace[] = {0, -1, 0,
    //                          -1, 5, -1,
    //                          0, -1, 0};

    // int enhancedLaplace[] = {-1, -1, -1,
    //                          -1, 8, -1,
    //  -1, -1, -1};

    int enhancedLaplace[] = {1, -2, 1,
                             -2, 4, -2,
                             1, -2, 1};

    FilterMethod _filterMethod;

    return _filterMethod.filtering(originImage, 3, enhancedLaplace, false);
} // enhancedLaplace