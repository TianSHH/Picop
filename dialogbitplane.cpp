#include "dialogbitplane.h"

DialogBitPlane::DialogBitPlane(QWidget *parent) : QMainWindow(parent)
{
    setup();
}

DialogBitPlane::~DialogBitPlane()
{
}

void DialogBitPlane::setup()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("this"));

    this->resize(800, 600);

    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));

    gridLayout = new QGridLayout(centralWidget);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    graphicsViewBitPlane0 = new QGraphicsView(centralWidget);
    graphicsViewBitPlane0->setObjectName(QStringLiteral("graphicsViewBitPlane0"));
    gridLayout->addWidget(graphicsViewBitPlane0, 0, 0, 1, 1);

    graphicsViewBitPlane1 = new QGraphicsView(centralWidget);
    graphicsViewBitPlane1->setObjectName(QStringLiteral("graphicsViewBitPlane1"));
    gridLayout->addWidget(graphicsViewBitPlane1, 0, 1, 1, 1);

    graphicsViewBitPlane2 = new QGraphicsView(centralWidget);
    graphicsViewBitPlane2->setObjectName(QStringLiteral("graphicsViewBitPlane2"));
    gridLayout->addWidget(graphicsViewBitPlane2, 0, 2, 1, 1);

    graphicsViewBitPlane3 = new QGraphicsView(centralWidget);
    graphicsViewBitPlane3->setObjectName(QStringLiteral("graphicsViewBitPlane3"));
    gridLayout->addWidget(graphicsViewBitPlane3, 0, 3, 1, 1);

    graphicsViewBitPlane4 = new QGraphicsView(centralWidget);
    graphicsViewBitPlane4->setObjectName(QStringLiteral("graphicsViewBitPlane4"));
    gridLayout->addWidget(graphicsViewBitPlane4, 1, 0, 1, 1);

    graphicsViewBitPlane5 = new QGraphicsView(centralWidget);
    graphicsViewBitPlane5->setObjectName(QStringLiteral("graphicsViewBitPlane5"));
    gridLayout->addWidget(graphicsViewBitPlane5, 1, 1, 1, 1);

    graphicsViewBitPlane6 = new QGraphicsView(centralWidget);
    graphicsViewBitPlane6->setObjectName(QStringLiteral("graphicsViewBitPlane6"));
    gridLayout->addWidget(graphicsViewBitPlane6, 1, 2, 1, 1);

    graphicsViewBitPlane7 = new QGraphicsView(centralWidget);
    graphicsViewBitPlane7->setObjectName(QStringLiteral("graphicsViewBitPlane7"));
    gridLayout->addWidget(graphicsViewBitPlane7, 1, 3, 1, 1);

    this->setCentralWidget(centralWidget);

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
