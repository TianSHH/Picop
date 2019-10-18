#include "dialogpowertransformation.h"

DialogPowerTransformation::DialogPowerTransformation(QWidget *parent) : QDialog(parent)
{
    setup();

    setAttribute(Qt::WA_DeleteOnClose);

    paintFunctionImage(doubleSpinBoxArgC->value(), doubleSpinBoxArgR->value(), doubleSpinBoxArgB->value());

    connect(doubleSpinBoxArgC, SIGNAL(valueChanged(double)), this, SLOT(on_doubleSpinBoxArgC_valueChanged(double)));
    connect(doubleSpinBoxArgR, SIGNAL(valueChanged(double)), this, SLOT(on_doubleSpinBoxArgR_valueChanged(double)));
    connect(doubleSpinBoxArgB, SIGNAL(valueChanged(double)), this, SLOT(on_doubleSpinBoxArgB_valueChanged(double)));

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(emitSignalPowerTransformationStart()));
    connect(ptr, SIGNAL(signalSendImage(QImage *)), this, SLOT(powerTransformation(QImage *)));
}

DialogPowerTransformation::~DialogPowerTransformation()
{
}

void DialogPowerTransformation::setup()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("DialogLogTrans"));
    this->setFixedSize(400, 300);

    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    labelArgC = new QLabel(this);
    labelArgC->setObjectName(QStringLiteral("labelArgC"));

    labelArgR = new QLabel(this);
    labelArgR->setObjectName(QStringLiteral("labelArgR"));

    labelArgB = new QLabel(this);
    labelArgB->setObjectName(QStringLiteral("labelArgB"));

    doubleSpinBoxArgC = new QDoubleSpinBox(this);
    doubleSpinBoxArgC->setObjectName(QStringLiteral("doubleSpinBoxArgC"));
    doubleSpinBoxArgC->setValue(1);

    doubleSpinBoxArgR = new QDoubleSpinBox(this);
    doubleSpinBoxArgR->setObjectName(QStringLiteral("doubleSpinBoxArgR"));
    doubleSpinBoxArgR->setValue(1);

    doubleSpinBoxArgB = new QDoubleSpinBox(this);
    doubleSpinBoxArgB->setObjectName(QStringLiteral("doubleSpinBoxArgB"));
    doubleSpinBoxArgB->setValue(1);

    customPlot = new QCustomPlot(this);
    customPlot->setObjectName(QStringLiteral("customPlot"));

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal); // 设置 buttonBox 内部的布局
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

    gridLayout->addWidget(labelArgC, 0, 0);
    gridLayout->addWidget(labelArgR, 1, 0);
    gridLayout->addWidget(labelArgB, 2, 0);
    gridLayout->addWidget(doubleSpinBoxArgC, 0, 1);
    gridLayout->addWidget(doubleSpinBoxArgR, 1, 1);
    gridLayout->addWidget(doubleSpinBoxArgB, 2, 1);
    gridLayout->addWidget(customPlot, 0, 2, 3, 4); // 高度3行, 宽度4列
    gridLayout->addWidget(buttonBox, 3, 0, 1, 6);

    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    this->setLayout(gridLayout);

    retranslate();
} // setup

void DialogPowerTransformation::retranslate()
{
    this->setWindowTitle("设定幂次变换参数");

    labelArgC->setText(QApplication::translate("设定对数变换参数", "c ", Q_NULLPTR));
    labelArgR->setText(QApplication::translate("设定对数变换参数", "r ", Q_NULLPTR));
    labelArgB->setText(QApplication::translate("设定对数变换参数", "b ", Q_NULLPTR));
} // retranslate

// 幂次灰度变换 y=c*x^r+b
void DialogPowerTransformation::paintFunctionImage(double c, double r, double b)
{

    QVector<double> x(5101), y(5101);

    for (int i = 0; i < 5101; i++)
    {
        x[i] = i / 20.0;
        y[i] = c * qPow(x[i] / 255, r) * 255 + b;
    }

    // 创建图像并分配数据
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);

    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");

    customPlot->xAxis->setRange(0, 255);
    customPlot->yAxis->setRange(0, 255);
} // paintFunctionImage

void DialogPowerTransformation::on_doubleSpinBoxArgC_valueChanged(double arg)
{
    qDebug() << "doubleSpinBoxArgC参数改变";
    paintFunctionImage(arg, doubleSpinBoxArgR->value(), doubleSpinBoxArgB->value());
} // on_doubleSpinBoxArgC_valueChanged

void DialogPowerTransformation::on_doubleSpinBoxArgR_valueChanged(double arg)
{
    qDebug() << "doubleSpinBoxArgR参数改变";
    paintFunctionImage(doubleSpinBoxArgC->value(), arg, doubleSpinBoxArgB->value());
} // on_doubleSpinBoxArgR_valueChanged

void DialogPowerTransformation::on_doubleSpinBoxArgB_valueChanged(double arg)
{
    qDebug() << "doubleSpinBoxArgB参数改变";
    paintFunctionImage(doubleSpinBoxArgC->value(), doubleSpinBoxArgR->value(), arg);
} // on_doubleSpinBoxArgB_valueChanged

void DialogPowerTransformation::powerTransformation(QImage *originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行幂次变换";

    int width = originImage->width();
    int height = originImage->height();

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // ! logx(y) = ln(y)/ln(x)
            // y = c * x ^ r + b

            QColor color = QColor(originImage->pixel(i, j));

            int r = doubleSpinBoxArgC->value() * qPow(color.red() / 255.0, doubleSpinBoxArgR->value()) * 255 + doubleSpinBoxArgB->value();
            int g = doubleSpinBoxArgC->value() * qPow(color.green() / 255.0, doubleSpinBoxArgR->value()) * 255 + doubleSpinBoxArgB->value();
            int b = doubleSpinBoxArgC->value() * qPow(color.blue() / 255.0, doubleSpinBoxArgR->value()) * 255 + doubleSpinBoxArgB->value();

            r = qBound(0, r, 255);
            g = qBound(0, g, 255);
            b = qBound(0, b, 255);

            originImage->setPixel(i, j, qRgb(r, g, b));
        }
    }

    emit signalPowerTransformationEnd((QImage &)(*originImage));
} // powerTransformation

void DialogPowerTransformation::emitSignalPowerTransformationStart()
{
    emit signalPowerTransformationStart();
}
