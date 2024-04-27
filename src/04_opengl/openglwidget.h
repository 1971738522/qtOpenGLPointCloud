#pragma once

#include "src/head.h"
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>
#include <QString>
#include <QFile>
#include <QDebug>
#include <iostream>
#include <vector>

/***********************************************
 点云数据读取类：
    激光点云由一系列的三维坐标点组成，常见的点云格式有pcd、ply、las等；
    pcd格式的点云文件需要借助PCL点云库进行读取，Windows下配置PCL点云库较为麻烦；
    因此可先将pcd点云文件在Ubuntu系统下转换成csv文件，然后在Qt中直接读取csv文件；
    加载点云的数据格式为（x，y，z，intensity），其它点云格式只需简单修改下也可适用；
***********************************************/
class readPointData {
public:
    char* strsep(char** stringp, const char* delim) {
        char* s;
        const char* spanp;
        int c, sc;
        char* tok;
        if ((s = *stringp) == NULL)
            return (NULL);
        for (tok = s;;) {
            c = *s++;
            spanp = delim;
            do {
                if ((sc = *spanp++) == c) {
                    if (c == 0)
                        s = NULL;
                    else
                        s[-1] = 0;
                    *stringp = s;
                    return (tok);
                }
            } while (sc != 0);
        }
        /* NOTREACHED */
    }
    std::vector<float> read_csv_data(QString docPath) {
        std::vector<float> vertexs_data;
        QFile inputFile(docPath);
        if (inputFile.open(QIODevice::ReadOnly)) {
            uchar* fpr = inputFile.map(0, inputFile.size());
            int subcnt = 0;
            char* substr;
            char* s = strdup((char*)fpr);
            while (substr = strsep(&s, "\n")) {
                subcnt = 0;
                char* lineSubStr;
                while (subcnt < 4) {
                    lineSubStr = strsep(&substr, ",");
                    vertexs_data.push_back(atof(lineSubStr));
                    ++subcnt;
                }
            }
            inputFile.close();
        } else {
            qDebug() << "Can't open the file!" << endl;
        }
        return vertexs_data;
    }
};

/***********************************************
 OpenGL窗口类：
***********************************************/
class OpenGLWidget : public QOpenGLWidget, QOpenGLFunctions_3_3_Core {
    Q_OBJECT
public:
    OpenGLWidget(QWidget *parent = nullptr);
    ~OpenGLWidget();
protected:
    virtual void initializeGL() override;
    virtual void resizeGL(int w,int h) override;
    virtual void paintGL() override;
protected:
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
private:
    QOpenGLShaderProgram shaderProgram_mesh;
    QOpenGLShaderProgram shaderProgram_axis;
    QOpenGLShaderProgram shaderProgram_point;
    readPointData readCsvData;
    unsigned int VAO_MeshLine;
    unsigned int VBO_MeshLine;
    unsigned int VAO_Axis;
    unsigned int VBO_Axis;
    unsigned int VAO_Point;
    unsigned int VBO_Point;
    unsigned int vertex_count;
    unsigned int point_count;
    std::vector<float> pointData;
    float x_rotate;
    float z_rotate;
    float x_trans;
    float y_trans;
    float zoom;
    bool first_mouse;
    bool leftMousePress;
    bool MidMousePress;
private:
    unsigned int buildMeshline(float size, int count);
    void buildCooraxis(float length);
    unsigned int buildPointdata(std::vector<float>& point_vertexs);
};
