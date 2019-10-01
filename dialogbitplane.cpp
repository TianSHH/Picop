#include "dialogbitplane.h"

DialogBitPlane::DialogBitPlane(QWidget *parent) : QDialog(parent)
{
    setup();
    setAttribute(Qt::WA_DeleteOnClose);
}

DialogBitPlane::~DialogBitPlane()
{
}

void DialogBitPlane::setup()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("this"));

    this->resize(800, 600);

    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    graphicsViewBitPlane7 = new QGraphicsView(this);
    graphicsViewBitPlane7->setObjectName(QStringLiteral("graphicsViewBitPlane7"));
    gridLayout->addWidget(graphicsViewBitPlane7, 0, 0, 1, 1);

    graphicsViewBitPlane6 = new QGraphicsView(this);
    graphicsViewBitPlane6->setObjectName(QStringLiteral("graphicsViewBitPlane6"));
    gridLayout->addWidget(graphicsViewBitPlane6, 0, 1, 1, 1);

    graphicsViewBitPlane5 = new QGraphicsView(this);
    graphicsViewBitPlane5->setObjectName(QStringLiteral("graphicsViewBitPlane5"));
    gridLayout->addWidget(graphicsViewBitPlane5, 0, 2, 1, 1);

    graphicsViewBitPlane4 = new QGraphicsView(this);
    graphicsViewBitPlane4->setObjectName(QStringLiteral("graphicsViewBitPlane4"));
    gridLayout->addWidget(graphicsViewBitPlane4, 0, 3, 1, 1);

    graphicsViewBitPlane3 = new QGraphicsView(this);
    graphicsViewBitPlane3->setObjectName(QStringLiteral("graphicsViewBitPlane3"));
    gridLayout->addWidget(graphicsViewBitPlane3, 1, 0, 1, 1);

    graphicsViewBitPlane2 = new QGraphicsView(this);
    graphicsViewBitPlane2->setObjectName(QStringLiteral("graphicsViewBitPlane2"));
    gridLayout->addWidget(graphicsViewBitPlane2, 1, 1, 1, 1);

    graphicsViewBitPlane1 = new QGraphicsView(this);
    graphicsViewBitPlane1->setObjectName(QStringLiteral("graphicsViewBitPlane1"));
    gridLayout->addWidget(graphicsViewBitPlane1, 1, 2, 1, 1);

    graphicsViewBitPlane0 = new QGraphicsView(this);
    graphicsViewBitPlane0->setObjectName(QStringLiteral("graphicsViewBitPlane0"));
    gridLayout->addWidget(graphicsViewBitPlane0, 1, 3, 1, 1);

    graphicsSceneBitPlane0 = new QGraphicsScene;
    graphicsSceneBitPlane1 = new QGraphicsScene;
    graphicsSceneBitPlane2 = new QGraphicsScene;
    graphicsSceneBitPlane3 = new QGraphicsScene;
    graphicsSceneBitPlane4 = new QGraphicsScene;
    graphicsSceneBitPlane5 = new QGraphicsScene;
    graphicsSceneBitPlane6 = new QGraphicsScene;
    graphicsSceneBitPlane7 = new QGraphicsScene;

    graphicsItem0 = new QGraphicsPixmapItem();
    graphicsItem1 = new QGraphicsPixmapItem();
    graphicsItem2 = new QGraphicsPixmapItem();
    graphicsItem3 = new QGraphicsPixmapItem();
    graphicsItem4 = new QGraphicsPixmapItem();
    graphicsItem5 = new QGraphicsPixmapItem();
    graphicsItem6 = new QGraphicsPixmapItem();
    graphicsItem7 = new QGraphicsPixmapItem();

    graphicsSceneBitPlane0->setBackgroundBrush(QColor::fromRgb(224, 224, 224));
    graphicsViewBitPlane0->setScene(graphicsSceneBitPlane0);

    graphicsSceneBitPlane1->setBackgroundBrush(QColor::fromRgb(224, 224, 224));
    graphicsViewBitPlane1->setScene(graphicsSceneBitPlane1);

    graphicsSceneBitPlane2->setBackgroundBrush(QColor::fromRgb(224, 224, 224));
    graphicsViewBitPlane2->setScene(graphicsSceneBitPlane2);

    graphicsSceneBitPlane3->setBackgroundBrush(QColor::fromRgb(224, 224, 224));
    graphicsViewBitPlane3->setScene(graphicsSceneBitPlane3);

    graphicsSceneBitPlane4->setBackgroundBrush(QColor::fromRgb(224, 224, 224));
    graphicsViewBitPlane4->setScene(graphicsSceneBitPlane4);

    graphicsSceneBitPlane5->setBackgroundBrush(QColor::fromRgb(224, 224, 224));
    graphicsViewBitPlane5->setScene(graphicsSceneBitPlane5);

    graphicsSceneBitPlane6->setBackgroundBrush(QColor::fromRgb(224, 224, 224));
    graphicsViewBitPlane6->setScene(graphicsSceneBitPlane6);

    graphicsSceneBitPlane7->setBackgroundBrush(QColor::fromRgb(224, 224, 224));
    graphicsViewBitPlane7->setScene(graphicsSceneBitPlane7);

    QMetaObject::connectSlotsByName(this);
} // setup

void DialogBitPlane::displayBitPlane(QImage *originImage)
{
    int width = originImage->width();
    int height = originImage->height();

    QImage newImage0(width, height, QImage::Format_RGB888);
    QImage newImage1(width, height, QImage::Format_RGB888);
    QImage newImage2(width, height, QImage::Format_RGB888);
    QImage newImage3(width, height, QImage::Format_RGB888);
    QImage newImage4(width, height, QImage::Format_RGB888);
    QImage newImage5(width, height, QImage::Format_RGB888);
    QImage newImage6(width, height, QImage::Format_RGB888);
    QImage newImage7(width, height, QImage::Format_RGB888);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            QColor color = QColor(originImage->pixel(i, j));
            int gray = color.red();
            QString binary = QString::number(gray, 2);

            { // 最低层
                int bit = gray & 0x1;
                if (bit == 1)
                    newImage7.setPixel(i, j, qRgb(255, 255, 255));
                else
                    newImage7.setPixel(i, j, qRgb(0, 0, 0));
            }

            {
                int bit = gray & 0x2;
                if (bit == 0x2)
                    newImage6.setPixel(i, j, qRgb(255, 255, 255));
                else
                    newImage6.setPixel(i, j, qRgb(0, 0, 0));
            }

            {
                int bit = gray & 0x4;
                if (bit == 0x4)
                    newImage5.setPixel(i, j, qRgb(255, 255, 255));
                else
                    newImage5.setPixel(i, j, qRgb(0, 0, 0));
            }

            {
                int bit = gray & 0x8;
                if (bit == 0x8)
                    newImage4.setPixel(i, j, qRgb(255, 255, 255));
                else
                    newImage4.setPixel(i, j, qRgb(0, 0, 0));
            }

            {
                int bit = gray & 0x10;
                if (bit == 0x10)
                    newImage3.setPixel(i, j, qRgb(255, 255, 255));
                else
                    newImage3.setPixel(i, j, qRgb(0, 0, 0));
            }

            {
                int bit = gray & 0x20;
                if (bit == 0x20)
                    newImage2.setPixel(i, j, qRgb(255, 255, 255));
                else
                    newImage2.setPixel(i, j, qRgb(0, 0, 0));
            }

            {
                int bit = gray & 0x40;
                if (bit == 0x40)
                    newImage1.setPixel(i, j, qRgb(255, 255, 255));
                else
                    newImage1.setPixel(i, j, qRgb(0, 0, 0));
            }

            { // 最高层
                int bit = gray & 0x80;
                if (bit == 0x80)
                    newImage0.setPixel(i, j, qRgb(255, 255, 255));
                else
                    newImage0.setPixel(i, j, qRgb(0, 0, 0));
            }
        }
    }
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "显示位平面";

    graphicsItem0 = graphicsSceneBitPlane0->addPixmap(QPixmap::fromImage(newImage0));
    graphicsItem1 = graphicsSceneBitPlane1->addPixmap(QPixmap::fromImage(newImage1));
    graphicsItem2 = graphicsSceneBitPlane2->addPixmap(QPixmap::fromImage(newImage2));
    graphicsItem3 = graphicsSceneBitPlane3->addPixmap(QPixmap::fromImage(newImage3));
    graphicsItem4 = graphicsSceneBitPlane4->addPixmap(QPixmap::fromImage(newImage4));
    graphicsItem5 = graphicsSceneBitPlane5->addPixmap(QPixmap::fromImage(newImage5));
    graphicsItem6 = graphicsSceneBitPlane6->addPixmap(QPixmap::fromImage(newImage6));
    graphicsItem7 = graphicsSceneBitPlane7->addPixmap(QPixmap::fromImage(newImage7));
} // displayBitPlane
