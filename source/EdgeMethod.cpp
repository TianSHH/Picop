// TODO 将“设定灰度阀值”中的图像二值化方法封装
#include "EdgeMethod.h"

EdgeMethod::EdgeMethod()
{
}

EdgeMethod::~EdgeMethod()
{
}

QImage EdgeMethod::sobel(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "边缘检测"
                       << "方法"
                       << "Sobel算子";

    ColorMethod _colorMethod = ColorMethod();
    originImage = _colorMethod.toGrayImage(originImage);

    FilterMethod _filterMethod(nullptr);
    QImage targetImage = _filterMethod.sobel(originImage);

    return targetImage;
    // return targetImage;
} // sobel

QImage EdgeMethod::prewitt(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "边缘检测"
                       << "方法"
                       << "Prewitt算子";

    ColorMethod _colorMethod = ColorMethod();
    originImage = _colorMethod.toGrayImage(originImage);

    FilterMethod _filterMethod(nullptr);
    QImage targetImage = _filterMethod.prewitt(originImage);

    return targetImage;
} // prewitt

QImage EdgeMethod::laplacian(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "边缘检测"
                       << "方法"
                       << "Laplacian算子";

    ColorMethod _colorMethod = ColorMethod();
    originImage = _colorMethod.toGrayImage(originImage);

    FilterMethod _filterMethod(nullptr);
    QImage targetImage = _filterMethod.laplacian(originImage);

    return targetImage;
} // laplacian

// 边缘跟踪
QImage EdgeMethod::edgeTracing(QImage originImage)
{
    int width = originImage.width();
    int height = originImage.height();

    QImage middleImage = QImage(width, height, QImage::Format_RGB888);
    QImage targetImage = QImage(width, height, QImage::Format_RGB888);

    middleImage.fill(Qt::white);
    targetImage.fill(Qt::white);

    FilterMethod _filterMethod;

    // step1 get gradient map
    // 第一步, 得到梯度图
    middleImage = _filterMethod.laplacian(originImage);

    // 梯度图二值化
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int gray = qGray(originImage.pixel(i, j));

            if (gray > 128)
                gray = 255;
            else
                gray = 0;

            middleImage.setPixel(i, j, qRgb(gray, gray, gray));
        }
    }

    // int pixels[8] = {0};
    // bool map[width][height] = {false};

    // for (int i = 1; i < width - 1; i++)
    // {
    //     for (int j = 1; j < height - 1; j++)
    //     {
    //         if (qRed(middleImage.pixel(i, j) == 0))
    //         {
    //             targetImage.setPixel(i, j, qRgb(0, 0, 0));

    //             // int max =

    //             pixels[0] = QColor(middleImage.pixel(i - 1, j - 1)).red();
    //             pixels[1] = QColor(middleImage.pixel(i - 1, j)).red();
    //             pixels[2] = QColor(middleImage.pixel(i - 1, j + 1)).red();
    //             pixels[3] = QColor(middleImage.pixel(i, j - 1)).red();
    //             pixels[4] = QColor(middleImage.pixel(i, j + 1)).red();
    //             pixels[5] = QColor(middleImage.pixel(i + 1, j - 1)).red();
    //             pixels[6] = QColor(middleImage.pixel(i + 1, j)).red();
    //             pixels[7] = QColor(middleImage.pixel(i + 1, j + 1)).red();
    //         }
    //     }
    // }

    return targetImage;
} // edgeTracing