#ifndef DIALOGHISTOGRAM_H
#define DIALOGHISTOGRAM_H

#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QtMath>
#include <QtGui/QColor>
#include <QtGui/QImage>
#include <QtGui/QPainter>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

class DialogHistogram : public QDialog
{

    Q_OBJECT

public:
    DialogHistogram(QWidget *parent);
    ~DialogHistogram();

public:
    // 索引 0 to 255 => 取该值的像素总数
    // 索引 256      => 出现次数最多的像素的出现次数
    double grayHistogram[257];
    double redHistogram[257];
    double greenHistogram[257];
    double blueHistogram[257];

    int widthHistogram = 256 + 2;                 // 直方图宽度
    double heightMaxLine = 148;                   // 直方图中最长线的最大高度
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

    QMainWindow *ptr = (QMainWindow *)parentWidget();

public:
    // 建立
    void setup();
    // 初始化
    void init();
    //
    void displayHistogram(QImage *originImage);
    // 画图事件, 自动触发, 绘制直方图
    void paintEvent(QPaintEvent *e);
    // 绘制直方图
    void drawHistogram(int xBaseRect, int yBaseRect, double *histogram, QColor color);
    // 获取绘制直方图信息
    void getImageInfo(QImage *);
    // 直方图均衡化
    QImage *histogramEqualization(QImage *originImage);
    // 获取平均像素值, 返回类型为 QString 的原因是为了方便使用 QPainter 绘制
    QString getMean(double *histogram);
    // 获取中位数
    QString getMedian(double *histogram);
    // 获取标准差
    QString getSD(double *histogram);

signals:
    void signalHistogramEqulizationEnd(QImage &);
};

#endif // DIALOGHISTOGRAM_H
