// TODO 将“设定灰度阀值”中的图像二值化方法封装
#include "EdgeMethod.h"

EdgeMethod::EdgeMethod()
{
}

EdgeMethod::~EdgeMethod()
{
}

QImage EdgeMethod::sobel(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "边缘检测"
                       << "方法"
                       << "Sobel算子";

    ColorMethod _colorMethod = ColorMethod();
    originImage = _colorMethod.toGrayImage(originImage);

    FilterMethod _filterMethod(nullptr);
    QImage targetImage = _filterMethod.sobel(originImage);

    return targetImage;
    // return targetImage;
} // sobel

QImage EdgeMethod::prewitt(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "边缘检测"
                       << "方法"
                       << "Prewitt算子";

    ColorMethod _colorMethod = ColorMethod();
    originImage = _colorMethod.toGrayImage(originImage);

    FilterMethod _filterMethod(nullptr);
    QImage targetImage = _filterMethod.prewitt(originImage);

    return targetImage;
} // prewitt

QImage EdgeMethod::laplacian(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "边缘检测"
                       << "方法"
                       << "Laplacian算子";

    ColorMethod _colorMethod = ColorMethod();
    originImage = _colorMethod.toGrayImage(originImage);

    FilterMethod _filterMethod(nullptr);
    QImage targetImage = _filterMethod.laplacian(originImage);

    return targetImage;
} // laplacian

// 边缘跟踪
QImage EdgeMethod::edgeTracing(QImage originImage)
{
    int width = originImage.width();
    int height = originImage.height();

    QImage middleImage = QImage(width, height, QImage::Format_RGB888);
    QImage targetImage = QImage(width, height, QImage::Format_RGB888);

    targetImage.fill(Qt::white);
    middleImage.fill(Qt::white);

    // 二值化
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            int gray = qGray(originImage.pixel(i, j));

            if (gray > 128)
                gray = 255;
            else
                gray = 0;

            middleImage.setPixel(i, j, qRgb(gray, gray, gray));
        }
    }

    int pixels[8] = {0}; // 目标像素周围的 8 个像素

    for (int i = 1; i < width - 1; i++)
    {
        for (int j = 1; j < height - 1; j++)
        {
            memset(pixels, 0, sizeof(pixels));

            if (QColor(middleImage.pixel(i, j)).red() == 0)
            {
                targetImage.setPixel(i, j, qRgb(0, 0, 0));
                pixels[0] = QColor(middleImage.pixel(i - 1, j - 1)).red();
                pixels[1] = QColor(middleImage.pixel(i - 1, j)).red();
                pixels[2] = QColor(middleImage.pixel(i - 1, j + 1)).red();
                pixels[3] = QColor(middleImage.pixel(i, j - 1)).red();
                pixels[4] = QColor(middleImage.pixel(i, j + 1)).red();
                pixels[5] = QColor(middleImage.pixel(i + 1, j - 1)).red();
                pixels[6] = QColor(middleImage.pixel(i + 1, j)).red();
                pixels[7] = QColor(middleImage.pixel(i + 1, j + 1)).red();

                if (pixels[0] + pixels[1] + pixels[2] + pixels[3] + pixels[4] + pixels[5] + pixels[6] + pixels[7] == 0)
                    targetImage.setPixel(i, j, qRgb(255, 255, 255));
            }
        }
    }

    return targetImage;
} // edgeTracing

QImage EdgeMethod::lineDetection(QImage originImage)
{
    // 选取图片左上角为原点
    int width = originImage.width();
    int height = originImage.height();

    // 直线的极坐标方程
    // r = xcosθ + ysinθ

    double rMaxDouble = qSqrt(qPow(width, 2) + qPow(height, 2));
    int rMax = (int)(rMaxDouble + 0.5); // 获取 r 的最大取值
    int thetaMax = 360;

    // 定义累加器
    struct stru
    {
        int r;
        int theta;
        int count;
    } *pAccumulator = NULL;

    int accuLen = (rMax + 1) * (thetaMax + 1);
    pAccumulator = new stru[accuLen * sizeof(stru)];

    // 初始化累加器
    memset(pAccumulator, 0, accuLen * sizeof(stru));

    // 获取边缘跟踪之后的图片
    QImage middleImage = edgeTracing(originImage);

    for (int i = 0; i < width; i++)
        for (int j = 0; j < height; j++)
            if (qGray(middleImage.pixel(i, j)) > 0)            // 对于每个边缘点
                for (int theta = 0; theta < thetaMax; theta++) // 让 theta 取遍所有可能值
                {
                    int r = i * qCos(theta) + j * qSin(theta);
                    if (r >= 0 && r < rMax)
                    {
                        int index = r * (thetaMax + 1) + theta;
                        pAccumulator[index].r = r;
                        pAccumulator[index].theta = theta;
                        pAccumulator[index].count++;
                    }
                }

    // 排序

    QPainter myPainter;

    QImage targetImage = originImage;

    myPainter.begin(&targetImage);
    myPainter.setPen(Qt::green);

    int lineNum = 3; // 绘制3条直线

    for (int i = 0; i < lineNum; i++)
    {
    }

    // 绘制直线
} // lineDetection