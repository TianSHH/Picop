#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialogbitplane.h"
#include "dialoggrayscalethreshold.h"
#include "dialoghistogram.h"
#include "dialogquantifylevel.h"
#include "dialogsamplingrate.h"
#include <QAction>
#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QtWidgets/QDialog>
#include <QFileDialog>
#include <QFileInfo>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGridLayout>
#include <QImage>
#include <QImageReader>
#include <QLabel>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QMessageBox>
#include <QStandardPaths>
#include <QStatusBar>
#include <QToolBar>
#include <QtCore/QDateTime>

#define WINDOW_TITLE "Picop"
#define WINDOW_CRITICAL "Error - Picop"
#define WINDOW_WARNING "Notice - Picop"
#define WINDOW_ABOUT "About - Picop"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public:
    QWidget *centralWidget;

    QGridLayout *gridLayout;

    QGraphicsView *graphicsViewLeft;
    QGraphicsView *graphicsViewRight;

    QMenuBar *menuBar;
    QToolBar *toolBar;
    QStatusBar *statusBar;

    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuDisplay;
    QMenu *menuHelp;

    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionClose;
    QAction *actionQuit;

    QAction *actionSetSamplingRate;
    QAction *actionSetQuantifyLevel;
    QAction *actionSetGrayscaleThreshold;

    QAction *actionDisplayBitPlane;
    QAction *actionDisplayHistogram;

    QAction *actionAbout;

    QGraphicsScene *leftScene;
    QGraphicsScene *rightScene;
    QGraphicsPixmapItem *leftPixmapItem;
    QGraphicsPixmapItem *rightPixmapItem;

    QFileInfo *info;
    QString imagePath; // 当前打开图像的路径

public:
    void setup();
    void retranslate();
    QString getUserPath();
    void updateRightScene(QImage &newImage);
    void closeImage();

signals:
    void signalSendImage(QImage *);

private slots:
    void emitSignalSendImage();

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionSaveAs_triggered();
    void on_actionClose_triggered();
    void on_actionQuit_triggered();

    void on_actionSetSamplingRate_triggered();
    void on_actionSetQuantifyLevel_triggered();
    void on_actionSetGrayscaleThreshold_triggered();

    void on_actionDisplayBitPlane_triggered();
    void on_actionDisplayHistogram_triggered();

    // void on_actionAbout_triggered();

    void updateRightImage(QImage & newImage);
};

#endif // MAINWINDOW_H
