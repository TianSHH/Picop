#include "dialoghistogram.h"

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

    for (int i = 0; i < 256; i++)
    {
        // 获取出现次数最多的像素的出现次数
        if (grayHistogram[256] < grayHistogram[i])
            grayHistogram[256] = grayHistogram[i];

        if (redHistogram[256] < redHistogram[i])
            redHistogram[256] = redHistogram[i];

        if (greenHistogram[256] < greenHistogram[i])
            greenHistogram[256] = greenHistogram[i];

        if (blueHistogram[256] < blueHistogram[i])
            blueHistogram[256] = blueHistogram[i];
    }
} // displayHistogram

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

void DialogHistogram::drawHistogram(int xBaseRect, int yBaseRect, int *histogram, QColor color)
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
    float max = histogram[256];

    painter.setPen(color);
    for (int i = 0; i < 256; i++)
        painter.drawLine(xBaseHistogram + 1 + i, yBaseHistogram, xBaseHistogram + 1 + i, yBaseHistogram - (float)(heightMaxLine / max) * (float)histogram[i]);
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

QString DialogHistogram::getMean(int *histogram)
{
    int sum = 0;

    for (int i = 0; i < 256; i++)
        sum += (i * histogram[i]);

    QString res = QString::number(sum / totalPixel, 10);

    return res;
} // getAverage

QString DialogHistogram::getMedian(int *histogram)
{
    // index 126 127
    int sum = 0;
    int left = 0;
    int right = 0;

    for (int i = 0; i < 256; i++)
    {
        sum += histogram[i];
        if (sum >= 126)
            left = i;
        if (sum >= 127)
        {
            right = i;
            break;
        }
    }

    QString res = QString::number((left + right) / 2, 10);

    return res;
} // getMedian

QString DialogHistogram::getSD(int *histogram)
{
    int mean = getMean(histogram).toInt();

    double d = 0; // 方差

    for (int i = 0; i < 256; i++)
        d += ((i - mean) * (i - mean) * histogram[i]);

    QString res = QString::number(sqrt(d), 10, 4);

    return res;
} // getSD
