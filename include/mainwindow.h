#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ColorMethod.h"
#include "SharpenMethod.h"
#include "dialogbitplane.h"
#include "dialoggrayscalethreshold.h"
#include "dialoghistogram.h"
#include "dialoglinearpointoperation.h"
#include "dialoglogtransformation.h"
#include "dialogpowertransformation.h"
#include "dialogquantifylevel.h"
#include "dialogrotation.h"
#include "dialogsamplingrate.h"
#include "dialogscaling.h"
#include "dialogtranslation.h"
#include "smoothmethod.h"
//#include "spectrogram.h"
#include <QApplication>
#include <QCoreApplication>
#include <QtCore/QDateTime>
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtCore/QFileInfo>
#include <QtCore/QStandardPaths>
#include <QtGui/QImage>
#include <QtGui/QImageReader>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QGraphicsPixmapItem>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
//#include <opencv4/opencv2/core/core.hpp>
//#include <opencv4/opencv2/highgui/highgui.hpp>
//#include <opencv4/opencv2/imgproc/imgproc.hpp>

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

    QMenuBar *menuBar;
    QToolBar *toolBar;
    QStatusBar *statusBar;

    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuDisplay;
    QMenu *menuPointOperation;
    QMenu *menuGeometricOperation;
    QMenu *menuImageTransformation;
    QMenu *menuImageEnhancement;
    QMenu *menuColorTransformation;
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

    QAction *actionLinearTransformation;
    QMenu *menuNolinearPointOperation;
    QAction *actionLogTransformation;
    QAction *actionPowerTransformation;
    QAction *actionHistogramEqualization;

    QMenu *menuSpatialTransformation;
    QAction *actionScaling;
    QAction *actionRotation;
    QAction *actionTranslation;

    QAction *actionSpectrogram;

    QMenu *menuSmooth;
    QAction *actionAverageFiltering;
    QAction *actionMedianFiltering;
    QAction *actionKNNF;
    QAction *actionKNNMF;
    QMenu *menuSharpen;
    QAction *actionReborts;
    QAction *actionSobel;
    QAction *actionLaplace;
    QAction *actionEnhancedLaplace;
    QAction *actionConvolution;

    // 颜色处理
    QAction *actionToGray;
    QAction *actionTo256;

    QAction *actionAbout;

    QLabel *statusSize;

    QGraphicsView *graphicsViewLeft;
    QGraphicsView *graphicsViewRight;

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
    void updateRightImageManual(QImage &newImage);
    void closeImage();
    void setStatus(bool status);

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

    void on_actionLinearTransformation_triggered();
    void on_actionLogTransformation_triggered();
    void on_actionPowerTransformation_triggered();
    void on_actionHistogramEqualization_triggered();

    void on_actionScaling_triggered();
    void on_actionRotation_triggered();
    void on_actionTranslation_triggered();

    void on_actionSpectrogram_triggered();

    void on_actionAverageFiltering_triggered();
    void on_actionMedianFiltering_triggered();
    void on_actionKNNF_triggered();
    void on_actionKNNMF_triggered();
    void on_actionReborts_triggered();
    void on_actionSobel_triggered();
    void on_actionLaplace_triggered();
    void on_actionEnhancedLaplace_triggered();
    void on_actionConvolution_triggered();

    void on_actionToGray_triggered();
    void on_actionTo256_triggered();

    // void on_actionAbout_triggered();

    void
    updateRightImage(QImage &newImage);
};

#endif // MAINWINDOW_H
