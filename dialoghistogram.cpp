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
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "setup";

    init();

    this->resize(800, 800);

    this->setWindowTitle("直方图 - Picop");
} // setup

void DialogHistogram::init()
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "init";

    for (int i = 0; i < 256; i++)
    {
        grayHistogram[i] = 0;
        redHistogram[i] = 0;
        greenHistogram[i] = 0;
        blueHistogram[i] = 0;
    }

    grayHistogram[256] = -1;
    redHistogram[256] = -1;
    greenHistogram[256] = -1;
    blueHistogram[256] = -1;

    redHistogram[257] = 0;
    greenHistogram[257] = 0;
    blueHistogram[257] = 0;

    grayHistogram[257] = 0;
    grayHistogram[258] = 0;
} // init

void DialogHistogram::displayHistogram(QImage *originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "displayHistogram";

    // qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
    //    << "显示直方图";

    int width = originImage->width();
    int height = originImage->height();
    int totalPixel = width * height;

    if (!originImage->isNull())
    {
        for (int i = 0; i < width; i++)
        {
            for (int j = 0; j < height; j++)
            {
                int grayValue = qGray(originImage->pixel(j, i));

                int redValue = qRed(originImage->pixel(j, i));
                int greenValue = qGreen(originImage->pixel(j, i));
                int blueValue = qBlue(originImage->pixel(j, i));

                grayHistogram[grayValue]++;
                redHistogram[redValue]++;
                greenHistogram[greenValue]++;
                blueHistogram[blueValue]++;
            }
        }

        for (int i = 0; i < 256; i++)
        {
            // maximum values
            if (grayHistogram[256] < grayHistogram[i])
                grayHistogram[256] = grayHistogram[i];

            if (redHistogram[256] < redHistogram[i])
                redHistogram[256] = redHistogram[i];

            if (greenHistogram[256] < greenHistogram[i])
                greenHistogram[256] = greenHistogram[i];

            if (blueHistogram[256] < blueHistogram[i])
                blueHistogram[256] = blueHistogram[i];

            // values of colour components
            redHistogram[257] += i * redHistogram[i];
            greenHistogram[257] += i * greenHistogram[i];
            blueHistogram[257] += i * blueHistogram[i];

            // values of dark and light component
            if (i <= 127)
                grayHistogram[257] += (127 - i) * grayHistogram[i];
            else
                grayHistogram[258] += (i - 127) * grayHistogram[i];
        }
    }
} // displayHistogram

void DialogHistogram::paintEvent(QPaintEvent *event)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "paintEvent";

    Q_UNUSED(event);

    int dist = 100;              // 直方图之间的距离
    int height = 255 + 10;       // 直方图高度
    int xBase = 99;              // 第一个直方图原点的 x 坐标
    int yBase = 30 + height + 1; // 第一个直方图原点的 y 坐标

    QPainter painter(this);
    painter.setPen(Qt::black);

    // 灰度直方图
    if (grayHistogram[256] != -1)
        drawGrayHistogram(xBase, yBase, height);
    else
        painter.drawText(xBase, yBase - height / 2 + 5, tr("Can not load the gray level histogram."));

    // red hstgrm
    if (redHistogram[256] != -1)
        drawRedHistogram(xBase + dist + height, yBase, height);
    else
        painter.drawText(xBase + dist + height + 1 - height / 2 + 5, yBase, tr("Can't load the red component histogram."));

    // 显示在第二行
    // green hstgrm
    if (greenHistogram[256] != -1)
        drawGreenHistogram(xBase, yBase + dist + height + 1, height);
    else
        painter.drawText(xBase, yBase + (dist + height + 1), tr("Can't load the green component histogram."));
    // blue hstgrm
    if (blueHistogram[256] != -1)
        drawBlueHistogram(xBase + dist + height, yBase + dist + height + 1, height);
    else
        painter.drawText(xBase + dist + height, yBase + dist + height + 1, tr("Can't load the blue component histogram."));
} // paintEvent

void DialogHistogram::drawGrayHistogram(int xBase, int yBase, int height)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "drawGrayHistogram";

    QPainter painter(this);
    painter.setPen(Qt::darkGray);

    float max = grayHistogram[256];

    if (max < redHistogram[256])
        max = redHistogram[256];

    if (max < greenHistogram[256])
        max = greenHistogram[256];

    if (max < blueHistogram[256])
        max = blueHistogram[256];

    //
    for (int i = 0; i < 256; i++)
    {
        painter.drawLine(xBase + 1 + i, yBase, xBase + 1 + i, yBase - (float)(256.0 / max) * (float)grayHistogram[i]);
    }

    painter.drawText(xBase, yBase + 25, tr("black"));
    painter.drawText(xBase + 220, yBase + 25, tr("white"));
    painter.setPen(Qt::black);

    painter.drawText(xBase + 40, yBase - height - 10, tr("灰度直方图"));

    painter.drawText(xBase + 100, yBase + 15, tr("Intensity"));
    painter.drawText(xBase - 84, yBase - height / 2 + 5, tr("Pixels count"));

    // abscissa
    painter.drawLine(xBase, yBase, xBase + 256 + 1, yBase);
    painter.drawLine(xBase, yBase + 1, xBase + 256 + 1, yBase + 1);

    // left ordinate
    painter.drawLine(xBase, yBase, xBase, yBase - height);
    painter.drawLine(xBase - 1, yBase, xBase - 1, yBase - height);

    // right ordinate
    painter.drawLine(xBase + 256 + 1, yBase, xBase + 256 + 1, yBase - height);
    painter.drawLine(xBase + 256 + 2, yBase, xBase + 256 + 2, yBase - height);

    // left ordinate arrow
    painter.drawLine(xBase, yBase - height, xBase + 4, yBase - height + 7);
    painter.drawLine(xBase - 1, yBase - height, xBase - 1 - 4, yBase - height + 7);

    // right ordinate arrow
    painter.drawLine(xBase + 256 + 1, yBase - height, xBase + 256 + 1 - 4, yBase - height + 7);
    painter.drawLine(xBase + 256 + 2, yBase - height, xBase + 256 + 2 + 4, yBase - height + 7);
} // drawGrayHistogram

void DialogHistogram::drawRedHistogram(int xBase, int yBase, int height)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "drawRedHistogram";

    QPainter painter(this);

    painter.setPen(Qt::darkRed);

    float max = grayHistogram[256];

    if (max < redHistogram[256])
        max = redHistogram[256];

    if (max < greenHistogram[256])
        max = greenHistogram[256];

    if (max < blueHistogram[256])
        max = blueHistogram[256];

    // drawing the histogram
    for (int i = 0; i < 256; i++)
    {
        painter.drawLine(xBase + 1 + i, yBase, xBase + 1 + i,
                         yBase - (float)(256. / max) * (float)redHistogram[i]);
    }

    painter.drawText(xBase, yBase + 25, tr("dark"));
    painter.drawText(xBase + 225, yBase + 25, tr("light"));

    painter.setPen(Qt::black);

    painter.drawText(xBase + 25, yBase - height - 10, tr("RED COMPONENT HISTOGRAM"));

    painter.drawText(xBase + 100, yBase + 15, tr("Intensity"));
    painter.drawText(xBase - 84, yBase - height / 2 + 5, tr("Pixels count"));

    // abscissa
    painter.drawLine(xBase, yBase, xBase + 256 + 1, yBase);
    painter.drawLine(xBase, yBase + 1, xBase + 256 + 1, yBase + 1);

    // left ordinate
    painter.drawLine(xBase, yBase, xBase, yBase - height);
    painter.drawLine(xBase - 1, yBase, xBase - 1, yBase - height);

    // right ordinate
    painter.drawLine(xBase + 256 + 1, yBase, xBase + 256 + 1, yBase - height);
    painter.drawLine(xBase + 256 + 2, yBase, xBase + 256 + 2, yBase - height);

    // left ordinate arrow
    painter.drawLine(xBase, yBase - height, xBase + 4, yBase - height + 7);
    painter.drawLine(xBase - 1, yBase - height, xBase - 1 - 4, yBase - height + 7);

    // right ordinate arrow
    painter.drawLine(xBase + 256 + 1, yBase - height, xBase + 256 + 1 - 4, yBase - height + 7);
    painter.drawLine(xBase + 256 + 2, yBase - height, xBase + 256 + 2 + 4, yBase - height + 7);
} // drawRedHistogram

void DialogHistogram::drawGreenHistogram(int xBase, int yBase, int height)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "drawGreenHistogram";

    QPainter painter(this);

    painter.setPen(Qt::darkGreen);

    float max = grayHistogram[256];

    if (max < redHistogram[256])
        max = redHistogram[256];

    if (max < greenHistogram[256])
        max = greenHistogram[256];

    if (max < blueHistogram[256])
        max = blueHistogram[256];

    // drawing the histogram
    for (int i = 0; i < 256; i++)
    {
        painter.drawLine(xBase + 1 + i, yBase, xBase + 1 + i,
                         yBase - (float)(256. / max) * (float)greenHistogram[i]);
    }

    painter.drawText(xBase, yBase + 25, tr("dark"));
    painter.drawText(xBase + 225, yBase + 25, tr("light"));

    painter.setPen(Qt::black);

    painter.drawText(xBase + 15, yBase - height - 10, tr("GREEN COMPONENT HISTOGRAM"));

    painter.drawText(xBase + 100, yBase + 15, tr("Intensity"));
    painter.drawText(xBase - 84, yBase - height / 2 + 5, tr("Pixels count"));

    // abscissa
    painter.drawLine(xBase, yBase, xBase + 256 + 1, yBase);
    painter.drawLine(xBase, yBase + 1, xBase + 256 + 1, yBase + 1);

    // left ordinate
    painter.drawLine(xBase, yBase, xBase, yBase - height);
    painter.drawLine(xBase - 1, yBase, xBase - 1, yBase - height);

    // right ordinate
    painter.drawLine(xBase + 256 + 1, yBase, xBase + 256 + 1, yBase - height);
    painter.drawLine(xBase + 256 + 2, yBase, xBase + 256 + 2, yBase - height);

    // left ordinate arrow
    painter.drawLine(xBase, yBase - height, xBase + 4, yBase - height + 7);
    painter.drawLine(xBase - 1, yBase - height, xBase - 1 - 4, yBase - height + 7);

    // right ordinate arrow
    painter.drawLine(xBase + 256 + 1, yBase - height, xBase + 256 + 1 - 4, yBase - height + 7);
    painter.drawLine(xBase + 256 + 2, yBase - height, xBase + 256 + 2 + 4, yBase - height + 7);
} // drawGreenHistogram

void DialogHistogram::drawBlueHistogram(int xBase, int yBase, int height)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "drawBleHistogram";

    QPainter painter(this);

    painter.setPen(Qt::darkBlue);

    float max = grayHistogram[256];

    if (max < redHistogram[256])
        max = redHistogram[256];

    if (max < greenHistogram[256])
        max = greenHistogram[256];

    if (max < blueHistogram[256])
        max = blueHistogram[256];

    // drawing the histogram
    for (int i = 0; i < 256; i++)
    {
        painter.drawLine(xBase + 1 + i, yBase, xBase + 1 + i,
                         yBase - (float)(256. / max) * (float)blueHistogram[i]);
    }

    painter.drawText(xBase, yBase + 25, tr("dark"));
    painter.drawText(xBase + 225, yBase + 25, tr("light"));

    painter.setPen(Qt::black);

    painter.drawText(xBase + 20, yBase - height - 10, tr("BLUE COMPONENT HISTOGRAM"));

    painter.drawText(xBase + 100, yBase + 15, tr("Intensity"));
    painter.drawText(xBase - 84, yBase - height / 2 + 5, tr("Pixels count"));

    // abscissa
    painter.drawLine(xBase, yBase, xBase + 256 + 1, yBase);
    painter.drawLine(xBase, yBase + 1, xBase + 256 + 1, yBase + 1);

    // left ordinate
    painter.drawLine(xBase, yBase, xBase, yBase - height);
    painter.drawLine(xBase - 1, yBase, xBase - 1, yBase - height);

    // right ordinate
    painter.drawLine(xBase + 256 + 1, yBase, xBase + 256 + 1, yBase - height);
    painter.drawLine(xBase + 256 + 2, yBase, xBase + 256 + 2, yBase - height);

    // left ordinate arrow
    painter.drawLine(xBase, yBase - height, xBase + 4, yBase - height + 7);
    painter.drawLine(xBase - 1, yBase - height, xBase - 1 - 4, yBase - height + 7);

    // right ordinate arrow
    painter.drawLine(xBase + 256 + 1, yBase - height, xBase + 256 + 1 - 4, yBase - height + 7);
    painter.drawLine(xBase + 256 + 2, yBase - height, xBase + 256 + 2 + 4, yBase - height + 7);
} // drawBlueHistogram

int DialogHistogram::getGrayHistogram(int index)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "getGrayHistogram";

    if (index >= 0 && index <= 258)
        return grayHistogram[index];
    else
        return -2;
} // getBwHistogram

int DialogHistogram::getRedHistogram(int index)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "getRedHistogram";

    if (index >= 0 && index <= 257)
        return redHistogram[index];
    else
        return -2;
} // getRedHistogram

int DialogHistogram::getGreenHistogram(int index)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "getGreenHistogram";

    if (index >= 0 && index <= 257)
        return greenHistogram[index];
    else
        return -2;
} // getGreenHistogram

int DialogHistogram::getBlueHistogram(int index)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "getBlueHistogram";

    if (index >= 0 && index <= 257)
        return blueHistogram[index];
    else
        return -2;
} // getBlueHistogram

// [Debug] 2019-10-01 12:56:16.425 : setup
// [Debug] 2019-10-01 12:56:16.425 : init
// [Debug] 2019-10-01 12:56:16.431 : displayHistogram
// [Debug] 2019-10-01 12:56:16.490 : paintEvent
// [Debug] 2019-10-01 12:56:16.490 : drawGrayHistogram
// [Debug] 2019-10-01 12:56:16.491 : drawRedHistogram
// [Debug] 2019-10-01 12:56:16.492 : drawGreenHistogram
// [Debug] 2019-10-01 12:56:16.492 : drawBleHistogram
