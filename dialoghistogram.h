#ifndef DIALOGHISTOGRAM_H
#define DIALOGHISTOGRAM_H

#include <QColor>
#include <QImage>
#include <QPainter>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <cmath>
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

    // 容纳直方图和相关信息的矩形框初始坐标, 原点在左上方
    int xBaseRect = 30; // 第一个直方图矩形框 x 坐标
    int yBaseRect = 30; // 第一个直方图矩形框 y 坐标

    int paddingUp = 20;     // 矩形框上内边距
    int paddingLeft = 15;   // 矩形框左内边距
    int paddingRight = 15;  // 矩形框右内边距
    int paddingBottom = 90; // 矩形框下内边距

    int widthRect = paddingLeft + widthHistogram + paddingRight;
    int heightRect = paddingUp + heightHistogram + paddingBottom;

    int distH = widthRect + 30;  // 直方图之间的水平距离
    int distV = heightRect + 30; // 直方图之间的竖直距离

    int width;
    int height;
    int totalPixel;

public:
    void setup();
    void init();

    void displayHistogram(QImage *originImage);

    void paintEvent(QPaintEvent *e);

    void drawHistogram(int xBaseRect, int yBaseRect, int *histogram, QColor color);

    QString getMean(int *histogram);
    QString getMedian(int *histogram);
    QString getSD(int *histogram);
};

#endif // DIALOGHISTOGRAM_H
