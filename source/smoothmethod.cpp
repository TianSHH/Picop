#include "smoothmethod.h"

SmoothMethod::SmoothMethod()
{
}

SmoothMethod::~SmoothMethod()
{
}

QImage SmoothMethod::averageFiltering(QImage *originImage)
{
    bool ok;
    int filterRadius = QInputDialog::getInt(nullptr, QObject::tr("均值滤波"), "输入滤波器大小(1~30)", 3, 1, 30, 1, &ok);
    if (ok)
    {
        if (filterRadius % 2 == 0)
            filterRadius += 1;

        qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                           << "图像平滑, 方式, 均值滤波"
                           << "滤波器大小" << filterRadius;

        int kernel[filterRadius][filterRadius];

        for (int i = 0; i < filterRadius; i++)
            for (int j = 0; j < filterRadius; j++)
                kernel[i][j] = 1;

        int len = filterRadius / 2;

        int originWidth = originImage->width();
        int originHeight = originImage->height();

        QImage targetImage = QImage(originWidth + 2 * len, originHeight + 2 * len, QImage::Format_RGB32);

        // 添加边框
        for (int i = 0; i < targetImage.width(); i++)
            for (int j = 0; j < targetImage.height(); j++)
                if (i >= len && i < targetImage.width() - len && j >= len && j < targetImage.height() - len)
                { // 不在边框中
                    QColor originImageColor = QColor(originImage->pixel(i - len, j - len));
                    targetImage.setPixelColor(i, j, originImageColor);
                }
                else                                       // 在边框中
                    targetImage.setPixel(i, j, Qt::white); // 将边框中颜色设置为白色

        for (int i = len; i < targetImage.width() - len; i++)
            for (int j = len; j < targetImage.height() - len; j++)
            {

                int r = 0;
                int g = 0;
                int b = 0;

                for (int p = -len; p <= len; p++)
                    for (int q = -len; q <= len; q++)
                    {
                        r = targetImage.pixelColor(i + p, j + q).red() * kernel[len + p][len + q] + r;
                        g = targetImage.pixelColor(i + p, j + q).green() * kernel[len + p][len + q] + g;
                        b = targetImage.pixelColor(i + p, j + q).blue() * kernel[len + p][len + q] + b;
                    }

                r /= (filterRadius * filterRadius);
                g /= (filterRadius * filterRadius);
                b /= (filterRadius * filterRadius);

                if (((i - len) >= 0) && ((i - len) < originWidth) && ((j - len) >= 0) && ((j - len) < originHeight))
                    originImage->setPixel(i - len, j - len, qRgb(r, g, b));
            }
    }

    return (*originImage);
} // averageFiltering

QImage SmoothMethod::medianFiltering(QImage *originImage)
{ // originImage 格式为 Format_RGB32
    bool ok;

    int filterRadius = QInputDialog::getInt(nullptr, QObject::tr("中值滤波"), "输入滤波器大小(1~30)", 3, 1, 30, 1, &ok);

    if (ok)
    {
        if (filterRadius % 2 == 0)
            filterRadius += 1;

        qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                           << "图像平滑, 方式, 中值滤波"
                           << "滤波器大小" << filterRadius;

        int len = filterRadius / 2;
        int threshold = filterRadius * filterRadius / 2 + 1;

        int originWidth = originImage->width();
        int originHeight = originImage->height();

        QImage middleImage = QImage(originWidth + 2 * len, originHeight + 2 * len, QImage::Format_RGB32);
        QImage targetImage = QImage(originWidth, originHeight, QImage::Format_RGB32);

        // 初始化 middleImage
        for (int i = 0; i < middleImage.width(); i++)
        {
            for (int j = 0; j < middleImage.height(); j++)
            {
                if ((i >= len) && (i < (middleImage.width() - len)) && (j >= len) && (j < (middleImage.height() - len)))
                { // 像素点不在边框中
                    middleImage.setPixelColor(i, j, QColor(originImage->pixel(i - len, j - len)));
                }
                else
                { // 像素点在边框中
                    middleImage.setPixelColor(i, j, Qt::white);
                }
            }
        }

        // 使用直方图记录窗口中出现的像素的出现次数
        int redHist[256] = {0};
        int greenHist[256] = {0};
        int blueHist[256] = {0};
        int grayHist[256] = {0};

        for (int i = len; i < middleImage.width() - len; i++)
        {
            for (int j = len; j < middleImage.height() - len; j++)
            {
                // 设置窗口
                if (j == len)
                { // 每到新的一列, 初始化直方图
                    memset(redHist, 0, sizeof(redHist));
                    memset(greenHist, 0, sizeof(greenHist));
                    memset(blueHist, 0, sizeof(blueHist));
                    memset(grayHist, 0, sizeof(grayHist));

                    for (int p = -len; p <= len; p++)
                    {
                        for (int q = -len; q <= len; q++)
                        {
                            int red = qRed(middleImage.pixel(i + p, j + q));
                            int green = qGreen(middleImage.pixel(i + p, j + q));
                            int blue = qBlue(middleImage.pixel(i + p, j + q));
                            int gray = qGray(middleImage.pixel(i + p, j + q));

                            redHist[red]++;
                            greenHist[green]++;
                            blueHist[blue]++;
                            grayHist[gray]++;
                        }
                    }
                }
                else
                { // 列数增加, 窗口按列向下移动, 为窗口新添加一行像素值, 并删去一行像素值
                    int oldWindowStartCol = j - len - 1;
                    int newWindowEndCol = j + len;

                    for (int p = -len; p <= len; p++)
                    {
                        // 要减去的列的像素值, 从窗口上到窗口下, 即 [j-len,j+len]
                        int red = qRed(middleImage.pixel(i + p, oldWindowStartCol));
                        int green = qGreen(middleImage.pixel(i + p, oldWindowStartCol));
                        int blue = qBlue(middleImage.pixel(i + p, oldWindowStartCol));
                        int gray = qGray(middleImage.pixel(i + p, oldWindowStartCol));

                        redHist[red]--;
                        greenHist[green]--;
                        blueHist[blue]--;
                        grayHist[gray]--;

                        red = qRed(middleImage.pixel(i + p, newWindowEndCol));
                        green = qGreen(middleImage.pixel(i + p, newWindowEndCol));
                        blue = qBlue(middleImage.pixel(i + p, newWindowEndCol));
                        gray = qGray(middleImage.pixel(i + p, newWindowEndCol));

                        redHist[red]++;
                        greenHist[green]++;
                        blueHist[blue]++;
                        grayHist[gray]++;
                    }
                }

                // 获取窗口内像素中值
                int r = getMedianValue(redHist, threshold);
                int g = getMedianValue(greenHist, threshold);
                int b = getMedianValue(blueHist, threshold);

                targetImage.setPixel(i - len, j - len, qRgb(r, g, b));
            }
        }

        return targetImage;
    }
} // medianFiltering

// 获取窗口中像素的中值
int SmoothMethod::getMedianValue(const int *histogram, int threshold)
{
    int sum = 0;
    for (int i = 0; i < 256; i++)
    {
        sum += histogram[i];
        if (sum >= threshold)
            return i;
    }
    return 255;
} // getMedianValue

QImage SmoothMethod::KNNF(QImage originImage)
{
    bool ok1;
    bool ok2;

    int filterRadius = QInputDialog::getInt(nullptr, QObject::tr("K近邻均值滤波"), "输入滤波器大小(1~30)", 3, 1, 30, 1, &ok1);
    int K = QInputDialog::getInt(nullptr, QObject::tr("K近邻均值平滑"), "输入K值", 1, 1, 30, 1, &ok2);

    if (ok1 & ok2)
    {
        if (filterRadius % 2 == 0)
            filterRadius += 1;

        qDebug().noquote().nospace() << "[Debug] " << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ": "
                                     << "图像平滑, 方式, K近邻均值滤波, "
                                     << "滤波器大小, " << filterRadius << ", "
                                     << "K值, " << K;

        // int kernel[filterRadius][filterRadius];

        // for (int i = 0; i < filterRadius; i++)
        //     for (int j = 0; j < filterRadius; j++)
        //         kernel[i][j] = 1;

        int len = filterRadius / 2;

        int originWidth = originImage.width();
        int originHeight = originImage.height();

        QImage middleImage = QImage(originWidth + 2 * len, originHeight + 2 * len, QImage::Format_RGB32);
        QImage targetImage = QImage(originWidth, originHeight, QImage::Format_RGB32);

        // 添加边框
        for (int i = 0; i < middleImage.width(); i++)
            for (int j = 0; j < middleImage.height(); j++)
                if (i >= len && i < middleImage.width() - len && j >= len && j < middleImage.height() - len)
                { // 不在边框中
                    middleImage.setPixelColor(i, j, QColor(originImage.pixel(i - len, j - len)));
                }
                else
                {                                          // 在边框中
                    middleImage.setPixel(i, j, Qt::white); // 将边框中颜色设置为白色
                }

        int redHist[256] = {0};
        int greenHist[256] = {0};
        int blueHist[256] = {0};

        for (int i = len; i < middleImage.width() - len; i++)
            for (int j = len; j < middleImage.height() - len; j++)
            {
                // 设置窗口
                if (j == len)
                { // 每到新的一列, 初始化直方图
                    memset(redHist, 0, sizeof(redHist));
                    memset(greenHist, 0, sizeof(greenHist));
                    memset(blueHist, 0, sizeof(blueHist));

                    for (int p = -len; p <= len; p++)
                    {
                        for (int q = -len; q <= len; q++)
                        {
                            int red = qRed(middleImage.pixel(i + p, j + q));
                            int green = qGreen(middleImage.pixel(i + p, j + q));
                            int blue = qBlue(middleImage.pixel(i + p, j + q));

                            redHist[red]++;
                            greenHist[green]++;
                            blueHist[blue]++;
                        }
                    }
                }
                else
                { // 列数增加, 窗口按列向下移动, 为窗口新添加一行像素值, 并删去一行像素值
                    int oldWindowStartCol = j - len - 1;
                    int newWindowEndCol = j + len;

                    for (int p = -len; p <= len; p++)
                    {
                        // 要减去的列的像素值, 从窗口上到窗口下, 即 [j-len,j+len]
                        int red = qRed(middleImage.pixel(i + p, oldWindowStartCol));
                        int green = qGreen(middleImage.pixel(i + p, oldWindowStartCol));
                        int blue = qBlue(middleImage.pixel(i + p, oldWindowStartCol));

                        redHist[red]--;
                        greenHist[green]--;
                        blueHist[blue]--;

                        red = qRed(middleImage.pixel(i + p, newWindowEndCol));
                        green = qGreen(middleImage.pixel(i + p, newWindowEndCol));
                        blue = qBlue(middleImage.pixel(i + p, newWindowEndCol));

                        redHist[red]++;
                        greenHist[green]++;
                        blueHist[blue]++;
                    }
                }

                int r = getKValue(redHist, qRed(middleImage.pixel(i, j)), K);
                int g = getKValue(greenHist, qGreen(middleImage.pixel(i, j)), K);
                int b = getKValue(blueHist, qBlue(middleImage.pixel(i, j)), K);

                // int r = getAverage(rKNNValue);
                // int g = getAverage(gKNNValue);
                // int b = getAverage(bKNNValue);

                targetImage.setPixel(i - len, j - len, qRgb(r, g, b));
            }
        return targetImage;
    }
    return originImage;
} // KNNF

int SmoothMethod::getKValue(const int *histogram, int key, int K)
{
    // 计算距离 key 的 K 近邻的方法也是桶排序
    // 记录各点到 key 距离的数组长度不超过 255-key
    // bucket[255-key][0] => 像素值大于 key 的点其像素值与 key 的差值
    // bucket[255-key][1] => 像素值小于 key 的点其像素值与 key 的差值
    int bucket[255][2];

    for (int i = 0; i <= 255; i++)
    {
        bucket[i][0] = 0;
        bucket[i][1] = 0;
    }

    for (int i = 0; i <= 255; i++)
    {
        if (histogram[i] > 0)
        {
            if (i - key >= 0)
            {
                bucket[i - key][0] = histogram[i];
            }
            else
            {
                bucket[key - i][1] = histogram[i];
            }
        }
    }

    int max = K + 1;
    int KNNValue[max] = {0};
    K = K - 1; // 所有的 K 近邻点中 key 本身是第一个
    KNNValue[0] = key;
    bucket[0][0]--;

    if (K <= 0)
        return key;

    // j 是 KNNValue 索引
    for (int i = 0, j = 1; i <= 255; i++)
    {
        if (bucket[i][0] > 0)
        { // TODO 可优化
            // 大于 key 的像素值
            qDebug() << ">";
            if (bucket[i][0] >= K)
            {
                for (int k = 0; k < K; j++, k++)
                {
                    KNNValue[j] = i + key;
                }
                K = 0;
            }
            else
            {
                for (int k = 0; k < bucket[i][0]; j++, k++)
                {                          // 将所有像素值为 i 的点全部加入
                    KNNValue[j] = i + key; // 还原原始像素值
                }
                K -= bucket[i][0];
            }
        }
        if (K <= 0)
            break;
        if (bucket[i][1] > 0)
        { // 小于 key 的像素值
            qDebug() << "<";
            if (bucket[i][1] >= K)
            {
                for (int k = 0; k < K; j++, k++)
                {
                    KNNValue[j] = key - i;
                }
                K = 0;
            }
            else
            {
                for (int k = 0; k < bucket[i][1]; j++, k++)
                {                          // 将所有像素值为 i 的点全部加入
                    KNNValue[j] = key - i; // 还原原始像素值
                }
                K -= bucket[i][1];
            }
        }
        if (K <= 0)
            break;
    }

    for (int i = 0; i < max - 1; i++)
        qDebug() << KNNValue[i];

    // return KNNValue;

    int res = getAverage(KNNValue, max - 1);

    return res;
} // getKValue

int SmoothMethod::getAverage(const int *arr, int len)
{
    int average = 0;

    for (int i = 0; i < len; i++)
        average += arr[i];

    int res = average / len;
    return res;
} // getAverage
