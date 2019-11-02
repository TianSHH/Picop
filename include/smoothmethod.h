#ifndef SMOOTHMETHOD_H
#define SMOOTHMETHOD_H

#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QObject>
#include <QtCore/QVariant>
#include <QtGui/QValidator>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QRadioButton>
#include <opencv4/opencv2/core/core.hpp>
#include <opencv4/opencv2/highgui/highgui.hpp>
#include <opencv4/opencv2/imgproc/imgproc.hpp>

class SmoothMethod
{
public:
    SmoothMethod();
    ~SmoothMethod();

public:
    QImage averageFiltering(QImage *originImage);
    QImage medianFiltering(QImage *originImage);
    QImage KNNF(QImage originImage);
    QImage KNNMF(QImage *originImage);

    int getMedianValue(const int *histogram, int threshold);
    int getKValue(const int *histogram, int key, int K);
    int getAverage(const int *arr, int len);
};

#endif // SMOOTHMETHOD_H
