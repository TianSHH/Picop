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
    // // 选取图片左上角为原点
    // int width = originImage.width();
    // int height = originImage.height();

    // // 直线的极坐标方程
    // // rho = xcosθ + ysinθ

    // double rMaxDouble = qSqrt(qPow(width, 2) + qPow(height, 2));
    // int rMax = (int)(rMaxDouble + 0.5); // 获取 rho 的最大取值
    // int thetaMax = 91;

    // // 定义累加器
    // struct accumulator
    // {
    //     int rho;
    //     int theta;
    //     int count;

    //     // 结构体构造函数
    //     accumulator()
    //     {
    //         rho = -1;
    //         theta = -1;
    //         count = 0;
    //     }

    //     void setValue(int rValue, int thetaValue, int countValue)
    //     { // 结构体赋值函数
    //         rho = rValue;
    //         theta = thetaValue;
    //         count = countValue;
    //     }
    // };

    // QList<accumulator> list;

    // 获取边缘跟踪之后的图片
    // QImage middleImage = edgeTracing(originImage);

    // for (int i = 0; i < width; i++)
    //     for (int j = 0; j < height; j++)
    //     {
    //         qDebug() << i << j;
    //         if (qGray(middleImage.pixel(i, j)) == 0) // 对于每个边缘点, 边缘点是黑色
    //         {
    //             for (int theta = -90; theta < thetaMax; theta++) // 让 theta 取遍所有可能值
    //             {                                                // rho 的取值范围 [-90, 90]
    //                 double rad = theta * 2 * M_PI / 360;         // 转换为弧度
    //                 int rho = i * qCos(rad) + j * qSin(rad);     // 由弧度值和直角坐标算出 rho
    //                 if (rho >= 0 && rho < rMax)
    //                 { // rho 值可能为负

    //                     bool appear = false; // 标记 list 中是否已经存在该点, 默认不存在

    //                     for (int k = 0; k < list.length(); k++)
    //                     { // 循环判断 list 中是否存在 rho, theta 等于当前 rho, theta 的元素
    //                         if (list[k].rho == rho && list[k].theta == theta)
    //                         { // 如果有, count++, 并退出循环
    //                             list[k].count++;
    //                             appear = true;
    //                             break;
    //                         }
    //                     }
    //                     if (appear == false)
    //                     { // 若 list 中没有该点
    //                         // 则将其加入
    //                         accumulator temp;             // 若该点没出现过
    //                         temp.setValue(rho, theta, 0); // 则将其加入到 list 中
    //                         list.append(temp);
    //                     }
    //                 }
    //             }
    //         }
    //     }

    // // 以参数空间中某点被经过的次数排序, 降序
    // qSort(list.begin(), list.end(), [](const accumulator &accumlatorA, const accumulator &accumlatorB) { return accumlatorA.count > accumlatorB.count; });

    // QImage targetImage = originImage;

    // QPainter myPainter;
    // myPainter.begin(&targetImage);
    // myPainter.setPen(Qt::green);

    // int minLen = rMax / 10; // 绘制的直线最小长度为 rMax 的 20 分之一

    // for (int i = 0; list[i].count >= minLen; i++)
    // {
    //     int rho = list[i].rho;
    //     int theta = list[i].theta;

    //     if (theta == 90)
    //     { // 直线与 x 轴平行
    //         // (0, rho) => (width, rho)
    //         myPainter.setPen(Qt::red);
    //         myPainter.drawLine(0, rho, width, rho);
    //     }
    //     else if (theta == 0)
    //     { // 直线与 x 轴垂直
    //         // (rho, 0) => (rho, width)
    //         myPainter.setPen(Qt::blue);
    //         myPainter.drawLine(rho, 0, rho, height);
    //     }
    //     else
    //     { // (x, 0) => (0, y)
    //         int x = rho / qCos(theta * 2 * M_PI / 360);
    //         int y = rho / qSin(theta * 2 * M_PI / 360);

    //         myPainter.setPen(Qt::green);
    //         myPainter.drawLine(x, 0, 0, y);
    //     }
    // }

    // // 绘制直线
    // return targetImage;

    FormatMethod _formatMethod;

    Mat image = _formatMethod.toMat(originImage);

    // Mat newImage = image.clone();

    Mat cannyImage, distImage;

    // 边缘提取
    Canny(image, cannyImage, 50, 200, 3);
    // 灰度转换
    cvtColor(cannyImage, distImage, COLOR_GRAY2BGR);

    vector<Vec4i> lines;

    HoughLinesP(cannyImage, lines, 1, CV_PI / 180, 10, 50, 10);

    for (int i = 0; i < lines.size(); i++)
    {
        Vec4i l = lines[i];

        line(distImage, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(186, 88, 255), 1, LINE_AA);
    }

    return _formatMethod.toQImage(distImage);
} // lineDetection