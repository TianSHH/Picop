#include "smoothmethod.h"

SmoothMethod::SmoothMethod()
{
}

SmoothMethod::~SmoothMethod()
{
}

QImage SmoothMethod::averageFiltering(QImage *originImage)
{
    bool ok;
    int filterRadius = QInputDialog::getInt(nullptr, QObject::tr("均值滤波"), "输入滤波器大小(1~30)", 3, 1, 30, 1, &ok);
    if (ok)
    {
        if (filterRadius % 2 == 0)
            filterRadius += 1;

        qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                           << "图像平滑, 方式, 均值滤波"
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

QImage SmoothMethod::medianFiltering(QImage *originImage)
{ // originImage 格式为 Format_RGB32
    bool ok;

    int filterRadius = QInputDialog::getInt(nullptr, QObject::tr("均值滤波"), "输入滤波器大小(1~30)", 3, 1, 30, 1, &ok);

    if (ok)
    {
        if (filterRadius % 2 == 0)
            filterRadius += 1;

        qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                           << "图像平滑, 方式, 均值滤波"
                           << "滤波器大小" << filterRadius;

        int len = filterRadius / 2;
        int threshold = filterRadius * filterRadius / 2 + 1;

        int originWidth = originImage->width();
        int originHeight = originImage->height();

        QImage middleImage = QImage(originWidth + 2 * len, originHeight + 2 * len, QImage::Format_RGB32);
        QImage targetImage = QImage(originWidth, originHeight, QImage::Format_RGB32);

        // 初始化 middleImage
        for (int i = 0; i < middleImage.width(); i++)
        {
            for (int j = 0; j < middleImage.height(); j++)
            {
                if ((i >= len) && (i < (middleImage.width() - len)) && (j >= len) && (j < (middleImage.height() - len)))
                { // 像素点不在边框中
                    middleImage.setPixelColor(i, j, QColor(originImage->pixel(i - len, j - len)));
                }
                else
                { // 像素点在边框中
                    middleImage.setPixelColor(i, j, Qt::white);
                }
            }
        }

        // 使用直方图记录窗口中出现的像素的出现次数
        int redHist[256] = {0};
        int greenHist[256] = {0};
        int blueHist[256] = {0};
        int grayHist[256] = {0};

        for (int i = len; i < middleImage.width() - len; i++)
        {
            for (int j = len; j < middleImage.height() - len; j++)
            {
                if (j == len)
                { // 每到新的一列, 初始化直方图
                    memset(redHist, 0, sizeof(redHist));
                    memset(redHist, 0, sizeof(greenHist));
                    memset(redHist, 0, sizeof(blueHist));
                    memset(redHist, 0, sizeof(grayHist));

                    for (int p = -len; p <= len; p++)
                    {
                        for (int q = -len; q <= len; q++)
                        {
                            int red = qRed(middleImage.pixel(i + p, j + q));
                            int green = qGreen(middleImage.pixel(i + p, j + q));
                            int blue = qBlue(middleImage.pixel(i + p, j + q));
                            int gray = qGray(middleImage.pixel(i + p, j + q));

                            redHist[red]++;
                            greenHist[green]++;
                            blueHist[blue]++;
                            grayHist[gray]++;
                        }
                    }
                }
                else
                { // 列数增加, 窗口按列向下移动, 添加一行窗口像素, 减去一行窗口像素
                    int oldWindowStartCol = j - len - 1;
                    int newWindowEndCol = j + len;

                    for (int p = -len; p <= len; p++)
                    {
                        // 要减去的列的像素值, 从窗口上到窗口下, 即 [j-len,j+len]
                        int red = qRed(middleImage.pixel(i + p, oldWindowStartCol));
                        int green = qGreen(middleImage.pixel(i + p, oldWindowStartCol));
                        int blue = qBlue(middleImage.pixel(i + p, oldWindowStartCol));
                        int gray = qGray(middleImage.pixel(i + p, oldWindowStartCol));

                        redHist[red]--;
                        greenHist[green]--;
                        blueHist[blue]--;
                        grayHist[gray]--;

                        red = qRed(middleImage.pixel(i + p, newWindowEndCol));
                        green = qGreen(middleImage.pixel(i + p, newWindowEndCol));
                        blue = qBlue(middleImage.pixel(i + p, newWindowEndCol));
                        gray = qGray(middleImage.pixel(i + p, newWindowEndCol));

                        redHist[red]++;
                        greenHist[green]++;
                        blueHist[blue]++;
                        grayHist[gray]++;
                    }
                }

                int newRed = getMedianValue(redHist, threshold);
                int newGreen = getMedianValue(greenHist, threshold);
                int newBlue = getMedianValue(blueHist, threshold);

                targetImage.setPixelColor(i - len, j - len, qRgb(newRed, newGreen, newBlue));
            }
        }

        return targetImage;
    }
} // medianFiltering

int SmoothMethod::getMedianValue(const int *histogram, int threshold)
{
    int sum = 0;
    for (int i = 0; i < 256; i++)
    {
        sum += histogram[i];
        if (sum >= threshold)
            return i;
    }
    return 255;
} // getMedianValue
