# Picop

a personal works of Digital Image Processing

## 功能简介  
1. 支持对图像的基本文件操作
1. 可设定采样率;
1. 可设定量化等级;
1. 可调节灰度阀值;
1. 直方图及位平面显示;
1. 图像点运算,对数变换,幂次变换等;
1. 图像几何运算,缩放,旋转,平移;
1. 平滑,中值滤波,均值滤波;
1. 锐化,Reborts,Sobel,Laplacian算子;
1. 自定义卷积核滤波;
1. 图像灰度转换;
1. 图像256色转换;
1. 边缘检测,Sobel,Prewitt,Laplacian算子;
1. Canny边缘跟踪;
1. 基于Hough变换的直线检测.

## 开发环境
Ubuntu19.10

## 开发工具
vscode + Qt5.9.8 + OpenCV4.1.2

## 安装
```
git clone git@github.com:TianSHH/picop.git
cd ./picop/
qmake picop.pro
make
./bin/picop
```

## 
