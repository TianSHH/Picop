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
    int filterRadius = QInputDialog::getInt(nullptr, QObject::tr("均值滤波"), "输入滤波器大小(1~30)", 3, 1, 30, 1, &ok);
    if (ok)
    {
        if (filterRadius % 2 == 0)
            filterRadius += 1;

        qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                           << "图像平滑, 方式,均值滤波"
                           << "滤波器大小" << filterRadius;

        int kernel[filterRadius][filterRadius];

        for (int i = 0; i < filterRadius; i++)
            for (int j = 0; j < filterRadius; j++)
                kernel[i][j] = 1;

        int len = filterRadius / 2;

        int originWidth = originImage->width();
        int originHeight = originImage->height();

        QImage targetImage = QImage(originWidth + 2 * len, originHeight + 2 * len, QImage::Format_RGB32);

        // 添加边框
        for (int i = 0; i < targetImage.width(); i++)
            for (int j = 0; j < targetImage.height(); j++)
                if (i >= len && i < targetImage.width() - len && j >= len && j < targetImage.height() - len)
                { // 不在边框中
                    QColor originImageColor = QColor(originImage->pixel(i - len, j - len));
                    targetImage.setPixelColor(i, j, originImageColor);
                }
                else                                       // 在边框中
                    targetImage.setPixel(i, j, Qt::white); // 将边框中颜色设置为白色

        for (int i = len; i < targetImage.width() - len; i++)
            for (int j = len; j < targetImage.height() - len; j++)
            {

                int r = 0;
                int g = 0;
                int b = 0;

                for (int p = -len; p <= len; p++)
                    for (int q = -len; q <= len; q++)
                    {
                        r = targetImage.pixelColor(i + p, j + q).red() * kernel[len + p][len + q] + r;
                        g = targetImage.pixelColor(i + p, j + q).green() * kernel[len + p][len + q] + g;
                        b = targetImage.pixelColor(i + p, j + q).blue() * kernel[len + p][len + q] + b;
                    }

                r /= (filterRadius * filterRadius);
                g /= (filterRadius * filterRadius);
                b /= (filterRadius * filterRadius);

                if (((i - len) >= 0) && ((i - len) < originWidth) && ((j - len) >= 0) && ((j - len) < originHeight))
                    originImage->setPixel(i - len, j - len, qRgb(r, g, b));
            }
    }

    return (*originImage);
} // averageFiltering

// QImage Smooth::medianFiltering(QImage *originImage)
// {
// bool ok;
// int filterRadius = QInputDialog::getInt(nullptr, tr("中值滤波"), "输入滤波器大小(1~30)", 3, 1, 30, 1, &ok);
// if (ok)
// {
//     int width = originImage->width();
//     int height = originImage->height();

//     // * originImage, filterRadius

// }
// } // medianFiltering
