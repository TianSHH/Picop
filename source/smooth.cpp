#include "smooth.h"

Smooth::Smooth()
{
}

Smooth::~Smooth()
{
}

QImage Smooth::averageFiltering(QImage *originImage)
{
    bool ok;
    int filterRadius = QInputDialog::getInt(nullptr, tr("均值滤波"), "输入滤波器大小(1~30)", 3, 1, 30, 1, &ok);
    if (ok)
    {
        int kernel[filterRadius][filterRadius];

        for (int i = 0; i < filterRadius; i++)
            for (int j = 0; j < filterRadius; j++)
                kernel[i][j] = 1;

        int len = filterRadius / 2;

        int originWidth = originImage->width();
        int originHeight = originImage->height();

        // originImage->data_ptr()

        QImage targetImage = QImage(originWidth + len, originHeight + len, QImage::Format_RGB32);
        // cv::Mat(originHeight, originWidth, format, const_cast<uchar*>(originImage->bits()), originImage->bytesPerLine()).clone();

        // 添加边框
        for (int i = 0; i < targetImage.width(); i++)
        {
            for (int j = 0; j < targetImage.height(); j++)
            {
                if (i >= len && i < targetImage.width() - len && j >= len && j <= targetImage.height() - len)
                { // 不在边框中
                    QColor originImageColor = QColor(originImage->pixel(i - len, j - len));
                    targetImage.setPixelColor(i, j, originImageColor);
                }
                else
                {                                          // 在边框中
                    targetImage.setPixel(i, j, Qt::white); // 将边框中颜色设置为白色
                }
            }
        }

        for (int i = len; i < targetImage.width(); i++)
        {
            for (int j = len; j < targetImage.height(); j++)
            {

                int r = targetImage.pixelColor(i, j).red();
                int g = targetImage.pixelColor(i, j).green();
                int b = targetImage.pixelColor(i, j).blue();

                for (int p = -len; p <= len; p++)
                {
                    for (int q = -len; q <= len; q++)
                    {
                        r *= kernel[len + p][len + q];
                        g *= kernel[len + p][len + q];
                        b *= kernel[len + p][len + q];
                    }
                }

                r /= (filterRadius * filterRadius);
                g /= (filterRadius * filterRadius);
                b /= (filterRadius * filterRadius);

                originImage->setPixel(i - len, j - len, qRgb(r, g, b));
            }
        }
    }

    return *originImage;
} // averageFiltering

QImage Smooth::medianFiltering(QImage *originImage)
{
    // bool ok;
    // int filterRadius = QInputDialog::getInt(nullptr, tr("中值滤波"), "输入滤波器大小(1~30)", 3, 1, 30, 1, &ok);
    // if (ok)
    // {
    //     int width = originImage->width();
    //     int height = originImage->height();

    //     // * originImage, filterRadius

    // }
} // medianFiltering
