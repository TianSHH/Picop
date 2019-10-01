#ifndef DIALOGHISTOGRAM_H
#define DIALOGHISTOGRAM_H

#include <QImage>
#include <QPainter>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <iostream>
#include <sstream>

class DialogHistogram : public QDialog
{
public:
    DialogHistogram(QWidget *parent);
    ~DialogHistogram();

public:
    // index 0 to 255 => count of image's pixels for this value
    // index 256 => maximum value
    // index 257 => total value of the dark component
    // index 258 => total value of the light component
    int grayHistogram[259];

    // index 0 to 255 => count of image's pixels for this value
    // index 256 => maximum value
    // index 257 => total value of the component
    int redHistogram[258];
    int greenHistogram[258];
    int blueHistogram[258];

    int widthHistogram = 256 + 2;                 // 直方图宽度
    int heightMaxLine = 148;                      // 直方图中最长线的最大高度
    int heightHistogram = heightMaxLine + 10 + 2; // 直方图高度

    int dist = 30;                       // 直方图之间的距离
    int xBase = 30;                       // 第一个直方图原点的 x 坐标
    int yBase = 30 + heightHistogram + 2; // 第一个直方图原点的 y 坐标

    int width;
    int height;
    int totalPixel;

public:
    void setup();
    void init();

    void displayHistogram(QImage *originImage);

    void paintEvent(QPaintEvent *e);

    void drawHistogram(int xBase, int yBase, int width, int height, int *histogram);
};

#endif // DIALOGHISTOGRAM_H
