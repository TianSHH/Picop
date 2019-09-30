#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setup();
    retranslate();
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
    menuHelp = new QMenu(menuBar);
    menuHelp->setObjectName(QStringLiteral("menuHelp"));
    this->setMenuBar(menuBar);

    toolBar = new QToolBar(this);
    toolBar->setObjectName(QStringLiteral("toolBar"));
    this->addToolBar(Qt::TopToolBarArea, toolBar);

    statusBar = new QStatusBar(this);
    statusBar->setObjectName(QStringLiteral("statusBar"));
    this->setStatusBar(statusBar);

    menuBar->addAction(menuFile->menuAction());
    menuBar->addAction(menuEdit->menuAction());
    menuBar->addAction(menuDisplay->menuAction());
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

    menuHelp->addAction(actionAbout);

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

    actionAbout->setText(QApplication::translate("MainWindow", "关于(&A)", Q_NULLPTR));
    actionAbout->setShortcut(QApplication::translate("MainWindow", "F1", Q_NULLPTR));

    menuFile->setTitle(QApplication::translate("MainWindow", "文件(&F)", Q_NULLPTR));
    menuEdit->setTitle(QApplication::translate("MainWindow", "编辑(&E)", Q_NULLPTR));
    menuDisplay->setTitle(QApplication::translate("MainWindow", "显示(&D)", Q_NULLPTR));
    menuHelp->setTitle(QApplication::translate("MainWindow", "帮助(&H)", Q_NULLPTR));
} // retranslate

QString MainWindow::getUserPath()
{
    QString userPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    return userPath;
} // getUserPath

void MainWindow::updateRightScene(QImage &newImage)
{
    rightPixmapItem = rightScene->addPixmap(QPixmap::fromImage(newImage));
    //    rightScene->setSceneRect(QRectF(pixmap.rect()));
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "更新右侧图像";
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

void MainWindow::showHideDialog(QDialog *dialog)
{
    if (dialog->isVisible())
        dialog->activateWindow();
    else
        dialog->show();
} // showHideDialog

void MainWindow::setSamplingRate(const int &rate)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "修改采样率" << rate;

    QImage originImage = leftPixmapItem->pixmap().toImage();
    QImage newImage = rightPixmapItem->pixmap().toImage();

    int width = newImage.width();
    int height = newImage.height();

    int r, g, b;

    QColor color;

    for (int i = 0; i < width; i += rate)
        for (int j = 0; j < height; j += rate)
        {
            color = QColor(originImage.pixel(i, j));
            r = color.red();
            g = color.green();
            b = color.blue();

            newImage.setPixel(i + 1, j + 1, qRgb(r, g, b));

            for (int p = 0; p < rate && i + p < height; p++)
                for (int q = 0; q < rate && j + q < width; q++)
                    newImage.setPixel(i + p, j + q, qRgb(r, g, b));
        }

    updateRightScene(newImage);
} // setSamplingRate

void MainWindow::setQuantifyLevel(const int &level)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "修改量化等级" << level;

    if (level <= 1 || level >= 257)
    {
        qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                           << "量化等级范围 2-256";
        return;
    }

    QImage originImage = leftPixmapItem->pixmap().toImage();
    QImage newImage = leftPixmapItem->pixmap().toImage();

    int width = newImage.width();
    int height = newImage.height();

    // 区间长度
    int length = 256 / (level - 1);

    // 遍历像素点
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // 获取该点灰度值
            QColor color(originImage.pixel(i, j));
            int gray = color.red();

            int left = 0;
            int right = length - 1;

            // 对于某一个像素点, 开始判断它的灰度值处于哪个区间
            while (right <= 255)
            {

                if ((left <= gray) && (gray <= right))
                {
                    if (right - gray <= gray - left)
                    {
                        newImage.setPixel(i, j, qRgb(right, right, right));
                        break;
                    }
                    else
                    {
                        newImage.setPixel(i, j, qRgb(left, left, left));
                        break;
                    }
                }
                else
                {
                    left += length;
                    right += length;
                }
            }
        }
    }

    updateRightScene(newImage);
} // setQuantifyLevel

void MainWindow::setGrayscaleThreshold(const int &threshold)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "修改灰度阀值" << threshold;

    QImage originImage = leftPixmapItem->pixmap().toImage();
    QImage newImage = rightPixmapItem->pixmap().toImage();

    int width = newImage.width();
    int height = newImage.height();

    int gray;

    QColor color;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            color = QColor(originImage.pixel(i, j));
            gray = color.red();

            if (gray < threshold)
                newImage.setPixel(i, j, qRgb(0, 0, 0));
            else
                newImage.setPixel(i, j, qRgb(255, 255, 255));
        }
    }
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "图像二值化";

    updateRightScene(newImage);
} // setGrayscaleThreshold

void MainWindow::displayBitPlane()
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "显示位平面";

    DialogBitPlane *dialogBitPlane = new DialogBitPlane(nullptr);

    showHideDialog(dialogBitPlane);

    QImage *originImage = new QImage(leftPixmapItem->pixmap().toImage());

    dialogBitPlane->displayBitPlane(originImage);

    delete originImage;
} // displayBitPlane

void MainWindow::displayHistogram()
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "显示直方图";

    DialogHistogram *dialogHistogram = new DialogHistogram(nullptr);

    showHideDialog(dialogHistogram);

    QImage *originImage = new QImage(leftPixmapItem->pixmap().toImage());

    dialogHistogram->displayHistogram(originImage);

    delete originImage;
} // diaplayHistogram

void MainWindow::on_actionOpen_triggered()
{
    closeImage();

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

        QImage leftImage;

        leftImage.load(imagePath);
        leftPixmapItem = leftScene->addPixmap(QPixmap::fromImage(leftImage));

        QImage rightImage;

        rightImage.load(imagePath);
        rightPixmapItem = rightScene->addPixmap(QPixmap::fromImage(rightImage));

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
} // on_actionClose_triggered

void MainWindow::on_actionQuit_triggered()
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "程序运行结束";
    qApp->quit();
} // on_actionQuit_triggered

void MainWindow::on_actionSetSamplingRate_triggered()
{
    DialogSamplingRate *dialogSamplingRate = new DialogSamplingRate(nullptr);

    showHideDialog(dialogSamplingRate);

    connect(dialogSamplingRate, SIGNAL(signalSetSamplingRate(const int &)), this, SLOT(setSamplingRate(const int &)));
} // on_actionSetSamplingRate_triggered

void MainWindow::on_actionSetQuantifyLevel_triggered()
{
    DialogQuantifyLevel *dialogQuantifyLevel = new DialogQuantifyLevel(nullptr);

    showHideDialog(dialogQuantifyLevel);

    connect(dialogQuantifyLevel, SIGNAL(signalSetQuantifyLevel(const int &)), this, SLOT(setQuantifyLevel(const int &)));
} // on_actionSetQuantifyLevel_triggered

void MainWindow::on_actionSetGrayscaleThreshold_triggered()
{
    DialogGrayscaleThreshold *dialogGrayscaleThreshold = new DialogGrayscaleThreshold(this);

    showHideDialog(dialogGrayscaleThreshold);

    connect(dialogGrayscaleThreshold, SIGNAL(signalThresholdChanged(const int &)), this, SLOT(setGrayscaleThreshold(const int &)));
} // on_actionSetGrayscaleThreshold_triggered

void MainWindow::on_actionDisplayBitPlane_triggered()
{
    displayBitPlane();
}

void MainWindow::on_actionDisplayHistogram_triggered()
{
    displayHistogram();
}
