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
    this->resize(400, 300);

    actionOpen = new QAction(this);
    actionOpen->setObjectName(QStringLiteral("actionOpen"));
    actionSave = new QAction(this);
    actionSave->setObjectName(QStringLiteral("actionSave"));
    actionSaveAs = new QAction(this);
    actionSaveAs->setObjectName(QStringLiteral("actionSaveAs"));
    actionQuit = new QAction(this);
    actionQuit->setObjectName(QStringLiteral("actionQuit"));
    actionSetSamplingRate = new QAction(this);
    actionSetSamplingRate->setObjectName(QStringLiteral("actionSetSamplingRate"));
    actionSetQuantifyLevel = new QAction(this);
    actionSetQuantifyLevel->setObjectName(QStringLiteral("actionSetQuantifyLevel"));
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
    menuBar->addAction(menuDisplay->menuAction());
    menuBar->addAction(menuHelp->menuAction());
    menuFile->addAction(actionOpen);
    menuFile->addAction(actionSave);
    menuFile->addAction(actionSaveAs);
    menuFile->addAction(actionQuit);
    menuDisplay->addAction(actionSetSamplingRate);
    menuDisplay->addAction(actionSetQuantifyLevel);
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
}

void MainWindow::retranslate()
{
    this->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));

    actionOpen->setText(QApplication::translate("MainWindow", "打开(&O)", Q_NULLPTR));
    actionOpen->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", Q_NULLPTR));
    actionSave->setText(QApplication::translate("MainWindow", "保存(&S)", Q_NULLPTR));
    actionSave->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", Q_NULLPTR));
    actionSaveAs->setText(QApplication::translate("MainWindow", "另存为……", Q_NULLPTR));
    actionSaveAs->setShortcut(QApplication::translate("MainWindow", "Ctrl+Shift+S", Q_NULLPTR));
    actionQuit->setText(QApplication::translate("MainWindow", "退出(&Q)", Q_NULLPTR));
    actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", Q_NULLPTR));

    actionSetSamplingRate->setText(QApplication::translate("MainWindow", "设定采样率(&S)", Q_NULLPTR));
    actionSetQuantifyLevel->setText(QApplication::translate("MainWindow", "设定量化等级(&Q)", Q_NULLPTR));

    actionAbout->setText(QApplication::translate("MainWindow", "关于(&A)", Q_NULLPTR));
    actionAbout->setShortcut(QApplication::translate("MainWindow", "F1", Q_NULLPTR));

    menuFile->setTitle(QApplication::translate("MainWindow", "文件(&F)", Q_NULLPTR));
    menuDisplay->setTitle(QApplication::translate("MainWindow", "显示", Q_NULLPTR));
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
    qDebug() << QDateTime::currentDateTime().addSecs(-10).toString("yyyy-MM-dd hh:mm:ss") << "更新右侧图片";
} // updateRightScene

void MainWindow::setSamplingRate(const int &rate)
{
    qDebug() << QDateTime::currentDateTime().addSecs(-10).toString("yyyy-MM-dd hh:mm:ss") << "修改采样率";

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

    qDebug() << QDateTime::currentDateTime().addSecs(-10).toString("yyyy-MM-dd hh:mm:ss") << "Done!";
} // setSamplingRate
void MainWindow::setQuantifyLevel(const int &level)
{
    qDebug() << QDateTime::currentDateTime().addSecs(-10).toString("yyyy-MM-dd hh:mm:ss") << "修改量化等级";

    if (level == 1)
    {
        qDebug() << QDateTime::currentDateTime().addSecs(-10).toString("yyyy-MM-dd hh:mm:ss") << "量化等级不能为 1";
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

    qDebug() << QDateTime::currentDateTime().addSecs(-10).toString("yyyy-MM-dd hh:mm:ss") << "Done!";
} // setQuantifyLevel

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

        // delete previous image
        //        cleanImage();

        // upload image
        info = new QFileInfo(imagePath);

        QImage leftImage;

        // 使用 QImage 加载图片
        leftImage.load(imagePath);
        leftPixmapItem = leftScene->addPixmap(QPixmap::fromImage(leftImage));

        QImage rightImage;

        rightImage.load(imagePath);
        rightPixmapItem = rightScene->addPixmap(QPixmap::fromImage(rightImage));
    }
} // on_actionOpen_triggered

void MainWindow::on_actionSave_triggered()
{
    QString imageSavePath = imagePath;
    QString imageFormat = imagePath;

    // 获取图片所在目录
    imageSavePath = imageSavePath.left(imageSavePath.lastIndexOf("/") + 1);
    // 获取图片格式
    imageFormat = imageFormat.right(imageFormat.length() - imageFormat.lastIndexOf(".") - 1);

    rightPixmapItem->pixmap().toImage().save(imagePath, (const char *)imageFormat.toStdString().c_str(), 100);

    qDebug() << QDateTime::currentDateTime().addSecs(-10).toString("yyyy-MM-dd hh:mm:ss") << "保存" << imageSavePath;
    qDebug() << QDateTime::currentDateTime().addSecs(-10).toString("yyyy-MM-dd hh:mm:ss") << "Done!";
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

    qDebug() << QDateTime::currentDateTime().addSecs(-10).toString("yyyy-MM-dd hh:mm:ss") << "另存为" << imageSaveAsPath;

    qDebug() << QDateTime::currentDateTime().addSecs(-10).toString("yyyy-MM-dd hh:mm:ss") << "Done!";
} // on_actionSaveAs_triggered

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
} // on_actionQuit_triggered

void MainWindow::on_actionSetSamplingRate_triggered()
{
    DialogSamplingRate *dialogSamplingRate = new DialogSamplingRate(nullptr);

    if (dialogSamplingRate->isVisible())
        dialogSamplingRate->activateWindow();
    else
        dialogSamplingRate->show();

    connect(dialogSamplingRate, SIGNAL(signalSetSamplingRate(const int &)), this, SLOT(setSamplingRate(const int &)));
} // on_actionSetSamplingRate_triggered

void MainWindow::on_actionSetQuantifyLevel_triggered()
{
    DialogQuantifyLevel *dialogQuantifyLevel = new DialogQuantifyLevel(nullptr);

    if (dialogQuantifyLevel->isVisible())
        dialogQuantifyLevel->activateWindow();
    else
        dialogQuantifyLevel->show();

    connect(dialogQuantifyLevel, SIGNAL(signalSetQuantifyLevel(const int &)), this, SLOT(setQuantifyLevel(const int &)));
} // on_actionSetQuantifyLevel_triggered
