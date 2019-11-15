#include "FilterMethod.h"

FilterMethod::FilterMethod(QWidget *parent) : QDialog(parent)
{
    if (parent != nullptr)
    { // FilterMethod 没有父窗口,
        // 即只使用 filtering 方法
        // 不自定义滤波模板
        setup();

        setAttribute(Qt::WA_DeleteOnClose);

        connect(buttonBox, SIGNAL(accepted()), this, SLOT(emitSignalFilterStart()));
        connect(ptr, SIGNAL(signalSendImage(QImage *)), this, SLOT(collectKernelInfo(QImage *)));
    }
}

FilterMethod::~FilterMethod()
{
}

// 自定义卷积核时, 显示自定义界面
void FilterMethod::setup()
{
    bool ok;

    this->filterSize = QInputDialog::getInt(nullptr, QObject::tr("获取卷积核大小"), "输入卷积核大小(1~30)", 3, 1, 30, 1, &ok);

    if (ok)
    {
        _dialog = new QDialog(nullptr);

        _gridLayout = new QGridLayout(_dialog);
        _gridLayout->setObjectName(QStringLiteral("_gridLayout"));

        kernelTable = new QTableWidget();
        kernelTable->setWindowTitle("设置卷积核");
        kernelTable->setEditTriggers(QAbstractItemView::CurrentChanged); // 设置编辑方式为可编辑
        // 若预先不设置 kernelTable 的行列数
        // 初始化没问题
        // 但读取 kernelTable 中数据时, 只能获得第一行数据
        kernelTable->setColumnCount(filterSize);
        kernelTable->setRowCount(filterSize);

        // 初始化卷积核
        for (int i = 0; i < kernelTable->rowCount(); i++)
        {
            for (int j = 0; j < kernelTable->columnCount(); j++)
            {
                kernelTable->setColumnWidth(j, 30);
                kernelTable->setRowHeight(i, 30);
                kernelTable->setItem(i, j, new QTableWidgetItem());
                // kernelTable->item(i, j)->setTextAlignment(Qt::AlignCenter);
                kernelTable->item(i, j)->setBackground(QColor(85, 170, 255));
                if ((i == filterSize / 2) && (j == filterSize / 2))
                    kernelTable->item(i, j)->setText("1");
                else
                    kernelTable->item(i, j)->setText("0");
            }
        }
        kernelTable->show();
        _gridLayout->addWidget(kernelTable, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox();
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
        _gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

        _dialog->setLayout(_gridLayout);
        _dialog->resize(filterSize * 30 + 37, filterSize * 30 + 76);
        _dialog->show();
    }
} // setup

void FilterMethod::retranslate() {}

QImage FilterMethod::filtering(QImage originImage, int filterSize, int *filterTemplateArray, bool flag)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "图像滤波"
                       << "滤波器大小" << filterSize;

    int filterTemplateMatrix[filterSize][filterSize];

    // 由于在传递二维数组时必须指定二维数组大小
    // 所以采用传递一位数组, 之后将其转换为二维数组
    // 方便 QImage 操作
    for (int i = 0; i < filterSize; i++)
        for (int j = 0; j < filterSize; j++)
            filterTemplateMatrix[i][j] = filterTemplateArray[i * filterSize + j];

    // 不需要处理 filterSize
    // 调用 filtering 之前其父函数已做处理
    if (filterSize % 2 == 0)
        filterSize += 1;
    int len = filterSize / 2;
    int lenLimit = len;

    QImage middleImage = QImage(originImage.width() + 2 * len, originImage.height() + 2 * len, QImage::Format_RGB32);
    QImage targetImage = QImage(originImage.width(), originImage.height(), QImage::Format_RGB32);

    // 初始化 middleImage
    for (int i = 0; i < middleImage.width(); i++)
        for (int j = 0; j < middleImage.height(); j++)
            if ((i >= len) && (i < (middleImage.width() - len)) && (j >= len) && (j < (middleImage.height() - len)))
            { // 像素点不在边框中
                middleImage.setPixelColor(i, j, QColor(originImage.pixel(i - len, j - len)));
            }
            else
            { // 像素点在边框中
                middleImage.setPixelColor(i, j, Qt::white);
            }

    qDebug() << "-----------------------------------------------__>" << middleImage.height();
    qDebug() << middleImage.height() - len;

    for (int i = len; i < middleImage.width() - len; i++)
    {
        for (int j = len; j < middleImage.height() - len; j++)
        {

            int r = 0;
            int g = 0;
            int b = 0;
            for (int p = -len; p <= lenLimit; p++)
            {
                for (int q = -len; q <= lenLimit; q++)
                {
                    r += ((middleImage.pixelColor(i + p, j + q).red() * filterTemplateMatrix[len + p][len + q]));
                    g += ((middleImage.pixelColor(i + p, j + q).green() * filterTemplateMatrix[len + p][len + q]));
                    b += ((middleImage.pixelColor(i + p, j + q).blue() * filterTemplateMatrix[len + p][len + q]));
                }
            }

            //!新的像素值还要加上原来的像素值
            // int oldR = qRed(originImage.pixel(i, j));
            // r += oldR;
            r = qBound(0, r, 255);

            // int oldG = qGreen(originImage.pixel(i, j));
            // g += oldG;
            g = qBound(0, g, 255);

            // int oldB = qBlue(originImage.pixel(i, j));
            // b += oldB;
            b = qBound(0, b, 255);

            if ((i >= len) && (i < (middleImage.width() - len)) && (j >= len) && (j < (middleImage.height() - len)))
                targetImage.setPixel(i - len, j - len, qRgb(r, g, b));
        }
    }

    if (flag == false)
        return targetImage;
    else
        emit signalFilterEnd(targetImage);
} // filtering

QImage FilterMethod::merging(QImage image1, QImage image2)
{
    QImage targetImage = QImage(image1.width(), image1.height(), QImage ::Format_RGB32);

    for (int i = 0; i < image1.width(); i++)
    {
        int r = 0;
        int g = 0;
        int b = 0;
        for (int j = 0; j < image1.height(); j++)
        {
            r = qMax(qAbs(qRed(image1.pixel(i, j))), qAbs(qRed(image2.pixel(i, j))));
            g = qMax(qAbs(qGreen(image1.pixel(i, j))), qAbs(qGreen(image2.pixel(i, j))));
            b = qMax(qAbs(qBlue(image1.pixel(i, j))), qAbs(qBlue(image2.pixel(i, j))));

            // r = qSqrt((qAbs(qRed(image1.pixel(i, j))) * qAbs(qRed(image1.pixel(i, j)))) + (qAbs(qRed(image2.pixel(i, j))) * qAbs(qRed(image2.pixel(i, j)))));
            // g = qSqrt((qAbs(qGreen(image1.pixel(i, j))) * qAbs(qGreen(image1.pixel(i, j)))) + (qAbs(qGreen(image2.pixel(i, j))) * qAbs(qGreen(image2.pixel(i, j)))));
            // b = qSqrt((qAbs(qBlue(image1.pixel(i, j))) * qAbs(qBlue(image1.pixel(i, j)))) + (qAbs(qBlue(image2.pixel(i, j))) * qAbs(qBlue(image2.pixel(i, j)))));

            r = qBound(0, r, 255);
            g = qBound(0, g, 255);
            b = qBound(0, b, 255);

            targetImage.setPixel(i, j, qRgb(r, g, b));
        }
    }

    return targetImage;
} // merging

QImage FilterMethod::reborts(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行图像卷积"
                       << "方法"
                       << "Reborts算子";

    int rebortsGx[] = {0, 0, 0,
                       0, -1, 0,
                       0, 0, 1};
    int rebortsGy[] = {0, 0, 0,
                       0, 0, -1,
                       0, 1, 0};

    QImage middleImageGx = filtering(originImage, 3, rebortsGx, false);
    QImage middleImageGy = filtering(originImage, 3, rebortsGy, false);

    return merging(middleImageGx, middleImageGy);
} // reborts

QImage FilterMethod::sobel(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行图像卷积"
                       << "方法"
                       << "Sobel算子";

    int sobelGx[] = {1, 0, -1,
                     2, 0, -2,
                     1, 0, -1};
    int sobelGy[] = {-1, -2, -1,
                     0, 0, 0,
                     1, 2, 1};

    QImage middleImageGx = filtering(originImage, 3, sobelGx, false);
    QImage middleImageGy = filtering(originImage, 3, sobelGy, false);

    return merging(middleImageGx, middleImageGy);
} // sobel

QImage FilterMethod::laplacian(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行图像卷积"
                       << "方法"
                       << "Laplacian算子";

    int laplacian[] = {0, -1, 0,
                       -1, 4, -1,
                       0, -1, 0};

    return filtering(originImage, 3, laplacian, false);
} // laplacian

QImage FilterMethod::enhancedLaplacian(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行图像卷积"
                       << "方法"
                       << "Laplacian算子";

    int enhancedLaplacian[] = {0, -1, 0,
                               -1, 5, -1,
                               0, -1, 0};

    return filtering(originImage, 3, enhancedLaplacian, false);
} // enhancedLaplacian

QImage FilterMethod::prewitt(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行图像卷积"
                       << "方法"
                       << "prewitt算子";

    int prewittGx[] = {-1, 0, 1,
                       -1, 0, 1,
                       -1, 0, 1};
    int prewittGy[] = {-1, -1, -1,
                       0, 0, 0,
                       1, 1, 1};

    QImage middleImageGx = filtering(originImage, 3, prewittGx, false);
    QImage middleImageGy = filtering(originImage, 3, prewittGy, false);
    QImage targetImage = QImage(middleImageGx.width(), middleImageGx.height(), QImage ::Format_RGB32);

    for (int i = 0; i < middleImageGx.width(); i++)
    {
        int r = 0;
        int g = 0;
        int b = 0;
        for (int j = 0; j < middleImageGx.height(); j++)
        {
            r = qMax(qAbs(qRed(middleImageGx.pixel(i, j))), qAbs(qRed(middleImageGy.pixel(i, j))));
            g = qMax(qAbs(qGreen(middleImageGx.pixel(i, j))), qAbs(qGreen(middleImageGy.pixel(i, j))));
            b = qMax(qAbs(qBlue(middleImageGx.pixel(i, j))), qAbs(qBlue(middleImageGy.pixel(i, j))));

            // r = qSqrt((qAbs(qRed(middleImageGx.pixel(i, j))) * qAbs(qRed(middleImageGx.pixel(i, j)))) + (qAbs(qRed(middleImageGy.pixel(i, j))) * qAbs(qRed(middleImageGy.pixel(i, j)))));
            // g = qSqrt((qAbs(qGreen(middleImageGx.pixel(i, j))) * qAbs(qGreen(middleImageGx.pixel(i, j)))) + (qAbs(qGreen(middleImageGy.pixel(i, j))) * qAbs(qGreen(middleImageGy.pixel(i, j)))));
            // b = qSqrt((qAbs(qBlue(middleImageGx.pixel(i, j))) * qAbs(qBlue(middleImageGx.pixel(i, j)))) + (qAbs(qBlue(middleImageGy.pixel(i, j))) * qAbs(qBlue(middleImageGy.pixel(i, j)))));

            r = qBound(0, r, 255);
            g = qBound(0, g, 255);
            b = qBound(0, b, 255);

            targetImage.setPixel(i, j, qRgb(r, g, b));
        }
    }
    return targetImage;
}

void FilterMethod::collectKernelInfo(QImage *originImage)
{
    _dialog->hide();

    filterTemplateArray = new int[kernelTable->rowCount() * kernelTable->columnCount()]();

    for (int i = 0; i < kernelTable->rowCount(); i++)
        for (int j = 0; j < kernelTable->columnCount(); j++)
            filterTemplateArray[i * kernelTable->rowCount() + j] = kernelTable->item(i, j)->text().toInt();

    // 必要信息收集完毕, 开始滤波
    filtering(*originImage, filterSize, filterTemplateArray, true);
} // collectKernelInfo

void FilterMethod::emitSignalFilterStart()
{
    emit signalFilterStart();
} // emitSignalFilterStart