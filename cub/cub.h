#ifndef CUB_H
#define CUB_H

#include <QWidget>
#include <QtOpenGL/QGLWidget>
#include "figurefunctionality.h"

class Cub : public FigureFunctionality
{
    Q_OBJECT

public:
    Cub(QWidget *parent = 0);
    ~Cub();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    GLuint textures[6];
    QVector<QVector2D> texCoords;
    QVector<QVector3D> cubeSidesVectors;
    void drawCube();
    void makeObject();
};

#endif // WIDGET_H
