#ifndef DIALOGLOGTRANS_H
#define DIALOGLOGTRANS_H

#include "qcustomplot.h"
#include <QMainWindow>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QVariant>
#include <QtCore/qglobal.h>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

class DialogLogTrans : public QDialog
{
    Q_OBJECT

public:
    explicit DialogLogTrans(QWidget *parent = nullptr);
    ~DialogLogTrans();

public:
    QCustomPlot *customPlot;
    QDialogButtonBox *buttonBox;
    QDoubleSpinBox *doubleSpinBoxArgA;
    QLabel *labelArgA;
    QGridLayout *gridLayout;
    QMainWindow *ptr = (QMainWindow *)parentWidget();

public:
    void setup();
    void retranslate();
    void paintFunctionImage(double a);

signals:
    void signalLogTransStart();
    void signalLogTransEnd(QImage &);

private slots:
    void on_doubleSpinBoxArgA_valueChanged(double arg);

    void emitSignalLogTransStart();

    void logTrans(QImage *originImage);
};

#endif // !DIALOGLOGTRANS_H
