#include "spectrogram.h"
using namespace cv;

Spectrogram::Spectrogram()
{
}

Spectrogram::~Spectrogram()
{
}

void Spectrogram::displaySpectrogram(QString imagePath)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "显示频谱图";
    cv::Mat src = cv::imread(imagePath.toStdString(), 0);

    // 扩充图像尺寸到最佳尺寸，边界用0填充
    int r = cv::getOptimalDFTSize(src.rows);
    int c = cv::getOptimalDFTSize(src.cols);
    cv::Mat padded;
    cv::copyMakeBorder(src, padded, 0, r - src.rows, 0, c - src.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

    // 为傅里叶变换的结果（复数，包含实部和虚部，所以需要创建一个二维的数组）分配存储空间,
    // 需要用至少float型来存储
    // 最后将二维数组合并为二通道--傅里叶变换需要
    cv::Mat dst1[] = {cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F)};
    cv::Mat dst2;
    cv::merge(dst1, 2, dst2);

    // 傅里叶变换,结果依旧存储在dst2中
    cv::dft(dst2, dst2);

    // 将复数换算成幅值
    cv::split(dst2, dst1);                    // 把二通道图像分解为二维数组，保存到dst1中,dst1[0]中存放的为实部
    cv::magnitude(dst1[0], dst1[1], dst1[0]); // 结果存放在dst1[0]中
    cv::Mat magnitudeImage = dst1[0];

    // 对数尺度缩放以便于显示
    // 计算log(1 + sqrt(Re(DFT(dst2))**2 + Im(DFT(dst2))**2))
    magnitudeImage += cv::Scalar::all(1);
    cv::log(magnitudeImage, magnitudeImage);

    // 剪切和重分布幅度图象限
    // 若有奇数行或奇数列，进行频谱裁剪
    magnitudeImage = magnitudeImage(cv::Rect(0, 0, magnitudeImage.cols & -2, magnitudeImage.rows & -2)); // 任何一个数&-2的结果一定是偶数

    // 重新排列傅里叶图像的象限，使原点位于图像中心
    int cx = magnitudeImage.cols / 2;
    int cy = magnitudeImage.rows / 2;
    cv::Mat q0(magnitudeImage(cv::Rect(0, 0, cx, cy)));
    cv::Mat q1(magnitudeImage(cv::Rect(cx, 0, cx, cy)));
    cv::Mat q2(magnitudeImage(cv::Rect(0, cy, cx, cy)));
    cv::Mat q3(magnitudeImage(cv::Rect(cy, cy, cx, cy)));

    cv::Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    // 将幅度值归一化到0~1之间，这是因为magnitudeImage中的数据类型是浮点型，这时用imshow()来显示函数，会将像素值乘于255，因此需要归一化到0~1之间
    cv::normalize(magnitudeImage, magnitudeImage, 0, 1, cv::NORM_MINMAX);

    // 显示最后的频谱
    cv::imshow("频谱图", magnitudeImage);

    cv::waitKey();

    return;
}
