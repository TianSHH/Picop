#ifndef DIALOGSCALING_H
#define DIALOGSCALING_H

#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QVariant>
#include <QtGui/QValidator>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QRadioButton>

class DialogScaling : public QDialog
{
    Q_OBJECT

public:
    explicit DialogScaling(QWidget *parent = nullptr);
    ~DialogScaling();

public:
    QLabel *labelWidthScalingFactor;
    QLabel *labelHeightScalingFactor;

    QDoubleValidator *doubleValidator; // 限制器

    QLineEdit *lineEditWidthScalingFactor;
    QLineEdit *lineEditHeightScalingFactor;

    QRadioButton *radioButton1;
    QRadioButton *radioButton2;

    QDialogButtonBox *buttonBox;

    QGridLayout *gridLayout;

    QMainWindow *ptr = (QMainWindow *)parentWidget();

public:
    double factorX; // 水平方向缩放因子
    double factorY; // 垂直方向缩放因子

    int originWidth;  // 原始图像宽度
    int originHeight; // 原始图像高度

    int targetWidth;  // 目标图像宽度
    int targetHeight; // 目标图像高度

public:
    void setup();
    void retranslate();

    void scalingNNI(QImage *); // 最临近插值
    void scalingBI(QImage *);  // 双线性差值

    void getInfo(QImage *originImage);

signals:
    void signalScalingStart();
    void signalScalingEnd(QImage &);

private slots:
    void emitSignalScalingEnd();

    void Scaling(QImage *originImage);
};

#endif // DIALOGSCALING_H
