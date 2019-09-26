#include "mainwindow.h"
#include "ui_mainwindow.h"

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
}

void MainWindow::on_actionOpen_triggered()
{
    // Automatically detects the current user's home directory
    // And then wait the user to select one image
    QString imagePath = QFileDialog::getOpenFileName(this, tr("Open image"), getUserPath() + "/Pictures",
                                                     tr("All Files (*);;"
                                                        "All Images (*.bpm *.gif *.jpg *.jpeg *.png *.ppm *.xbm *.xpm);;"
                                                        "Image BPM (*.bpm);;"
                                                        "Image GIF (*.gif);;"
                                                        "Image JPG (*.jpg);;"
                                                        "Image JPEG (*.jpeg);;"
                                                        "Image PNG (*.png);;"
                                                        "Image PPM (*.ppm);;"
                                                        "Image XBM (*.xbm);;"
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

QString MainWindow::getUserPath()
{
    QString userPath = QStandardPaths::writableLocation(QStandardPaths::HomeLocation);
    return userPath;
}

void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionSamplingRate_triggered()
{
    QImage originImage = rightPixmapItem->pixmap().toImage();
    QImage newImage = rightPixmapItem->pixmap().toImage();

    int samplingRate = 4;

    int width = newImage.width();
    int height = newImage.height();

    int r, g, b;

    QColor color;

    for (int i = 1; i <= height; i += samplingRate)
        for (int j = 1; j <= width; j += samplingRate)
        {
            color = QColor(originImage.pixel(i, j));
            r = color.red();
            g = color.green();
            b = color.blue();

            newImage.setPixel(i + 1, j + 1, qRgb(r, g, b));

            for (int p = 0; p < samplingRate && i + p <= height; p++)
                for (int q = 0; q < samplingRate && j + q <= width; q++)
                    newImage.setPixel(i + p, j + q, qRgb(r, g, b));
        }

    updateRightImage(newImage);

    qDebug() << "Done!";
}
