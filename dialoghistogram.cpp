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

    this->resize(800, 800);

    this->setWindowTitle("直方图 - Picop");
} // setup

void DialogHistogram::init()
{
    for (int i = 0; i < 256; i++)
    {
        bwHistogram[i] = 0;
        redHistogram[i] = 0;
        greenHistogram[i] = 0;
        blueHistogram[i] = 0;
    }

    bwHistogram[256] = -1;
    redHistogram[256] = -1;
    greenHistogram[256] = -1;
    blueHistogram[256] = -1;

    redHistogram[257] = 0;
    greenHistogram[257] = 0;
    blueHistogram[257] = 0;

    bwHistogram[257] = 0;
    bwHistogram[258] = 0;
} // init

void DialogHistogram::displayHistogram(QImage *originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "显示直方图";

    if (!originImage->isNull())
    {
        for (int i = 0; i < originImage->height(); i++)
        {
            for (int j = 0; j < originImage->width(); j++)
            {
                int bwValue = qGray(originImage->pixel(j, i));

                int redValue = qRed(originImage->pixel(j, i));
                int greenValue = qGreen(originImage->pixel(j, i));
                int blueValue = qBlue(originImage->pixel(j, i));

                bwHistogram[bwValue]++;
                redHistogram[redValue]++;
                greenHistogram[greenValue]++;
                blueHistogram[blueValue]++;
            }
        }

        for (int i = 0; i < 256; i++)
        {
            // maximum values
            if (bwHistogram[256] < bwHistogram[i])
                bwHistogram[256] = bwHistogram[i];

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
                bwHistogram[257] += (127 - i) * bwHistogram[i];
            else
                bwHistogram[258] += (i - 127) * bwHistogram[i];
        }
    }
} // displayHistogram

void DialogHistogram::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int dist = 100;              // 直方图之间的距离
    int height = 255 + 10;       // 直方图高度
    int xBase = 99;              // 第一个直方图原点的 x 坐标
    int yBase = 30 + height + 1; // 第一个直方图原点的 y 坐标

    QPainter painter(this);
    painter.setPen(Qt::black);

    // 灰度直方图
    if (bwHistogram[256] != -1)
        drawBwHistogram(xBase, yBase, height);
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

void DialogHistogram::drawBwHistogram(int xBase, int yBase, int height)
{
    QPainter painter(this);
    painter.setPen(Qt::darkGray);

    float max = bwHistogram[256];

    if (max < redHistogram[256])
        max = redHistogram[256];

    if (max < greenHistogram[256])
        max = greenHistogram[256];

    if (max < blueHistogram[256])
        max = blueHistogram[256];

    //
    for (int i = 0; i < 256; i++)
    {
        painter.drawLine(xBase + 1 + i, yBase, xBase + 1 + i, yBase - (float)(256.0 / max) * (float)bwHistogram[i]);
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
} // drawBwHistogram

void DialogHistogram::drawRedHistogram(int xBase, int yBase, int height)
{
    QPainter painter(this);

    painter.setPen(Qt::darkRed);

    float max = bwHistogram[256];

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
}

void DialogHistogram::drawGreenHistogram(int xBase, int yBase, int height)
{
    QPainter painter(this);

    painter.setPen(Qt::darkGreen);

    float max = bwHistogram[256];

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
}

void DialogHistogram::drawBlueHistogram(int xBase, int yBase, int height)
{
    QPainter painter(this);

    painter.setPen(Qt::darkBlue);

    float max = bwHistogram[256];

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
}

int DialogHistogram::getBwHistogram(int index)
{
    if (index >= 0 && index <= 258)
        return bwHistogram[index];
    else
        return -2;
} // getBwHistogram

int DialogHistogram::getRedHistogram(int index)
{
    if (index >= 0 && index <= 257)
        return redHistogram[index];
    else
        return -2;
}

int DialogHistogram::getGreenHistogram(int index)
{
    if (index >= 0 && index <= 257)
        return greenHistogram[index];
    else
        return -2;
}

int DialogHistogram::getBlueHistogram(int index)
{
    if (index >= 0 && index <= 257)
        return blueHistogram[index];
    else
        return -2;
}
