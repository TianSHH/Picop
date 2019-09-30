#include "dialogquantifylevel.h"

DialogQuantifyLevel::DialogQuantifyLevel(QWidget *parent) : QDialog(parent)
{
    setup();
    retranslate();
    setAttribute(Qt::WA_DeleteOnClose);

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(emitSignalSetQuantifyLevel()));
    connect(ptr, SIGNAL(signalSendImage(QImage *)), this, SLOT(setQuantifyLevel(QImage *)), Qt::UniqueConnection);
}

DialogQuantifyLevel::~DialogQuantifyLevel()
{
}

void DialogQuantifyLevel::setup()
{
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("DialogQuantifyLevel"));
    this->resize(400, 112);

    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    label = new QLabel(this);
    label->setObjectName(QStringLiteral("label"));

    gridLayout->addWidget(label, 0, 0, 1, 1);

    lineEdit = new QLineEdit(this);
    lineEdit->setObjectName(QStringLiteral("lineEdit"));

    gridLayout->addWidget(lineEdit, 1, 0, 1, 1);

    buttonBox = new QDialogButtonBox(this);
    buttonBox->setObjectName(QStringLiteral("buttonBox"));
    buttonBox->setOrientation(Qt::Horizontal);
    buttonBox->setStandardButtons(QDialogButtonBox::Cancel | QDialogButtonBox::Ok);

    gridLayout->addWidget(buttonBox, 2, 0, 1, 1);

    retranslate();
    QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QMetaObject::connectSlotsByName(this);
} // setup

void DialogQuantifyLevel::retranslate()
{
    this->setWindowTitle(QApplication::translate("DialogQuantifyLevel", "Dialog", Q_NULLPTR));
    label->setText(QApplication::translate("DialogQuantifyLevel", "输入量化等级", Q_NULLPTR));
} // retranslate

void DialogQuantifyLevel::emitSignalSetQuantifyLevel()
{
    int level = lineEdit->text().toInt();

    if (lineEdit->text().isEmpty())
        return;

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "设定量化等级" << level;

    emit signalSetQuantifyLevel();
} // emitSignalSetQuantifyLevel

void DialogQuantifyLevel::setQuantifyLevel(QImage *originImage)
{
    int level = lineEdit->text().toInt();

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "修改量化等级" << level;

    if (level <= 1 || level >= 257)
    {
        qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                           << "量化等级范围 2-256";
        return;
    }

    int width = originImage->width();
    int height = originImage->height();

    // 区间长度
    int length = 256 / (level - 1);

    // 遍历像素点
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // 获取该点灰度值
            QColor color(originImage->pixel(i, j));
            int gray = color.red();

            int left = 0;
            int right = length - 1;

            // 对于某一个像素点, 开始判断它的灰度值处于哪个区间
            while (right <= 255)
            {

                if ((left <= gray) && (gray <= right))
                {
                    if (right - gray <= gray - left)
                    {
                        originImage->setPixel(i, j, qRgb(right, right, right));
                        break;
                    }
                    else
                    {
                        originImage->setPixel(i, j, qRgb(left, left, left));
                        break;
                    }
                }
                else
                {
                    left += length;
                    right += length;
                }
            }
        }
    }

    emit signalSetQuantifyLevelFinished((QImage &)(*originImage));
} // setQuantifyLevel
