#include "tetrahedron.h"
#include "math.h"
#include <QVector2D>
#include <QVector3D>
#include <QGLContext>
#include <QApplication>
#include <QPixmap>



Tetrahedron::Tetrahedron(QWidget *parent)
    : FigureFunctionality(parent)
{
}

void Tetrahedron::drawTetrahedron() {
    static GLdouble alpha = 1.0;
    static GLfloat vertices[] = {
        0, 0, 0, alpha,
        0, 0, 1, alpha,
        1, 0, 0, alpha,
        0, 1, 0, alpha,
    };
    static GLubyte triangles[] = {
        0, 1, 2,// front
        2, 3, 1,// left
        1, 3, 0, // back
        3, 2, 0, // right
    };

    glColorPointer(4, GL_FLOAT, 4*sizeof(GLfloat), vertices);
    glVertexPointer(3, GL_FLOAT, 4*sizeof(GLfloat), vertices);

    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glDrawElements(GL_TRIANGLES, 4*4, GL_UNSIGNED_BYTE, triangles);

    glDisableClientState(GL_COLOR_ARRAY);

    glColor4f(0, 0, 0, 1);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawElements(GL_TRIANGLES, 4*4, GL_UNSIGNED_BYTE, triangles);

    glDisableClientState(GL_VERTEX_ARRAY);
    //Textures
//    glVertexPointer(3, GL_FLOAT, 0, tetrahedronSidesVectors.constData());
//    glTexCoordPointer(2, GL_FLOAT, 0, texCoords.constData());
//    glEnableClientState(GL_VERTEX_ARRAY);
//    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

//    glBindTexture(GL_TEXTURE_2D, texture);
//    for (int i = 0; i < 4; ++i) {

//         glDrawArrays(GL_TRIANGLES, i * 3, 3);
//    }
}

void Tetrahedron::initializeGL() {
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    getTimer()->start(500, this);
    makeObject();

}

void Tetrahedron::makeObject() {
    static const int coords[4][3][3] = {
             { { 1, 0, 0 }, { 0, 0, 0 }, { 0, 1, 0 } },
             { { 1, 0, 0 }, { 0, 1, 0 }, { 0, 0, 1 } },
             { { 0, 0, 1 }, { 1, 0, 0 }, { 0, 0, 0 } },
             { { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 0 } },

    };
    texture = bindTexture(QPixmap(QString("/Users/andrey/Documents/workspace/qt/Cub/images/side1.png")), GL_TEXTURE_2D);
    for (int j=0; j < 4; ++j) {
        texCoords.append(QVector2D(0, 0));
        texCoords.append(QVector2D(0, 1));
        texCoords.append(QVector2D(1, 0));
        for ( int i = 0; i < 3; i++ ) {
            tetrahedronSidesVectors.append(QVector3D(coords[j][i][0], coords[j][i][1],
                            coords[j][i][2]));
        }
    }
}

void Tetrahedron::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glScaled(2, 2, 1);
    glTranslated(0.0, 0.0, getZtranslation());
    glRotated(getRotateAngle(), 1, 0, 0);
    glRotated(getRotateAngle(), 0, 1, 0);

    drawTetrahedron();
}

void Tetrahedron::resizeGL(int w, int h) {
    static GLdouble aspect = (GLdouble) w / h;
    const GLdouble pi = 3.1415926535897932384626433832795;

    GLdouble horizontal, vertical;
    GLdouble near = 0.001;
    GLdouble far = 100;
    GLdouble fovY = 30;

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    vertical = tan( fovY / 360 * pi ) * near;
    horizontal = vertical * aspect;

    glFrustum( -horizontal, horizontal, -vertical, vertical, near, far );
    glMatrixMode(GL_MODELVIEW);

}

Tetrahedron::~Tetrahedron()
{

}

