# Picop

a personal works of Digital Image Processing

目录结构  
picop  
|───bin  
|───debug  
|───|───moc  
|───|───obj  
|───include  
|───|───| 头文件  
|───|───|  
|───source  
|───|───| 源代码  
|───|───|  
|───Makefile  
|───picop.pro  
|───prcop.pro.user  
|───README.md  

运行环境
Ubuntu19.10

开发工具
vscode + Qt5.9.8 + Opencv4.1.1

编译指令  
Linux  
qmake ${workSpaceFolder}picop.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug  
make -f ${workSpaceFolder}Makefile qmake_all  
make -j8  
Windows  
也许是  
qmake picop.pro  
make  
暂时还未在Windows下尝试编译    

需要优化的地方有很多, 但在正式实现所有功能和完成其它课程作业之前, 没有时间优化

TODO  
* 根据打开图像大小自动调整窗口大小
* 实现滚轮控制图片缩放
* 自选, 实现bmp2txt
* 优化直方图均衡化和直方图显示功能
* 图片旋转只支持正方形
* 24位真彩色图像转256色图像有点慢, 需要做个进度条

?  
* K 邻域均值滤波 stack smashing detected

github
https://github.com/TianSHH/picop

