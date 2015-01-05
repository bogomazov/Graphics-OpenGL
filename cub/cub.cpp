#include "cub.h"
#include "math.h"
#include <QVector2D>
#include <QVector3D>
 #include <QPixmap>
#include <QApplication>


Cub::Cub(QWidget *parent)
    : FigureFunctionality(parent)
{

}

void Cub::drawCube() {
    //TEXTURES
    glVertexPointer(3, GL_FLOAT, 0, cubeSidesVectors.constData());
    glTexCoordPointer(2, GL_FLOAT, 0, texCoords.constData());
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    for (int i = 0; i < 6; ++i) {
         glBindTexture(GL_TEXTURE_2D, textures[i]);
         glDrawArrays(GL_TRIANGLE_FAN, i * 4, 4);
    }
    //Gradient and cube
//    static GLdouble alpha = 1.0;
//    static GLfloat vertices[] = {
//        0, 0, 0, alpha,
//        0, 0, 1, alpha,
//        1, 0, 1, alpha,
//        1, 0, 0, alpha,
//        0, 1, 0, alpha,
//        0, 1, 1, alpha,
//        1, 1, 1, alpha,
//        1, 1, 0, alpha,
//    };

//    static GLfloat colorPoints[] = {
//        0, 0, 0, alpha,
//        255, 255, 255, alpha,
//        0, 0, 0, alpha,
//        255, 255, 255, alpha,
//        0, 0, 0, alpha,
//        255, 255, 255, alpha,
//        0, 0, 0, alpha,
//        255, 255, 255, alpha,
//    };
//    static GLubyte elements[] = {
//        0, 1, 2, 3, // bottom
//        4, 5, 6, 7, // top
//        0, 4, 7, 3, // front
//        1, 5, 6, 2, // back
//        0, 4, 5, 1, // left
//        3, 7, 6, 2, // right
//    };
//    glShadeModel(GL_SMOOTH);
//    glColorPointer(4, GL_FLOAT, 4*sizeof(GLfloat), colorPoints);
//    glVertexPointer(3, GL_FLOAT, 4*sizeof(GLfloat), vertices);

//    glEnableClientState(GL_COLOR_ARRAY);

//    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    glDrawElements(GL_QUADS, 6*4, GL_UNSIGNED_BYTE, elements);

//    glDisableClientState(GL_COLOR_ARRAY);

//    glColor4f(0, 0, 0, 1);
//    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//    glDrawElements(GL_QUADS, 6*4, GL_UNSIGNED_BYTE, elements);

//    glDisableClientState(GL_VERTEX_ARRAY);

}

void Cub::initializeGL() {
    glEnable(GL_TEXTURE_2D);
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    getTimer()->start(500, this);
    makeObject();
}

void Cub::makeObject() {
    static const int coords[6][4][3] = {
         { { 1, 0, 0 }, { 0, 0, 0 }, { 0, 1, 0 }, { 1, 1, 0 } },
         { { 1, 1, 0 }, { 0, 1, 0 }, { 0, 1, 1 }, { 1, 1, 1 } },
         { { 1, 0, 1 }, { 1, 0, 0 }, { 1, 1, 0 }, { 1, 1, 1 } },
         { { 0, 0, 0 }, { 0, 0, 1 }, { 0, 1, 1 }, { 0, 1, 0 } },
         { { 1, 0, 1 }, { 0, 0, 1 }, { 0, 0, 0 }, { 1, 0, 0 } },
         { { 0, 0, 1 }, { 1, 0, 1 }, { 1, 1, 1 }, { 0, 1, 1 } }
     };
    for (int j=0; j < 6; ++j) {
        textures[j] = bindTexture
         (QPixmap(QString("/Users/andrey/Documents/workspace/qt/Cub/images/side%1.png").arg(j + 1)), GL_TEXTURE_2D);
        for ( int i = 0; i < 4; i++ ) {
            texCoords.append
                             (QVector2D(i == 0 || i == 3, i == 0 || i == 1));
            cubeSidesVectors.append(QVector3D(coords[j][i][0], coords[j][i][1],
                            coords[j][i][2]));
        }
    }
}

void Cub::paintGL() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    glScaled(2, 2, 1);
    glTranslated(0.0, 0.0, getZtranslation());
    glRotated(getRotateAngle(), 1, 0, 0);
    glRotated(getRotateAngle(), 0, 1, 0);

    drawCube();
}

void Cub::resizeGL(int w, int h) {
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


Cub::~Cub()
{

}
