#ifndef SPHERE_H
#define SPHERE_H

#include <QtOpenGL/QGLWidget>
#include "figurefunctionality.h"

class Sphere : public FigureFunctionality
{
    Q_OBJECT

public:
    Sphere(QWidget *parent = 0, float radius = 1, unsigned int rings = 12, unsigned int sectors = 24);
    ~Sphere();

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int w, int h);

private:
    std::vector<GLfloat> vertices;
    std::vector<GLfloat> normals;
    std::vector<GLfloat> texcoords;
    std::vector<GLushort> indices;
    GLuint texture;
    void drawSphere();
};

#endif // SPHERE_H
