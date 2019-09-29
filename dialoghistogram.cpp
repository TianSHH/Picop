#include "dialoghistogram.h"

DialogHistogram::DialogHistogram(QWidget *parent) : QLabel(parent)
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
}

DialogHistogram::DialogHistogram(QWidget *parent, DialogHistogram *histogram) : QLabel(parent)
{
    for (int i = 0; i < 258; i++)
    {
        bwHistogram[i] = histogram->bwHistogram[i];
        redHistogram[i] = histogram->redHistogram[i];
        greenHistogram[i] = histogram->greenHistogram[i];
        blueHistogram[i] = histogram->blueHistogram[i];
    }

    bwHistogram[258] = histogram->bwHistogram[258];
}

void DialogHistogram::computeHistogram(QImage img)
{
    if (!img.isNull())
    {
        for (int i = 0; i < img.height(); i++)
        {
            for (int j = 0; j < img.width(); j++)
            {
                int bwValue = qGray(img.pixel(j, i));

                int redValue = qRed(img.pixel(j, i));
                int greenValue = qGreen(img.pixel(j, i));
                int blueValue = qBlue(img.pixel(j, i));

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
}

void DialogHistogram::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    int dist = 100;              // 直方图之间的距离
    int height = 255 + 10;       // 直方图高度
    int xBase = 99;              // 第一个直方图原点的 x 坐标
    int yBase = 30 + height + 1; // 第一个直方图原点的 y 坐标

    QPainter painter(this);
    painter.setPen(Qt::black);

    if (bwHistogram[256] != -1)
        drawBwHistogram(xBase, yBase, height);
    else
        painter.drawText(xBase, yBase - height / 2 + 5, tr("Can not load the gray level histogram."));
}

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

    painter.drawText(xBase + 40, yBase - height - 10, tr("GRAY LEVELS HISTOGRAM"));

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
}
