#include "FilterMethod.h"

FilterMethod::FilterMethod()
{
}

FilterMethod::~FilterMethod()
{
}

QImage FilterMethod::filtering(QImage originImage, int filterSize, int *filterTemplateArray)
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

    return targetImage;
} // filtering

void FilterMethod::getFilterInfo(QImage originImage)
{
    bool ok;

    int filterSize = QInputDialog::getInt(nullptr, QObject::tr("获取卷积核大小"), "输入卷积核大小(1~30)", 3, 1, 30, 1, &ok);

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "自定义卷积核"
                       << "卷积核大小" << filterSize << "X" << filterSize;

    if (ok == true)
    {
        QDialog *_dialog = new QDialog(nullptr);

        QGridLayout *_gridLayout = new QGridLayout(_dialog);
        _gridLayout->setObjectName(QStringLiteral("_gridLayout"));

        QTableWidget *tableWidget = new QTableWidget(filterSize, filterSize);
        tableWidget->setWindowTitle("设置卷积核");
        tableWidget->setEditTriggers(QAbstractItemView::CurrentChanged); // 设置编辑方式为可编辑

        // 初始化卷积核
        for (int i = 0; i < filterSize; i++)
        {
            for (int j = 0; j < filterSize; j++)
            {
                tableWidget->setColumnWidth(j, 30);
                tableWidget->setRowHeight(i, 30);
                tableWidget->setItem(i, j, new QTableWidgetItem());
                tableWidget->item(i, j)->setTextAlignment(Qt::AlignCenter);
                tableWidget->item(i, j)->setBackground(QColor(85, 170, 255));
                if ((i == filterSize / 2) && (j == filterSize / 2))
                    tableWidget->item(i, j)->setText("1");
                else
                    tableWidget->item(i, j)->setText("0");
            }
        }
        tableWidget->show();
        _gridLayout->addWidget(tableWidget, 0, 0, 1, 1);

        QDialogButtonBox *buttonBox;
        buttonBox = new QDialogButtonBox();
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
        _gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

        _dialog->setLayout(_gridLayout);
        _dialog->resize(filterSize * 30 + 37, filterSize * 30 + 76);
        _dialog->show();

        // 起初是将所有的组件放到了 QWidget
        // 但是 QWidget 中并没有 SLOT accept() 和 reject()
        // 所以将容纳 QTableWidget 和 QButtonBox 的容器
        // 换成 QDialog
        }

    // return this->filtering(originImage, filterSize, filterTemplateArray);
} // getFilterInfo