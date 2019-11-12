#include "FilterMethod.h"

FilterMethod::FilterMethod(QWidget *parent) : QDialog(parent)
{
    setup();

    setAttribute(Qt::WA_DeleteOnClose);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(emitSignalFilterStart()));
    connect(ptr, SIGNAL(signalSendImage(QImage *)), this, SLOT(collectKernelInfo(QImage *)));
}

FilterMethod::~FilterMethod()
{
}

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
                       << "进行图像滤波"
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
    // if (filterSize%2==0)
    //     filterSize +=1;
    int len = filterSize / 2;
    int lenLimit = len;

    if (filterSize % 2 == 0)
        lenLimit = len - 1;
    else
        lenLimit = len;

    int a;

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

            r = qBound(0, r, 255);
            g = qBound(0, g, 255);
            b = qBound(0, b, 255);

            targetImage.setPixel(i - len, j - len, qRgb(r, g, b));
        }
    }

    if (flag == false)
        return targetImage;
    else
        emit signalFilterEnd(targetImage);
} // filtering

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