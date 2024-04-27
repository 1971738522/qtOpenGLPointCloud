#----------------------------支持QT4版本
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#----------------------------添加相关QT模块
QT           += core gui opengl
QT           += network
QT           += concurrent

#----------------------------添加用于构建应用程序Makefile(默认)
TEMPLATE      = app

#----------------------------添加构建目标(exe)名称
TARGET        = openGLPointCloudTest

#----------------------------添加构建目标输出目录
# 元对象编译输出 - Q_OBJECT宏翻译代码
MOC_DIR       = $$PWD/obj/_moc
# qrc资源文件输出
RCC_DIR       = $$PWD/obj/_rcc
# ui文件输出
UI_DIR        = $$PWD/obj/_ui
# 中间文件输出
OBJECTS_DIR   = $$PWD/obj/_mid
# 可执行文件输出
DESTDIR       = $$PWD/obj/_bin

#----------------------------添加工程文件
#------------------工程目录（根目录）
INCLUDEPATH  += $$PWD
SOURCES      += $$PWD/src/main.cpp
HEADERS      += $$PWD/src/head.h
#------------------构建目录
INCLUDEPATH  += $$PWD/src/01_build
#------------------公共目录
INCLUDEPATH  += $$PWD/src/02_common
include ($$PWD/src/02_common/_common.pri)
#------------------窗体目录
INCLUDEPATH  += $$PWD/src/03_appforms
include ($$PWD/src/03_appforms/_appforms.pri)
#------------------OpenGL目录
INCLUDEPATH  += $$PWD/src/04_opengl
include ($$PWD/src/04_opengl/_opengl.pri)

#----------------------------添加资源文件
RESOURCES += source/image.qrc \
    source/opengl.qrc \
    source/pointcloud.qrc
