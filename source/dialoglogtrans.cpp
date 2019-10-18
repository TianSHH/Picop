#include "dialoglogtrans.h"

DialogLogTrans::DialogLogTrans(QWidget *parent) : QDialog(parent)
{
    setup();

    setAttribute(Qt::WA_DeleteOnClose);

    paintFunctionImage(doubleSpinBoxArgA->value());

    connect(doubleSpinBoxArgA, SIGNAL(valueChanged(double)), this, SLOT(on_doubleSpinBoxArgA_valueChanged(double)));

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(emitSignalLogTransStart()));
    connect(ptr, SIGNAL(signalSendImage(QImage *)), this, SLOT(logTrans(QImage *)));
}

DialogLogTrans::~DialogLogTrans()
{
}

void DialogLogTrans::setup()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("DialogLogTrans"));
    this->setFixedSize(400, 300);

    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));

    labelArgA = new QLabel(this);
    labelArgA->setObjectName(QStringLiteral("labelArgA"));

    doubleSpinBoxArgA = new QDoubleSpinBox(this);
    doubleSpinBoxArgA->setObjectName(QStringLiteral("doubleSpinBoxArgA"));
    doubleSpinBoxArgA->setValue(1);

    customPlot = new QCustomPlot(this);
    customPlot->setObjectName(QStringLiteral("customPlot"));

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal); // 设置 buttonBox 内部的布局
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

    gridLayout->addWidget(labelArgA, 1, 0);
    gridLayout->addWidget(doubleSpinBoxArgA, 1, 1);
    gridLayout->addWidget(customPlot, 0, 2, 3, 4); // 高度3行, 宽度4列
    gridLayout->addWidget(buttonBox, 3, 0, 1, 6);

    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    this->setLayout(gridLayout);

    retranslate();
} // setup

void DialogLogTrans::retranslate()
{
    this->setWindowTitle("设定对数变换参数");

    labelArgA->setText(QApplication::translate("设定对数变换参数", "a ", Q_NULLPTR));
} // retranslate

void DialogLogTrans::paintFunctionImage(double a)
{
    QVector<double> x(5101), y(5101);

    for (int i = 0; i < 5101; ++i)
    {
        x[i] = i / 20.0;
        y[i] = qLn(1 + a * x[i] / 255) / qLn(a + 1) * 255;
    }

    // 创建图像并分配数据
    customPlot->addGraph();
    customPlot->graph(0)->setData(x, y);

    customPlot->xAxis->setLabel("x");
    customPlot->yAxis->setLabel("y");

    customPlot->xAxis->setRange(0, 255);
    customPlot->yAxis->setRange(0, 255);
    customPlot->replot();
} // paintFunctionImage

void DialogLogTrans::on_doubleSpinBoxArgA_valueChanged(double arg)
{
    qDebug() << "doubleSpinBoxArgA参数改变";
    paintFunctionImage(arg);
} // on_doubleSpinBoxArgA_valueChanged

void DialogLogTrans::logTrans(QImage *originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "进行对数变换";

    int width = originImage->width();
    int height = originImage->height();

    // QImage *newImage = new QImage(width, height, QImage::Format_ARGB32);

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            QColor color = QColor(originImage->pixel(i, j));

            // ! logx(y)=ln(y)/ln(x)
            // y = c * log(b + 1)(1 + b * x / 255) * 255

            int r = qLn(1 + doubleSpinBoxArgA->value() * color.red() / 255) / qLn(1 + doubleSpinBoxArgA->value()) * 255;
            int g = qLn(1 + doubleSpinBoxArgA->value() * color.green() / 255) / qLn(1 + doubleSpinBoxArgA->value()) * 255;
            int b = qLn(1 + doubleSpinBoxArgA->value() * color.blue() / 255) / qLn(1 + doubleSpinBoxArgA->value()) * 255;

            r = qBound(0, r, 255);
            g = qBound(0, g, 255);
            b = qBound(0, b, 255);

            originImage->setPixel(i, j, qRgb(r, g, b));
        }
    }

    emit signalLogTransEnd((QImage &)(*originImage));
} // logTrans

void DialogLogTrans::emitSignalLogTransStart()
{
    emit signalLogTransStart();
} // emitSignalLogTransStart
