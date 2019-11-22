#include "SpectrogramMethod.h"

SpectrogramMethod::SpectrogramMethod()
{
}

SpectrogramMethod::~SpectrogramMethod()
{
}

void SpectrogramMethod::displaySpectrogram(QString imagePath)
{
    qDebug().noquote() << "[Debug]" << QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd hh:mm:ss.zzz") << ":"
                       << "显示频谱图";

    // 读入灰度图
    cv::Mat image = cv::imread(imagePath.toStdString(), cv::IMREAD_GRAYSCALE);

    cv::Mat padded;
    int m = cv::getOptimalDFTSize(image.rows);
    int n = cv::getOptimalDFTSize(image.cols);

    cv::copyMakeBorder(image, padded, 0, m - image.rows, 0, n - image.cols, cv::BORDER_CONSTANT, cv::Scalar::all(0));

    cv::Mat planes[] = {cv::Mat_<float>(padded), cv::Mat::zeros(padded.size(), CV_32F)};
    cv::Mat complexImage;
    cv::merge(planes, 2, complexImage);

    // 进行傅里叶变换
    cv::dft(complexImage, complexImage);

    // 计算幅值, 转换到对数尺度
    cv::split(complexImage, planes);
    cv::magnitude(planes[0], planes[1], planes[0]);
    cv::Mat magImage = planes[0];

    magImage += cv::Scalar::all(1);
    cv::log(magImage, magImage);

    magImage = magImage(cv::Rect(0, 0, magImage.cols & -2, magImage.rows & -2));

    int cx = magImage.cols / 2;
    int cy = magImage.rows / 2;

    cv::Mat q0(magImage, cv::Rect(0, 0, cx, cy));   //左上角图像划定 ROI 区域
    cv::Mat q1(magImage, cv::Rect(cx, 0, cx, cy));  //右上角图像
    cv::Mat q2(magImage, cv::Rect(0, cy, cx, cy));  //左下角图像
    cv::Mat q3(magImage, cv::Rect(cx, cy, cx, cy)); //右下角图像

    //变换左上角和右下角象限
    cv::Mat tmp;
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);

    //变换右上角和左下角象限
    q1.copyTo(tmp);
    q2.copyTo(q1);
    tmp.copyTo(q2);

    //归一化处理，用0-1之间的浮点数将矩阵变换为可视的图像格式
    // cv::normalize(magImage, magImage, 0, 1, );

    cv::imshow("输入图像", image);
    cv::imshow("频谱图", magImage);
    cv::waitKey(0);

    return;
}
