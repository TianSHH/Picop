#include "ColorMethod.h"

ColorMethod::ColorMethod()
{
}

ColorMethod::~ColorMethod()
{
}

QImage ColorMethod::toGrayImage(QImage originImage)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "图像灰度化处理";

    QImage targetImage(originImage.width(), originImage.height(), QImage::Format_Grayscale8);

    for (int i = 0; i < targetImage.width(); i++)
    {
        for (int j = 0; j < targetImage.height(); j++)
        {
            int g = qGray(originImage.pixel(i, j));

            targetImage.setPixelColor(i, j, qRgb(g, g, g));
        }
    }

    return targetImage;
} // toGrayImage

QImage ColorMethod::to256ColorImage(QImage originImage)
{ // median cut algorithm

    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "转化为256色图像";

    QList<QRgb> pixels;    // 将图片中所有的RGB信息以像素为单位存到列表中
    int color_count = 256; // 要得到的处理过的图片的颜色数目

    // 为了找到范围最广的颜色通道
    // 需要设定每种颜色通道的上界和下界
    int lower_red = qRed(originImage.pixel(0, 0)),
        lower_green = qGreen(originImage.pixel(0, 0)),
        lower_blue = qBlue(originImage.pixel(0, 0));
    int upper_red = 0,
        upper_green = 0,
        upper_blue = 0;

    qDebug() << 1;

    // 循环处理所有的像素, 找到每种颜色通道的上下界
    for (int x = 0; x < originImage.width(); x++)
    {
        for (int y = 0; y < originImage.height(); y++)
        {
            QRgb rgb = originImage.pixel(x, y); // Get rgb data of a particular pixel
            if (!pixels.contains(rgb))
            { // If we have the same pixel, we don't need it twice or more
                lower_red = std::min(lower_red, qRed(rgb));
                lower_green = std::min(lower_green, qGreen(rgb));
                lower_blue = std::min(lower_blue, qBlue(rgb));

                upper_red = std::max(upper_red, qRed(rgb));
                upper_green = std::max(upper_green, qGreen(rgb));
                upper_blue = std::max(upper_blue, qBlue(rgb));
                pixels.append(rgb);
            }
        }
    }

    qDebug() << 2;

    int red = upper_red - lower_red;
    int green = upper_green - lower_green;
    int blue = upper_blue - lower_blue;
    int max = std::max(std::max(red, green), blue);

    // 依据找到的分布最广的颜色通道进行排序
    qSort(pixels.begin(), pixels.end(), [max, red, green, blue](const QRgb &rgb1, const QRgb &rgb2) {
        if (max == red)                     // if red is our color that has the widest range
            return qRed(rgb1) < qRed(rgb2); // just compare their red channel
        else if (max == green)              //...
            return qGreen(rgb1) < qRed(rgb2);
        else /*if (max == blue)*/
            return qBlue(rgb1) < qBlue(rgb2);
    });

    qDebug() << 3;

    // 排序之后需要将列表的上半部分移动到另一个列表中
    // 如此便能得到两个列表, 对这两个列表, 循环同样
    // 的步骤, 知道得到 color_count 个列表

    QList<QList<QRgb>> lists;

    // 分割之后每个子列表的大小
    int list_size = pixels.size() / color_count;

    for (int i = 0; i < color_count; i++)
    {
        // 将列表 pixels 分割为 pixel_count 个列表
        QList<QRgb> list;
        for (int j = list_size * i; j < (list_size * i) + list_size; j++)
        {
            list.append(pixels.at(j));
        }
        lists.append(list);
    }

    qDebug() << 4;

    // 将每个子列表的中值作为新的调色板值
    QVector<QRgb> palette;
    for (QList<QRgb> list : lists)
    {
        palette.append(list.at(list.size() / 2));
    }

    QImage targetImage(originImage.width(), originImage.height(), QImage::Format_ARGB32);
    for (int x = 0; x < originImage.width(); x++)
    {
        for (int y = 0; y < originImage.height(); y++)
        {
            targetImage.setPixelColor(x, y, palette[closestMatch(originImage.pixel(x, y), palette)]);
        }
    }

    qDebug() << 5;

    return targetImage;
}