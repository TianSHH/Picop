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

    this->setFixedSize(606, 410);
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
    width = originImage->width();
    height = originImage->height();
    totalPixel = width * height;

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
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setPen(Qt::black);

    drawHistogram(xBase, yBase, widthHistogram, heightHistogram, grayHistogram);

    drawHistogram(xBase + dist + widthHistogram, yBase, widthHistogram, heightHistogram, redHistogram);

    drawHistogram(xBase, yBase + dist + heightHistogram, widthHistogram, heightHistogram, greenHistogram);

    drawHistogram(xBase + dist + widthHistogram, yBase + dist + heightHistogram, widthHistogram, heightHistogram, blueHistogram);
} // paintEvent

void DialogHistogram::drawHistogram(int xBase, int yBase, int widthHistogram, int heightHistogram, int *histogram)
{
    QPainter painter(this);

    float max = histogram[256];

    painter.setPen(Qt::gray);
    painter.drawRect(xBase, yBase - heightHistogram, widthHistogram, heightHistogram);

    for (int i = 0; i < 256; i++)
        painter.drawLine(xBase + 1 + i, yBase, xBase + 1 + i, yBase - (float)(heightMaxLine / max) * (float)histogram[i]);

} // drawHistogram
