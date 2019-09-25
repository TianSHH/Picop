#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void on_actionOpen_triggered();

    void on_actionQuit_triggered();

    void on_actionSamplingRate_triggered();

private:
    Ui::MainWindow *ui;

    QGraphicsScene *leftScene;
    QGraphicsScene *rightScene;
    QGraphicsPixmapItem *leftPixmapItem;
    QGraphicsPixmapItem *rightPixmapItem;

    QFileInfo *info;

    QString getUserPath(); // 获取当前用户所在根目录
};

#endif // MAINWINDOW_H
