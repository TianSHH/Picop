#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "ColorMethod.h"
#include "EdgeMethod.h"
#include "SharpenMethod.h"
#include "SpectrogramMethod.h"
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
    // QToolBar *toolBar;
    QStatusBar *statusBar;

    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuDisplay;
    QMenu *menuPointOperation;
    QMenu *menuGeometricOperation;
    QMenu *menuImageTransformation;
    QMenu *menuImageEnhancement;
    QMenu *menuColorTransformation;
    QMenu *menuImageSegmentation;
    QMenu *menuHelp;

    // 基本文件处理
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSaveAs;
    QAction *actionClose;
    QAction *actionQuit;

    // 第2章作业, 图像数字化与显示
    QAction *actionSetSamplingRate;       // 设定采样率
    QAction *actionSetQuantifyLevel;      // 设定量化等级
    QAction *actionSetGrayscaleThreshold; // 设定灰度阀值

    // 第3,4章作业, 图像表示与处理
    QAction *actionDisplayBitPlane;  // 显示位平面
    QAction *actionDisplayHistogram; // 显示直方图

    // 第5章作业, 点运算
    QAction *actionLinearTransformation; // 线性变换
    QMenu *menuNolinearPointOperation;
    QAction *actionLogTransformation;     // 对数变换
    QAction *actionPowerTransformation;   // 幂次变换
    QAction *actionHistogramEqualization; // 直方图均衡化

    // 第6章作业, 几何运算
    QMenu *menuSpatialTransformation;
    QAction *actionScaling;     // 缩放
    QAction *actionRotation;    // 旋转
    QAction *actionTranslation; // 平移

    // 第8章作业, 图像变换
    QAction *actionSpectrogram; // 频谱图

    // 第9章作业 图像增强
    QMenu *menuSmooth;                // 平滑
    QAction *actionAverageFiltering;  // 均值滤波
    QAction *actionMedianFiltering;   // 中值滤波
    QAction *actionKNNF;              // K近邻均值滤波
    QAction *actionKNNMF;             // K近邻中值滤波
    QMenu *menuSharpen;               // 锐化
    QAction *actionReborts;           // Reborts算子
    QAction *actionSobel;             // Sobel算子
    QAction *actionLaplacian;         // Laplacian算子
    QAction *actionEnhancedLaplacian; // 增强Laplacian算子
    QAction *actionConvolution;       // 自定义卷积

    // 第11章作业, 彩色处理
    QAction *actionToGray; // 灰度转换
    QAction *actionTo256;  // 24位真彩色转换为256色

    // 第12章作业, 图像分割
    QMenu *menuEdgeDetect;        // 边缘检测
    QAction *actionEdgeSobel;     // Sobel算子
    QAction *actionEdgePrewitt;   // Prewitt算子
    QAction *actionEdgeLaplacian; // Laplacian算子
    QAction *actionEdgeTracing;   // 边缘跟踪
    QAction *actionEdgeHough;     // 霍夫变换检测直线

    QAction *actionAbout; // 关于本作业

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
    void on_actionLaplacian_triggered();
    void on_actionEnhancedLaplacian_triggered();
    void on_actionConvolution_triggered();

    void on_actionToGray_triggered();
    void on_actionTo256_triggered();

    void on_actionEdgeSobel_triggered();
    void on_actionEdgePrewitt_triggered();
    void on_actionEdgeLaplacian_triggered();
    void on_actionEdgeTracing_triggered();
    void on_actionEdgeHough_triggered();

    void on_actionAbout_triggered();

    void updateRightImage(QImage &newImage);
};

#endif // MAINWINDOW_H
