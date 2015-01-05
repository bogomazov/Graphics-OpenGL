#include "sphere.h"
#include "math.h"
#include <QtOpenGL>
#include <OpenGL/glu.h>
#include <QPixmap>

Sphere::Sphere(QWidget *parent, float radius, unsigned int rings, unsigned int sectors)
    : FigureFunctionality(parent)
{

    float const R = 1./(float)(rings-1);
    float const S = 1./(float)(sectors-1);
    int r, s;

    vertices.resize(rings * sectors * 3);
    normals.resize(rings * sectors * 3);
    texcoords.resize(rings * sectors * 2);
    std::vector<GLfloat>::iterator v = vertices.begin();
    std::vector<GLfloat>::iterator n = normals.begin();
    std::vector<GLfloat>::iterator t = texcoords.begin();
    for(r = 0; r < rings; r++) for(s = 0; s < sectors; s++) {
        float const y = sin( -M_PI_2 + M_PI * r * R );
        float const x = cos(2*M_PI * s * S) * sin( M_PI * r * R );
        float const z = sin(2*M_PI * s * S) * sin( M_PI * r * R );

        *t++ = s*S;
        *t++ = r*R;

        *v++ = x * radius;
        *v++ = y * radius;
        *v++ = z * radius;

        *n++ = x;
        *n++ = y;
        *n++ = z;
    }

    indices.resize(rings * sectors * 4);
    std::vector<GLushort>::iterator i = indices.begin();
    for(r = 0; r < rings-1; r++) for(s = 0; s < sectors-1; s++) {
            *i++ = r * sectors + s;
            *i++ = r * sectors + (s+1);
            *i++ = (r+1) * sectors + (s+1);
            *i++ = (r+1) * sectors + s;
    }
    setZtranslation(-5);
}

void Sphere::drawSphere() {

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);

    glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
    glNormalPointer(GL_FLOAT, 0, &normals[0]);
    glTexCoordPointer(2, GL_FLOAT, 0, &texcoords[0]);
    glBindTexture(GL_TEXTURE_2D, texture);
    glDrawElements(GL_QUADS, indices.size(), GL_UNSIGNED_SHORT, &indices[0]);
}

void Sphere::initializeGL() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_TEXTURE_2D);
    texture = bindTexture
     (QPixmap(QString("/Users/andrey/Documents/workspace/qt/Cub/images/earth.png")), GL_TEXTURE_2D);
    getTimer()->start(1000, this);
}

void Sphere::paintGL() {

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glTranslatef(0,0,getZtranslation());
    glRotated(getRotateAngle(), 0, 1, 0);

    drawSphere();

    glPopMatrix();
}

void Sphere::resizeGL(int w, int h) {
    static GLdouble aspect = (GLdouble) w / h;
    const GLdouble pi = 3.1415926535897932384626433832795;

    glViewport(0, 0, w, h);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, aspect, 1, 10);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}

Sphere::~Sphere()
{

}


