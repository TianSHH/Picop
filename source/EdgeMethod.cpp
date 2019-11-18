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

    SharpenMethod _sharpenMethod = SharpenMethod();
    QImage targetImage = _sharpenMethod.sobel(originImage);

    // // 二值化
    // for (int i = 0; i < targetImage.width(); i++)
    // {
    //     for (int j = 0; j < targetImage.height(); j++)
    //     {
    //         if (qGray(targetImage.pixel(i, j)) >= 30)
    //             targetImage.setPixel(i, j, qRgb(255, 255, 255));
    //         else
    //             targetImage.setPixel(i, j, qRgb(0, 0, 0));
    //     }
    // }

    return targetImage;
} // sobel

QImage EdgeMethod::prewitt(QImage originImage)
{
    ColorMethod _colorMethod = ColorMethod();
    originImage = _colorMethod.toGrayImage(originImage);

    FilterMethod _filterMethod(nullptr);
    QImage targetImage = _filterMethod.prewitt(originImage);

    // for (int i = 0; i < targetImage.width(); i++)
    // {
    //     for (int j = 0; j < targetImage.height(); j++)
    //     {
    //         if (qGray(targetImage.pixel(i, j)) >= 30)
    //             targetImage.setPixel(i, j, qRgb(255, 255, 255));
    //         else
    //             targetImage.setPixel(i, j, qRgb(0, 0, 0));
    //     }
    // }

    return targetImage;
} // prewitt

QImage EdgeMethod::laplacian(QImage originImage)
{
    ColorMethod _colorMethod = ColorMethod();
    originImage = _colorMethod.toGrayImage(originImage);

    FilterMethod _filterMethod(nullptr);
    QImage targetImage = _filterMethod.laplacian(originImage);

    for (int i = 0; i < targetImage.width(); i++)
    {
        for (int j = 0; j < targetImage.height(); j++)
        {
            if (qGray(targetImage.pixel(i, j)) >= 30)
                targetImage.setPixel(i, j, qRgb(255, 255, 255));
            else
                targetImage.setPixel(i, j, qRgb(0, 0, 0));
        }
    }

    return targetImage;
} // laplacian

// 边缘跟踪
QImage EdgeMethod::edgeTracing(QImage origimImage)
{
    int width = origimImage.width();
    int height = origimImage.height();

    QImage middleImage = QImage(width, height, QImage::Format_RGB888);
    QImage targetImage = QImage(width, height, QImage::Format_RGB888);

    middleImage.fill(Qt::white);
    targetImage.fill(Qt::white);

    二值化
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int gray = qGray(origimImage.pixel(i, j));

            if (gray > 128)
                gray = 255;
            else
                gray = 0;

            middleImage.setPixel(i, j, qRgb(gray, gray, gray));
        }
    }

    int pixels[8] = {0}; // 目标像素周围的 8 个像素

    for (int i = 1; i < width - 1; i++)
    {
        for (int j = 1; j < height - 1; j++)
        {
            memset(pixels, 0, sizeof(pixels));

            if (QColor(middleImage.pixel(i, j)).red() == 0)
            {
                targetImage.setPixel(i, j, qRgb(0, 0, 0));
                pixels[0] = QColor(middleImage.pixel(i - 1, j - 1)).red();
                pixels[1] = QColor(middleImage.pixel(i - 1, j)).red();
                pixels[2] = QColor(middleImage.pixel(i - 1, j + 1)).red();
                pixels[3] = QColor(middleImage.pixel(i, j - 1)).red();
                pixels[4] = QColor(middleImage.pixel(i, j + 1)).red();
                pixels[5] = QColor(middleImage.pixel(i + 1, j - 1)).red();
                pixels[6] = QColor(middleImage.pixel(i + 1, j)).red();
                pixels[7] = QColor(middleImage.pixel(i + 1, j + 1)).red();

                if (pixels[0] + pixels[1] + pixels[2] + pixels[3] + pixels[4] + pixels[5] + pixels[6] + pixels[7] == 0)
                    targetImage.setPixel(i, j, qRgb(255, 255, 255));
            }
        }
    }

    return targetImage;
} // edgeTracing