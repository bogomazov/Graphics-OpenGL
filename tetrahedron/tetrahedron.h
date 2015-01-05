#ifndef TETRAHEDRON_H
#define TETRAHEDRON_H

#include <QWidget>
#include <QtOpenGL/QGLWidget>
#include "figurefunctionality.h"

class Tetrahedron : public FigureFunctionality
{
    Q_OBJECT

public:
    Tetrahedron(QWidget *parent = 0);
    ~Tetrahedron();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    GLuint texture;
    QVector<QVector2D> texCoords;
    QVector<QVector3D> tetrahedronSidesVectors;
    void drawTetrahedron();
    void makeObject();
};


#endif // TETRAHEDRON_H
