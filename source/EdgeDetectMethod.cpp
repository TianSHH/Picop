// TODO 将“设定灰度阀值”中的图像二值化方法封装
#include "EdgeDetectMethod.h"

EdgeDetectMethod::EdgeDetectMethod()
{
}

EdgeDetectMethod::~EdgeDetectMethod()
{
}

QImage EdgeDetectMethod::sobel(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "边缘检测"
                       << "方法"
                       << "Sobel算子";

    ColorMethod _colorMethod = ColorMethod();
    SharpenMethod _sharpenMethod = SharpenMethod();

    originImage = _colorMethod.toGrayImage(originImage);

    QImage targetImage = _sharpenMethod.sobel(originImage);

    // 二值化
    // for (int i = 0; i < targetImage.width(); i++)
    // {
    //     for (int j = 0; j < targetImage.height(); j++)
    //     {
    //         if (qGray(targetImage.pixel(i, j)) >= 128)
    //             targetImage.setPixel(i, j, qRgb(255, 255, 255));
    //         else
    //             targetImage.setPixel(i, j, qRgb(0, 0, 0));
    //     }
    // }

    return targetImage;
} // sobel

QImage EdgeDetectMethod::prewitt(QImage originImage)
{
    FilterMethod _filterMethod(nullptr);

    // 对图像进行卷积
    QImage targetImage = _filterMethod.prewitt(originImage);

    for (int i = 0; i < targetImage.width(); i++)
    {
        for (int j = 0; j < targetImage.height(); j++)
        {
            if (qGray(targetImage.pixel(i, j)) >= 128)
                targetImage.setPixel(i, j, qRgb(255, 255, 255));
            else
                targetImage.setPixel(i, j, qRgb(0, 0, 0));
        }
    }

    return targetImage;
} // prewitt

QImage EdgeDetectMethod::laplacian(QImage originImage)
{
    FilterMethod _filterMethod(nullptr);

    QImage targetImage = _filterMethod.laplacian(originImage);

    return targetImage;
} // laplacian