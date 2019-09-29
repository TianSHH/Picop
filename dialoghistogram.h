#ifndef DIALOGHISTOGRAM_H
#define DIALOGHISTOGRAM_H

#include <QPainter>
#include <QtCore/QDebug>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <iostream>
#include <sstream>

class DialogHistogram : public QLabel
{
public:
    DialogHistogram(QWidget *parent = nullptr);
    DialogHistogram(QWidget *, DialogHistogram *);

    void computeHistogram(QImage img);
    void paintEvent(QPaintEvent *e);
    void drawBwHistogram(int xBase, int yBase, int height);
    void drawRedHistogram(int xBase, int yBase, int height);
    void drawGreenHistogram(int xBase, int yBase, int height);
    void drawBlueHistogram(int xBase, int yBase, int height);
    int getBwHistogram(int index);
    int getRedHistogram(int index);
    int getGreenHistogram(int index);
    int getBlueHistogram(int index);

private:
    // index 0 to 255 => count of image's pixels for this value
    // index 256 => maximum value
    // index 257 => total value of the dark component
    // index 258 => total value of the light component
    int bwHistogram[259];

    // index 0 to 255 => count of image's pixels for this value
    // index 256 => maximum value
    // index 257 => total value of the component
    int redHistogram[258];
    int greenHistogram[258];
    int blueHistogram[258];
};

#endif // DIALOGHISTOGRAM_H
