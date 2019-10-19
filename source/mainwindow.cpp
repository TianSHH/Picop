// TODO 根据打开图像大小自动调整窗口大小
// TODO 实现滚轮控制图片缩放
// TODO 自选, 实现bmp2txt
// TODO 优化直方图均衡化和直方图显示功能
#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setup();
    retranslate();
    setStatus(false);
}

MainWindow::~MainWindow()
{
}

void MainWindow::setup()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("this"));

    this->resize(800, 600);

    actionOpen = new QAction(this);
    actionOpen->setObjectName(QStringLiteral("actionOpen"));
    actionSave = new QAction(this);
    actionSave->setObjectName(QStringLiteral("actionSave"));
    actionSaveAs = new QAction(this);
    actionSaveAs->setObjectName(QStringLiteral("actionSaveAs"));
    actionClose = new QAction(this);
    actionClose->setObjectName(QStringLiteral("actionClose"));
    actionQuit = new QAction(this);
    actionQuit->setObjectName(QStringLiteral("actionQuit"));

    actionSetSamplingRate = new QAction(this);
    actionSetSamplingRate->setObjectName(QStringLiteral("actionSetSamplingRate"));
    actionSetQuantifyLevel = new QAction(this);
    actionSetQuantifyLevel->setObjectName(QStringLiteral("actionSetQuantifyLevel"));
    actionSetGrayscaleThreshold = new QAction(this);
    actionSetGrayscaleThreshold->setObjectName(QStringLiteral("actionSetGrayscaleThreshold"));

    actionDisplayBitPlane = new QAction(this);
    actionDisplayBitPlane->setObjectName(QStringLiteral("actionDisplayBitPlane"));
    actionDisplayHistogram = new QAction(this);
    actionDisplayHistogram->setObjectName(QStringLiteral("actionDisplayHistogram"));

    actionLinearTransformation = new QAction(this);
    actionLinearTransformation->setObjectName(QStringLiteral("actionLinearTransformation"));
    menuNolinearPointOperation = new QMenu(this); // 二级菜单
    menuNolinearPointOperation->setObjectName(QStringLiteral("menuNolinearPointOperation"));
    actionLogTransformation = new QAction(this);
    actionLogTransformation->setObjectName(QStringLiteral("actionLogTransformation"));
    actionPowerTransformation = new QAction(this);
    actionPowerTransformation->setObjectName(QStringLiteral("actionPowerTransformation"));
    actionHistogramEqualization = new QAction(this);
    actionHistogramEqualization->setObjectName(QStringLiteral("actionHistogramEqualization"));

    menuSpatialTransformation = new QMenu(this);
    menuSpatialTransformation->setObjectName(QStringLiteral("menuSpatialTransformation"));
    actionScaling = new QAction(this);
    actionScaling->setObjectName(QStringLiteral("actionScaling"));
    actionRotation = new QAction(this);
    actionRotation->setObjectName(QStringLiteral("actionRotation"));
    actionTranslation = new QAction(this);
    actionTranslation->setObjectName(QStringLiteral("actionTranslation"));
    menuGrayLevelInterpolation = new QMenu(this);
    menuGrayLevelInterpolation->setObjectName(QStringLiteral("menuGrayLevelInterpolation"));

    actionAbout = new QAction(this);
    actionAbout->setObjectName(QStringLiteral("actionAbout"));

    centralWidget = new QWidget(this);
    centralWidget->setObjectName(QStringLiteral("centralWidget"));
    gridLayout = new QGridLayout(centralWidget);
    gridLayout->setSpacing(6);
    gridLayout->setContentsMargins(11, 11, 11, 11);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    graphicsViewLeft = new QGraphicsView(centralWidget);
    graphicsViewLeft->setObjectName(QStringLiteral("graphicsViewLeft"));
    gridLayout->addWidget(graphicsViewLeft, 0, 0, 1, 1);

    graphicsViewRight = new QGraphicsView(centralWidget);
    graphicsViewRight->setObjectName(QStringLiteral("graphicsViewRight"));
    gridLayout->addWidget(graphicsViewRight, 0, 1, 1, 1);

    this->setCentralWidget(centralWidget);

    menuBar = new QMenuBar(this);
    menuBar->setObjectName(QStringLiteral("menuBar"));
    menuBar->setGeometry(QRect(0, 0, 400, 27));
    menuFile = new QMenu(menuBar);
    menuFile->setObjectName(QStringLiteral("menuFile"));
    menuEdit = new QMenu(menuBar);
    menuEdit->setObjectName(QStringLiteral("menuEdit"));
    menuDisplay = new QMenu(menuBar);
    menuDisplay->setObjectName(QStringLiteral("menuDisplay"));
    menuPointOperation = new QMenu(menuBar);
    menuPointOperation->setObjectName(QStringLiteral("menuPointOperation"));
    menuGeometricOperation = new QMenu(menuBar);
    menuGeometricOperation->setObjectName(QStringLiteral("menuGeometricOperation"));
    menuHelp = new QMenu(menuBar);
    menuHelp->setObjectName(QStringLiteral("menuHelp"));
    this->setMenuBar(menuBar);

    toolBar = new QToolBar(this);
    toolBar->setObjectName(QStringLiteral("toolBar"));
    this->addToolBar(Qt::TopToolBarArea, toolBar);

    statusSize = new QLabel(this);
    statusSize->setObjectName(QStringLiteral("stuatusSize"));

    statusBar = new QStatusBar(this);
    statusBar->setObjectName(QStringLiteral("statusBar"));
    this->setStatusBar(statusBar);

    // 菜单栏添加组件

    menuBar->addAction(menuFile->menuAction());
    menuBar->addAction(menuEdit->menuAction());
    menuBar->addAction(menuDisplay->menuAction());
    menuBar->addAction(menuPointOperation->menuAction());
    menuBar->addAction(menuGeometricOperation->menuAction());
    menuBar->addAction(menuHelp->menuAction());

    menuFile->addAction(actionOpen);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionSaveAs);
    menuFile->addSeparator();
    menuFile->addAction(actionClose);
    menuFile->addSeparator();
    menuFile->addAction(actionQuit);

    menuEdit->addAction(actionSetSamplingRate);
    menuEdit->addAction(actionSetQuantifyLevel);
    menuEdit->addAction(actionSetGrayscaleThreshold);

    menuDisplay->addAction(actionDisplayBitPlane);
    menuDisplay->addAction(actionDisplayHistogram);

    menuPointOperation->addAction(actionLinearTransformation);
    menuPointOperation->addMenu(menuNolinearPointOperation);        // 添加二级菜单
    menuNolinearPointOperation->addAction(actionLogTransformation); // 二级菜单下添加Action
    menuNolinearPointOperation->addAction(actionPowerTransformation);
    menuNolinearPointOperation->addAction(actionHistogramEqualization);

    menuGeometricOperation->addMenu(menuSpatialTransformation);
    menuSpatialTransformation->addAction(actionScaling);
    menuSpatialTransformation->addAction(actionRotation);
    menuSpatialTransformation->addAction(actionTranslation);
    menuGeometricOperation->addMenu(menuGrayLevelInterpolation);

    menuHelp->addAction(actionAbout);

    // 状态栏添加组件

    statusBar->addPermanentWidget(statusSize);

    leftScene = new QGraphicsScene;
    rightScene = new QGraphicsScene;

    leftPixmapItem = new QGraphicsPixmapItem();
    rightPixmapItem = new QGraphicsPixmapItem();

    info = nullptr;

    leftScene->setBackgroundBrush(QColor::fromRgb(224, 224, 224));
    graphicsViewLeft->setScene(leftScene);
    rightScene->setBackgroundBrush(QColor::fromRgb(224, 224, 224));
    graphicsViewRight->setScene(rightScene);

    QMetaObject::connectSlotsByName(this);
} // setup

void MainWindow::retranslate()
{
    this->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));

    actionOpen->setText(QApplication::translate("MainWindow", "打开(&O)", Q_NULLPTR));
    actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", Q_NULLPTR));
    actionSave->setText(QApplication::translate("MainWindow", "保存(&S)", Q_NULLPTR));
    actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", Q_NULLPTR));
    actionSaveAs->setText(QApplication::translate("MainWindow", "另存为……", Q_NULLPTR));
    actionSaveAs->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", Q_NULLPTR));
    actionClose->setText(QApplication::translate("MainWindos", "关闭(&C)", Q_NULLPTR));
    actionClose->setShortcut(QApplication::translate("MainWindow", "Ctrl+W", Q_NULLPTR));
    actionQuit->setText(QApplication::translate("MainWindow", "退出(&Q)", Q_NULLPTR));
    actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", Q_NULLPTR));

    actionSetSamplingRate->setText(QApplication::translate("MainWindow", "设定采样率(&S)", Q_NULLPTR));
    actionSetQuantifyLevel->setText(QApplication::translate("MainWindow", "设定量化等级(&Q)", Q_NULLPTR));
    actionSetGrayscaleThreshold->setText(QApplication::translate("MainWindow", "设定灰度阀值(&G)", Q_NULLPTR));

    actionDisplayBitPlane->setText(QApplication::translate("MainWindow", "显示位平面(&B)", Q_NULLPTR));
    actionDisplayHistogram->setText(QApplication::translate("MainWindow", "显示直方图(&H)", Q_NULLPTR));

    actionLinearTransformation->setText(QApplication::translate("MainWindow", "线性点运算(&L)", Q_NULLPTR));
    menuNolinearPointOperation->setTitle(QApplication::translate("MainWindow", "非线性点运算(&N)", Q_NULLPTR));
    actionLogTransformation->setText(QApplication::translate("MainWindow", "对数变换(&L)", Q_NULLPTR));
    actionPowerTransformation->setText(QApplication::translate("MainWindow", "幂次变换(&P)", Q_NULLPTR));
    actionHistogramEqualization->setText(QApplication::translate("MainWindow", "直方图均衡化(&H)", Q_NULLPTR));

    menuSpatialTransformation->setTitle(QApplication::translate("MainWindow", "空间变换(&S)", Q_NULLPTR));
    actionScaling->setText(QApplication::translate("MainWindow", "缩放(&S)", Q_NULLPTR));
    actionRotation->setText(QApplication::translate("MainWindow", "旋转(&R)", Q_NULLPTR));
    actionTranslation->setText(QApplication::translate("MainWindow", "平移(&T)", Q_NULLPTR));
    menuGrayLevelInterpolation->setTitle(QApplication::translate("MainWindow", "直方图均衡化(&H)", Q_NULLPTR));

    actionAbout->setText(QApplication::translate("MainWindow", "关于(&A)", Q_NULLPTR));
    actionAbout->setShortcut(QApplication::translate("MainWindow", "F1", Q_NULLPTR));

    menuFile->setTitle(QApplication::translate("MainWindow", "文件(&F)", Q_NULLPTR));
    menuEdit->setTitle(QApplication::translate("MainWindow", "编辑(&E)", Q_NULLPTR));
    menuDisplay->setTitle(QApplication::translate("MainWindow", "显示(&D)", Q_NULLPTR));
    menuPointOperation->setTitle(QApplication::translate("MainWindow", "点运算(&P)", Q_NULLPTR));
    menuGeometricOperation->setTitle(QApplication::translate("MainWindow", "几何运算(&G)", Q_NULLPTR));
    menuHelp->setTitle(QApplication::translate("MainWindow", "帮助(&H)", Q_NULLPTR));

    statusSize->setText(QApplication::translate("MainWindow", "", Q_NULLPTR));
} // retranslate

QString MainWindow::getUserPath()
{
    QString userPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    return userPath;
} // getUserPath

void MainWindow::updateRightScene(QImage &newImage)
{
    // rightPixmapItem = rightScene->addPixmap(QPixmap::fromImage(newImage));
    //    rightScene->setSceneRect(QRectF(pixmap.rect()));
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "更新右侧图像";
    rightPixmapItem->setPixmap(QPixmap::fromImage(newImage));
    rightScene->setSceneRect(QRectF(newImage.rect()));
} // updateRightScene

void MainWindow::closeImage()
{
    leftScene->clear();
    graphicsViewLeft->resetTransform();

    rightScene->clear();
    graphicsViewRight->resetTransform();

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "关闭图像";
} // closeImage

void MainWindow::setStatus(bool status)
{
    actionSave->setEnabled(status);
    actionSaveAs->setEnabled(status);
    actionClose->setEnabled(status);

    actionSetSamplingRate->setEnabled(status);
    actionSetQuantifyLevel->setEnabled(status);
    actionSetGrayscaleThreshold->setEnabled(status);

    actionDisplayBitPlane->setEnabled(status);
    actionDisplayHistogram->setEnabled(status);
} // setStatus

void MainWindow::emitSignalSendImage()
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "发送图片";

    QImage *originImage = new QImage(leftPixmapItem->pixmap().toImage());

    emit signalSendImage(originImage);

    delete originImage;
} // emitSignalSendImage

void MainWindow::on_actionOpen_triggered()
{
    imagePath = QFileDialog::getOpenFileName(this, tr("Open image"), getUserPath() + "/Pictures",
                                             tr("All Files (*);;"
                                                "All Images (*.bpm *.gif *.jpg *.jpeg *.png *.ppm *.xbm *.xpm);;"
                                                "Image BPM (*.bpm);;"
                                                "Image GIF (*.gif);;"
                                                "Image JPG (*.jpg);;"
                                                "Image JPEG (*.jpeg);;"
                                                "Image PNG (*.png);;"
                                                "Image PPM (*.ppm);;"
                                                "Image XBM (*.xbm);;"
                                                "Image BMP (*.bmp);;"
                                                "Image XPM (*.xpm);;"));

    if (!imagePath.isEmpty())
    {
        QFile file(imagePath);
        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr(WINDOW_CRITICAL), tr("Unable to open image."));
            return;
        }

        info = new QFileInfo(imagePath);

        closeImage();

        QImage leftImage;

        leftImage.load(imagePath);
        leftPixmapItem = leftScene->addPixmap(QPixmap::fromImage(leftImage));

        QImage rightImage;

        rightImage.load(imagePath);
        rightPixmapItem = rightScene->addPixmap(QPixmap::fromImage(rightImage));

        statusSize->setText(QString::number(leftPixmapItem->pixmap().width()) + " x " + QString::number(leftPixmapItem->pixmap().height()));

        setStatus(true);

        this->setWindowTitle(info->fileName() + " - Picop");

        qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                           << "打开图像" << imagePath;
    }
} // on_actionOpen_triggered

void MainWindow::on_actionSave_triggered()
{
    QString imageSavePath = imagePath;
    QString imageFormat = imagePath;

    // 获取图像所在目录
    imageSavePath = imageSavePath.left(imageSavePath.lastIndexOf("/") + 1);
    // 获取图像格式
    imageFormat = imageFormat.right(imageFormat.length() - imageFormat.lastIndexOf(".") - 1);

    rightPixmapItem->pixmap().toImage().save(imagePath, (const char *)imageFormat.toStdString().c_str(), 100);

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "保存图像" << imagePath;
} // on_actionSave_triggered

void MainWindow::on_actionSaveAs_triggered()
{
    QString imageSaveAsPath = QFileDialog::getSaveFileName(this, tr("Open image"), getUserPath() + "/Pictures",
                                                           tr("All Files (*);;"
                                                              "All Images (*.bpm *.gif *.jpg *.jpeg *.png *.ppm *.xbm *.xpm);;"
                                                              "Image BPM (*.bpm);;"
                                                              "Image GIF (*.gif);;"
                                                              "Image JPG (*.jpg);;"
                                                              "Image JPEG (*.jpeg);;"
                                                              "Image PNG (*.png);;"
                                                              "Image PPM (*.ppm);;"
                                                              "Image XBM (*.xbm);;"
                                                              "Image BMP (*.bmp);;"
                                                              "Image XPM (*.xpm);;"));

    if (imageSaveAsPath.isEmpty())
        return;

    rightPixmapItem->pixmap().toImage().save(imageSaveAsPath, nullptr, 100);

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "图像另存为" << imageSaveAsPath;
} // on_actionSaveAs_triggered

void MainWindow::on_actionClose_triggered()
{
    closeImage();

    statusSize->setText("");

    setStatus(false);
} // on_actionClose_triggered

void MainWindow::on_actionQuit_triggered()
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "程序运行结束";
    qApp->quit();
} // on_actionQuit_triggered

void MainWindow::on_actionSetSamplingRate_triggered()
{
    DialogSamplingRate *dialogSamplingRate = new DialogSamplingRate(this);

    dialogSamplingRate->show();

    connect(dialogSamplingRate, SIGNAL(signalSetSamplingRate()), this, SLOT(emitSignalSendImage()));

    connect(dialogSamplingRate, SIGNAL(signalSetSamplingRateFinished(QImage &)), this, SLOT(updateRightImage(QImage &)));
} // on_actionSetSamplingRate_triggered

void MainWindow::on_actionSetQuantifyLevel_triggered()
{
    DialogQuantifyLevel *dialogQuantifyLevel = new DialogQuantifyLevel(this);

    dialogQuantifyLevel->show();

    connect(dialogQuantifyLevel, SIGNAL(signalSetQuantifyLevel()), this, SLOT(emitSignalSendImage()));

    connect(dialogQuantifyLevel, SIGNAL(signalSetQuantifyLevelFinished(QImage &)), this, SLOT(updateRightImage(QImage &)));
} // on_actionSetQuantifyLevel_triggered

void MainWindow::on_actionSetGrayscaleThreshold_triggered()
{
    DialogGrayscaleThreshold *dialogGrayscaleThreshold = new DialogGrayscaleThreshold(this);

    dialogGrayscaleThreshold->show();

    connect(dialogGrayscaleThreshold, SIGNAL(signalSetGrayscaleThreshold()), this, SLOT(emitSignalSendImage()));

    connect(dialogGrayscaleThreshold, SIGNAL(signalSetGrayscaleThresholdFinished(QImage &)), this, SLOT(updateRightImage(QImage &)));
} // on_actionSetGrayscaleThreshold_triggered

void MainWindow::on_actionDisplayBitPlane_triggered()
{
    DialogBitPlane *dialogBitPlane = new DialogBitPlane(nullptr);

    dialogBitPlane->show();

    QImage *originImage = new QImage(leftPixmapItem->pixmap().toImage());

    dialogBitPlane->displayBitPlane(originImage);

    delete originImage;
    dialogBitPlane->exec();
} // on_actionDisplayBitPlane_triggered

void MainWindow::on_actionDisplayHistogram_triggered()
{

    DialogHistogram *dialogHistogram = new DialogHistogram(nullptr);

    dialogHistogram->show();

    QImage *originImage = new QImage(rightPixmapItem->pixmap().toImage()); // 显示右侧图像直方图

    dialogHistogram->displayHistogram(originImage);

    delete originImage;
} // on_actionDisplayHistogram_triggered

void MainWindow::on_actionLinearTransformation_triggered()
{
    DialogLinearPointOperation *_dialogLinearPointOperation = new DialogLinearPointOperation(this);

    _dialogLinearPointOperation->show();

    connect(_dialogLinearPointOperation, SIGNAL(signalLinearPointOperation()), this, SLOT(emitSignalSendImage()));
    connect(_dialogLinearPointOperation, SIGNAL(signalLinearPointOperationFinished(QImage &)), this, SLOT(updateRightImage(QImage &)));
} // on_actionLinearTransformation_triggered

void MainWindow::on_actionLogTransformation_triggered()
{
    DialogLogTransformation *_dialogLogTransformation = new DialogLogTransformation(this);

    _dialogLogTransformation->show();

    connect(_dialogLogTransformation, SIGNAL(signalLogTransformationStart()), this, SLOT(emitSignalSendImage()));
    connect(_dialogLogTransformation, SIGNAL(signalLogTransformationEnd(QImage &)), this, SLOT(updateRightImage(QImage &)));
} // on_actionLogTransformation_triggered

void MainWindow::on_actionPowerTransformation_triggered()
{
    DialogPowerTransformation *_dialogPowerTransformation = new DialogPowerTransformation(this);

    _dialogPowerTransformation->show();

    connect(_dialogPowerTransformation, SIGNAL(signalPowerTransformationStart()), this, SLOT(emitSignalSendImage()));
    connect(_dialogPowerTransformation, SIGNAL(signalPowerTransformationEnd(QImage &)), this, SLOT(updateRightImage(QImage &)));
} // on_actionPowerTransformation_triggered

void MainWindow::on_actionHistogramEqualization_triggered()
{
    DialogHistogram *_dialogHistogram = new DialogHistogram(this);

    QImage *originImage = new QImage(rightPixmapItem->pixmap().toImage()); // 显示右侧图像直方图

    QImage *newImage = _dialogHistogram->histogramEqualization(originImage);

    updateRightScene((QImage &)(*newImage));
} // on_actionHistogramEqualization_triggered

void MainWindow::on_actionTranslation_triggered()
{
    DialogTranslation *_dialogTranslation = new DialogTranslation(this);

    _dialogTranslation->show();

    connect(_dialogTranslation, SIGNAL(signalTranslationStart()), this, SLOT(emitSignalSendImage()));
    connect(_dialogTranslation, SIGNAL(signalTranslationEnd(QImage &)), this, SLOT(updateRightImage(QImage &)));
}

void MainWindow::updateRightImage(QImage &newImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "更新右侧图像";
    rightPixmapItem->setPixmap(QPixmap::fromImage(newImage));
    rightScene->setSceneRect(QRectF(newImage.rect()));
} // updateRightImage
