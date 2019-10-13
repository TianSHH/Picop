#include "dialoglinearpointoperation.h"

DialogLinearPointOperation::DialogLinearPointOperation(QWidget *parent) : QDialog(parent)
{
    setup();
    setAttribute(Qt::WA_DeleteOnClose);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(emitSignalPointLinearOperation()));
    connect(ptr, SIGNAL(signalSendImage(QImage *)), this, SLOT(pointOperation(QImage *)));
}

DialogLinearPointOperation::~DialogLinearPointOperation()
{
}

void DialogLinearPointOperation::setup()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("DialogLinearPointOperation"));
    this->resize(300, 50);

    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    lineEditSlope = new QLineEdit(this);
    lineEditSlope->setObjectName(QStringLiteral("lineEditSlope"));

    lineEditOffset = new QLineEdit(this);
    lineEditOffset->setObjectName(QStringLiteral("lineEditOffset"));

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal); // 设置 buttonBox 内部的布局
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

    gridLayout->addWidget(lineEditSlope, 0, 0);
    gridLayout->addWidget(lineEditOffset, 0, 1);
    gridLayout->addWidget(buttonBox, 0, 2);

    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    this->setLayout(gridLayout);

    retranslate();
}

void DialogLinearPointOperation::retranslate()
{
    this->setWindowTitle("设定线性点运算参数");
}

void DialogLinearPointOperation::emitSignalPointLinearOperation()
{
    int slope = lineEditSlope->text().toInt();
    int offset = lineEditOffset->text().toInt();

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "设定点线性点运算参数"
                       << "斜率:" << slope << "偏移量:" << offset;

    emit signalLinearPointOperation();
}

void DialogLinearPointOperation::pointOperation(QImage *originImage)
{
    int slope = lineEditSlope->text().toInt();
    int offset = lineEditOffset->text().toInt();

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行线性点运算, 参数,"
                       << "斜率:" << slope << "偏移量:" << offset;

    if (slope == 1 && offset == 0)
    {
        emit signalLinearPointOperationFinished((QImage &)(*originImage));
        return;
    }

    int width = originImage->width();
    int height = originImage->height();

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            QColor _color = QColor(originImage->pixel(i, j));
            int r = _color.red() * slope + offset > 255 ? 255 : (_color.red() * slope + offset < 0 ? 0 : _color.red() * slope + offset);
            int g = _color.green() * slope + offset > 255 ? 255 : (_color.green() * slope + offset < 0 ? 0 : _color.green() * slope + offset);
            int b = _color.blue() * slope + offset > 255 ? 255 : (_color.blue() * slope + offset < 0 ? 0 : _color.blue() * slope + offset);

            originImage->setPixel(i, j, qRgb(r, g, b));
        }
    }

    emit signalLinearPointOperationFinished((QImage &)(*originImage));
}
