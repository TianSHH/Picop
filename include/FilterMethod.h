#ifndef FILTERMETHOD_H
#define FILTERMETHOD_H

#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore>
#include <QtGui>
#include <QtWidgets/QAbstractItemView>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTableWidgetItem>
#include <QtWidgets/QWidget>

class FilterMethod
{
public:
    FilterMethod();
    ~FilterMethod();

public:
    int filterSize;
    int *filterTemplateArray;

public:
    QImage filtering(QImage originImage, int filterSize, int *filterTemplateArray);
    void getFilterInfo(QImage originImage);

private slots:
    void collectingKernelInfo(QTableWidget * tableWidget);
};

#endif // FILTERMETHOD_H
