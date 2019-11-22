#include "dialogrotation.h"

DialogRotation::DialogRotation(QWidget *parent) : QDialog(parent)
{
    setup();
    retranslate();

    setAttribute(Qt::WA_DeleteOnClose);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(emitSignalRotationEnd()));
    connect(ptr, SIGNAL(signalSendImage(QImage *)), this, SLOT(Rotate(QImage *)));
}

DialogRotation::~DialogRotation()
{
}

void DialogRotation::setup()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("DialogRotation"));
    this->setFixedSize(400, 112);

    labelAngle = new QLabel(this);
    labelAngle->setObjectName(QStringLiteral("labelAngle"));

    lineEditAngle = new QLineEdit(this);
    lineEditAngle->setObjectName(QStringLiteral("lineEditAngle"));

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    gridLayout->addWidget(labelAngle, 0, 0);
    gridLayout->addWidget(lineEditAngle, 0, 1);
    gridLayout->addWidget(buttonBox, 1, 0, 1, 1);

    retranslate();

    QMetaObject::connectSlotsByName(this);
} // setup

void DialogRotation::retranslate()
{
    this->setWindowTitle(QApplication::translate("DialogRotation", "Dialog", Q_NULLPTR));

    labelAngle->setText(QApplication::translate("DialogRotation", "设定旋转角度", Q_NULLPTR));
} // retranslate

void DialogRotation::emitSignalRotationEnd()
{
    emit signalRotationStart();
} // emitSignaRotationEnd

void DialogRotation::Rotate(QImage *originImage)
{
    double factor = M_PI / 180.0;
    // 取模
    int angle = (lineEditAngle->text().toInt()) % 360;
    double radian = angle * factor;

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "图像旋转,"
                       << "旋转角度:" << angle << ";"
                       << "旋转弧度:" << radian;

    int width = originImage->width();
    int height = originImage->height();

    cv::Mat src, dst;

    FormatMethod _formatMethod;

    src = _formatMethod.toMat(*originImage);

    int maxBorder = (int)(cv::max(src.cols, src.rows) * 1.414); // 即为sqrt(2)*max
    int dx = (maxBorder - src.cols) / 2;
    int dy = (maxBorder - src.rows) / 2;
    copyMakeBorder(src, dst, dy, dy, dx, dx, cv::BORDER_CONSTANT);

    // 旋转
    cv::Point2f center((float)(dst.cols / 2), (float)(dst.rows / 2));
    cv::Mat affine_matrix = getRotationMatrix2D(center, angle, 1.0); // 求得旋转矩阵
    warpAffine(dst, dst, affine_matrix, dst.size());

    // 计算图像旋转之后包含图像的最大的矩形
    float sinVal = abs(sin(radian));
    float cosVal = abs(cos(radian));
    cv::Size targetSize((int)(src.cols * cosVal + src.rows * sinVal),
                        (int)(src.cols * sinVal + src.rows * cosVal));

    // 剪掉多余边框
    int x = (dst.cols - targetSize.width) / 2;
    int y = (dst.rows - targetSize.height) / 2;
    cv::Rect rect(x, y, targetSize.width, targetSize.height);
    dst = cv::Mat(dst, rect);

    QImage targetImage = _formatMethod.toQImage(dst);

    emit signalRotationEnd((QImage &)targetImage);

} // Rotate
