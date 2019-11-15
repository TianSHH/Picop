#ifndef FILTERMETHOD_H
#define FILTERMETHOD_H

#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore>
#include <QtGui>
#include <QtWidgets/QAbstractItemView>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QTableWidget>

class FilterMethod : public QDialog
{

    Q_OBJECT

public:
    explicit FilterMethod(QWidget *parent = nullptr);
    ~FilterMethod();

public:
    int filterSize;
    int *filterTemplateArray;

public:
    QDialog *_dialog;
    QGridLayout *_gridLayout;
    QTableWidget *kernelTable;
    QDialogButtonBox *buttonBox;
    QMainWindow *ptr = (QMainWindow *)parent();

public:
    void setup();
    void retranslate();

    QImage filtering(QImage originImage, int filterSize, int *filterTemplateArray, bool flag);
    QImage merging(QImage image1, QImage image2);
    QImage adding(QImage image1, QImage image2);

    QImage reborts(QImage originImage);
    QImage sobel(QImage originImage);
    QImage laplacian(QImage originImage);
    QImage enhancedLaplacian(QImage originImage);
    QImage prewitt(QImage originImage);

signals:
    void signalFilterStart();
    void signalFilterEnd(QImage &);

private slots:
    void emitSignalFilterStart();

    void collectKernelInfo(QImage *);
};

#endif // FILTERMETHOD_H
