#include "mainwindow.h"
#include "../build-Picop-Desktop_Qt_5_9_8_GCC_64bit-Debug/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent),
                                          ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    leftScene = new QGraphicsScene;
    rightScene = new QGraphicsScene;

    leftPixmapItem = new QGraphicsPixmapItem();
    rightPixmapItem = new QGraphicsPixmapItem();

    info = nullptr;

    leftScene->setBackgroundBrush(QColor::fromRgb(224, 224, 224));
    ui->graphicsViewLeft->setScene(leftScene);
    rightScene->setBackgroundBrush(QColor::fromRgb(224, 224, 224));
    ui->graphicsViewRight->setScene(rightScene);

    setWindowTitle("Picop");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateRightImage(QImage &newImage)
{
    rightPixmapItem = rightScene->addPixmap(QPixmap::fromImage(newImage));
    //    rightScene->setSceneRect(QRectF(pixmap.rect()));
    qDebug() << "更新右侧图片";
}

void MainWindow::showSamplingRateDialog()
{
    DialogSamplingRate *dialogSamplingRate = new DialogSamplingRate(nullptr);

    if (dialogSamplingRate->isVisible())
        dialogSamplingRate->activateWindow();
    else
        dialogSamplingRate->show();

    connect(dialogSamplingRate, SIGNAL(samplingRateSignal(const int &)), this, SLOT(samplingRate(const int &)));
}

void MainWindow::samplingRate(const int &rate)
{
    qDebug() << "开始修改采样率";

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

    updateRightImage(newImage);

    qDebug() << "Done!";
}

void MainWindow::showQuantifyLevelDialog()
{
    DialogQuantifyLevel *dialogQuantifyLevel = new DialogQuantifyLevel(nullptr);

    if (dialogQuantifyLevel->isVisible())
        dialogQuantifyLevel->activateWindow();
    else
        dialogQuantifyLevel->show();

    connect(dialogQuantifyLevel, SIGNAL(quantifyLevelSignal(const int &)), this, SLOT(quantifyLevel(const int &)));
}

void MainWindow::quantifyLevel(const int &level)
{
    qDebug() << "开始修改量化等级";

    if (level == 1)
    {
        qDebug() << "量化等级不能为1";
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

    updateRightImage(newImage);

    qDebug() << "Done!";
}

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
}

void MainWindow::on_actionSave_triggered()
{
    QString imageSavePath = imagePath;
    QString imageFormat = imagePath;

    // 获取图片所在目录
    imageSavePath = imageSavePath.left(imageSavePath.lastIndexOf("/") + 1);
    // 获取图片格式
    imageFormat = imageFormat.right(imageFormat.length() - imageFormat.lastIndexOf(".") - 1);

    rightPixmapItem->pixmap().toImage().save(imagePath, (const char *)imageFormat.toStdString().c_str(), 100);

    qDebug() << "保存到" << imageSavePath;
    qDebug() << "Done!";
}

void MainWindow::on_actionSaveAs_triggered()
{
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionSamplingRate_triggered()
{
    showSamplingRateDialog();
}

void MainWindow::on_actionQuantifyLevel_triggered()
{
    showQuantifyLevelDialog();
}

QString MainWindow::getUserPath()
{
    QString userPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    return userPath;
}
