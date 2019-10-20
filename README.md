# Picop

a personal works of Digital Image Processing

文件目录
picop
|───debug
|    |───bin
|    |───moc
|    |───obj
|───picop
|    |───include
|    |   | 头文件
|    |   |
|    |───source
|    |   | 源代码
|    |   |
|    |   Makefile
|    |   picop.pro
|    |   prcop.pro.user
|    |   README.md

运行环境
Ubuntu18.04

开发工具
vscode + Qt5.9.8 + Opencv4.1.1

编译指令
qmake ${workSpaceFolder}picop.pro -spec linux-g++ CONFIG+=debug CONFIG+=qml_debug
make -f ${workSpaceFolder}Makefile qmake_all
make -j8
