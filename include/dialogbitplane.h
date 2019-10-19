#ifndef DIALOGBITPLANE_H
#define DIALOGBITPLANE_H

#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>

class DialogBitPlane : public QDialog
{
    Q_OBJECT

public:
    explicit DialogBitPlane(QWidget *parent = nullptr);
    ~DialogBitPlane();

public:
    QGridLayout *gridLayout;

    QGraphicsView *graphicsViewBitPlane0;
    QGraphicsView *graphicsViewBitPlane1;
    QGraphicsView *graphicsViewBitPlane2;
    QGraphicsView *graphicsViewBitPlane3;
    QGraphicsView *graphicsViewBitPlane4;
    QGraphicsView *graphicsViewBitPlane5;
    QGraphicsView *graphicsViewBitPlane6;
    QGraphicsView *graphicsViewBitPlane7;

    QGraphicsScene *graphicsSceneBitPlane0;
    QGraphicsScene *graphicsSceneBitPlane1;
    QGraphicsScene *graphicsSceneBitPlane2;
    QGraphicsScene *graphicsSceneBitPlane3;
    QGraphicsScene *graphicsSceneBitPlane4;
    QGraphicsScene *graphicsSceneBitPlane5;
    QGraphicsScene *graphicsSceneBitPlane6;
    QGraphicsScene *graphicsSceneBitPlane7;

    QGraphicsPixmapItem *graphicsItem0;
    QGraphicsPixmapItem *graphicsItem1;
    QGraphicsPixmapItem *graphicsItem2;
    QGraphicsPixmapItem *graphicsItem3;
    QGraphicsPixmapItem *graphicsItem4;
    QGraphicsPixmapItem *graphicsItem5;
    QGraphicsPixmapItem *graphicsItem6;
    QGraphicsPixmapItem *graphicsItem7;

public:
    void setup();
    void displayBitPlane(QImage *originImage);
};

#endif // DIALOGBITPLANE_H
