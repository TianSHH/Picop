#include "dialoghistogram.h"
#include <stdio.h>

DialogHistogram::DialogHistogram(QWidget *parent) : QDialog(parent)
{
    setup();
    setAttribute(Qt::WA_DeleteOnClose);
}

DialogHistogram::~DialogHistogram()
{
}

void DialogHistogram::setup()
{
    init();

    this->setFixedSize(60 + widthRect + distH, 60 + heightRect + distV);
    this->setWindowTitle("直方图 - Picop");
} // setup

void DialogHistogram::init()
{
    for (int i = 0; i < 256; i++)
    {
        grayHistogram[i] = 0;
        redHistogram[i] = 0;
        greenHistogram[i] = 0;
        blueHistogram[i] = 0;
    }
} // init

void DialogHistogram::displayHistogram(QImage *originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "显示直方图";

    getImageInfo(originImage);
} // displayHistogram

QImage *DialogHistogram::histogramEqualization(QImage *originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "直方图均衡化";

    getImageInfo(originImage);

    // step1
    // 计算初始各像素级所占图像总像素百分比

    double grayHs[256];
    double redHs[256];
    double greenHs[256];
    double blueHs[256];

    for (int i = 0; i <= 255; i++)
    {
        grayHs[i] = grayHistogram[i];
        redHs[i] = redHistogram[i];
        greenHs[i] = greenHistogram[i];
        blueHs[i] = blueHistogram[i];
    }

    // step2
    // 计算各像素级的累计分布概率

    // 各像素级的累计分布概率
    double grayHp[256];
    double redHp[256];
    double greenHp[256];
    double blueHp[256];

    grayHp[0] = grayHs[0];
    redHp[0] = redHs[0];
    greenHp[0] = greenHs[0];
    blueHp[0] = blueHs[0];

    for (int i = 1; i <= 255; i++)
    {
        grayHp[i] = grayHp[i - 1] + grayHs[i];
        redHp[i] = redHp[i - 1] + redHs[i];
        greenHp[i] = greenHp[i - 1] + greenHs[i];
        blueHp[i] = blueHp[i - 1] + blueHs[i];
    }

    // step3
    // 计算新的调色板索引值

    // 新调色板索引值
    double newIndexGrayHs[256];
    double newIndexRedHs[256];
    double newIndexGreenHs[256];
    double newIndexBlueHs[256];

    for (int i = 0; i <= 255; i++)
    {
        newIndexGrayHs[i] = (int)(255 * grayHp[i] + 0.5);
        newIndexRedHs[i] = (int)(255 * redHp[i] + 0.5);
        newIndexGreenHs[i] = (int)(255 * greenHp[i] + 0.5);
        newIndexBlueHs[i] = (int)(255 * blueHp[i] + 0.5);
    }

    // step4
    // 将老的索引值对应的概率合并, 作为对应的新的索引值的概率

    for (int i = 0; i <= width; i++)
    {
        for (int j = 0; j <= height; j++)
        {
            int gray = qGray(originImage->pixel(i, j));
            int red = qRed(originImage->pixel(i, j));
            int green = qGreen(originImage->pixel(i, j));
            int blue = qBlue(originImage->pixel(i, j));

            gray = newIndexGrayHs[gray];
            red = newIndexRedHs[red];
            green = newIndexGreenHs[green];
            blue = newIndexBlueHs[blue];

            originImage->setPixel(i, j, qRgb(red, green, blue));
        }
    }

    return originImage;
} // histogramEqualization

void DialogHistogram::paintEvent(QPaintEvent *event)
{
    // 去掉警告, 很烦
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(Qt::black);

    drawHistogram(xBaseRect, yBaseRect, grayHistogram, Qt::gray);
    drawHistogram(xBaseRect + distH, yBaseRect, redHistogram, Qt::red);
    drawHistogram(xBaseRect, yBaseRect + distV, greenHistogram, Qt::green);
    drawHistogram(xBaseRect + distH, yBaseRect + distV, blueHistogram, Qt::blue);
} // paintEvent

void DialogHistogram::drawHistogram(int xBaseRect, int yBaseRect, double *histogram, QColor color)
{
    QPainter painter(this);
    painter.setPen(Qt::black);

    if (color == Qt::gray)
        painter.drawText(xBaseRect + 20, yBaseRect + 5, "灰度通道"); // 一个汉字的高为 10, 宽为 15
    else if (color == Qt::red)
        painter.drawText(xBaseRect + 20, yBaseRect + 5, "红色通道");
    else if (color == Qt::green)
        painter.drawText(xBaseRect + 20, yBaseRect + 5, "绿色通道");
    else
        painter.drawText(xBaseRect + 20, yBaseRect + 5, "蓝色通道");

    // 直方图初始坐标, 原点在左下方
    int xBaseHistogram = xBaseRect + paddingLeft;
    int yBaseHistogram = yBaseRect + paddingUp + heightHistogram;
    double max = histogram[256];

    painter.setPen(color);
    for (int i = 0; i < 256; i++)
        painter.drawLine(xBaseHistogram + 1 + i, yBaseHistogram, xBaseHistogram + 1 + i, yBaseHistogram - (heightMaxLine / max) * histogram[i]);
    // 使用长度为 (float)(heightMaxLine / max) * (float)histogram[i]) 的直线代表灰度值 i 的出现频率
    // 为了完整显示直方图, 使出现频率最多的像素值作为直方图中的最高点

    // 绘制直方图数据
    painter.setPen(Qt::black);
    painter.drawText(xBaseHistogram + 15, yBaseHistogram + 25, "平均色度");
    painter.drawText(xBaseHistogram + 15, yBaseHistogram + 50, "中值色度");
    painter.drawText(xBaseHistogram + 15, yBaseHistogram + 75, "色度标准差");

    painter.drawText(xBaseHistogram + 100, yBaseHistogram + 25, getMean(histogram));
    painter.drawText(xBaseHistogram + 100, yBaseHistogram + 50, getMedian(histogram));
    painter.drawText(xBaseHistogram + 100, yBaseHistogram + 75, getSD(histogram));

    // 绘制直方图边框
    painter.setPen(Qt::gray);
    painter.drawLine(xBaseRect, yBaseRect, xBaseRect, yBaseRect + heightRect);                          // left
    painter.drawLine(xBaseRect, yBaseRect, xBaseRect + 10, yBaseRect);                                  // up
    painter.drawLine(xBaseRect + 90, yBaseRect, xBaseRect + widthRect, yBaseRect);                      // up
    painter.drawLine(xBaseRect + widthRect, yBaseRect, xBaseRect + widthRect, yBaseRect + heightRect);  // right
    painter.drawLine(xBaseRect, yBaseRect + heightRect, xBaseRect + widthRect, yBaseRect + heightRect); // buttom

    painter.drawRect(xBaseRect + paddingLeft, yBaseRect + paddingUp, widthHistogram, heightHistogram);
} // drawHistogram

void DialogHistogram::getImageInfo(QImage *originImage)
{
    width = originImage->width();
    height = originImage->height();
    totalPixel = width * height;

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
        {
            int grayValue = qGray(originImage->pixel(i, j));
            int redValue = qRed(originImage->pixel(i, j));
            int greenValue = qGreen(originImage->pixel(i, j));
            int blueValue = qBlue(originImage->pixel(i, j));

            grayHistogram[grayValue]++;
            redHistogram[redValue]++;
            greenHistogram[greenValue]++;
            blueHistogram[blueValue]++;
        }

    /* **********************************************************
     * 把 grayHistogram 从存储各像素级出现的次数变为存储各像素级出现的频率,
     * 这样做对于画直方图无性能提升, 但对于直方图均衡化处理有好处,
     * 原因是: 直方图均衡化最后的结果用 grayHistogram 存储结果即各像素级
     * 出现的概率顺其自然, 这里将 grayHistogram 存储的内容和
     * drawHistogram() 稍作修改就可以避免在 histogramEqulization() 中创建
     * 新数组存储结果, 并将结果转化为各像素级出现次数的麻烦.
     * *********************************************************/

    for (int i = 0; i <= 255; i++)
    {
        grayHistogram[i] /= (double)totalPixel;
        redHistogram[i] /= (double)totalPixel;
        greenHistogram[i] /= (double)totalPixel;
        blueHistogram[i] /= (double)totalPixel;
    }

    for (int i = 0; i < 256; i++)
    {
        // 获取各像素级出现频率最多的像素的出现频率
        if (grayHistogram[256] < grayHistogram[i])
            grayHistogram[256] = grayHistogram[i];

        if (redHistogram[256] < redHistogram[i])
            redHistogram[256] = redHistogram[i];

        if (greenHistogram[256] < greenHistogram[i])
            greenHistogram[256] = greenHistogram[i];

        if (blueHistogram[256] < blueHistogram[i])
            blueHistogram[256] = blueHistogram[i];
    }
}

QString DialogHistogram::getMean(double *histogram)
{
    int sum = 0;

    for (int i = 0; i < 256; i++)
        sum += (i * histogram[i] * totalPixel);

    QString res = QString::number((int)(sum / totalPixel), 10);

    return res;
} // getAverage

QString DialogHistogram::getMedian(double *histogram)
{
    // index 126 127
    int sum = 0;
    int left = 0;
    int right = 0;

    for (int i = 0; i < 256; i++)
    {
        sum += (histogram[i] * totalPixel);
        if (sum >= 126)
            left = i;
        if (sum >= 127)
        {
            right = i;
            break;
        }
    }

    QString res = QString::number((int)((left + right) / 2), 10);

    return res;
} // getMedian

QString DialogHistogram::getSD(double *histogram)
{
    int mean = getMean(histogram).toInt();

    double d = 0; // 方差

    for (int i = 0; i < 256; i++)
        d += ((i - mean) * (i - mean) * histogram[i]);

    QString res = QString::number((int)((sqrt(d))), 10, 4);

    return res;
} // getSD
