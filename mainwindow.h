#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialogquantifylevel.h"
#include "dialogsamplingrate.h"
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QImage>
#include <QImageReader>
#include <QMainWindow>
#include <QMessageBox>
#include <QStandardPaths>

#define WINDOW_TITLE "ImageQt"
#define WINDOW_CRITICAL "Error - ImageQt"
#define WINDOW_WARNING "Notice - ImageQt"
#define WINDOW_ABOUT "About - ImageQt"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void updateRightImage(QImage &newImage);

private slots:
    void showSamplingRateDialog();
    void samplingRate(const int &rate);

    void showQuantifyLevelDialog();
    void quantifyLevel(const int &level);

    void on_actionOpen_triggered();
    void on_actionSave_triggered();
    void on_actionQuit_triggered();
    void on_actionSamplingRate_triggered();
    void on_actionQuantifyLevel_triggered();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *leftScene;
    QGraphicsScene *rightScene;
    QGraphicsPixmapItem *leftPixmapItem;
    QGraphicsPixmapItem *rightPixmapItem;

    QFileInfo *info;
    QString imagePath; // 当前打开图像的路径

    QString getUserPath(); // 获取当前用户所在根目录
};

#endif // MAINWINDOW_H
