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

    int kernel[5][5] = {{0, 0, 1, 0, 0},
                        {0, 1, 3, 1, 0},
                        {1, 3, 7, 3, 1},
                        {0, 1, 3, 1, 0},
                        {0, 0, 1, 0, 0}};


    int kernelSize = 5;
    int sumKernel = 27;
    int r, g, b;
    QColor color;

    qDebug() << newImage.width();
    qDebug() << newImage.height();

    for (int x = kernelSize / 2; x < newImage.width() - (kernelSize / 2); x++)
    {
        for (int y = kernelSize / 2; y < newImage.height() - (kernelSize / 2); y++)
        {

            r = 0;
            g = 0;
            b = 0;

            for (int i = -kernelSize / 2; i <= kernelSize / 2; i++)
            {
                for (int j = -kernelSize / 2; j <= kernelSize / 2; j++)
                {
                    color = QColor(originImage.pixel(x + i, y + j));
                    r += color.red() * kernel[kernelSize / 2 + i][kernelSize / 2 + j];
                    g += color.green() * kernel[kernelSize / 2 + i][kernelSize / 2 + j];
                    b += color.blue() * kernel[kernelSize / 2 + i][kernelSize / 2 + j];
                }
            }

            r = qBound(0, r / sumKernel, 255);
            g = qBound(0, g / sumKernel, 255);
            b = qBound(0, b / sumKernel, 255);

            newImage.setPixel(x, y, qRgb(r, g, b));
        }
    }
    //    rightScene->addPixmap(QPixmap::fromImage(newImage));

    qDebug() << "???";

    //    newImage.load("/home/xhls/Pictures/asuka.jpg");
    updateRightImage(newImage);

    qDebug() << "Done!";
}
