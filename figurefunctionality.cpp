#include "figurefunctionality.h"

#include <QKeyEvent>

FigureFunctionality::FigureFunctionality(QWidget *parent)
: QGLWidget(parent)
{
    //default values;
    rotateAngle = 0;
    zTranslation = -10.0;
    timer = new QBasicTimer;
}

FigureFunctionality::~FigureFunctionality() {
}

void FigureFunctionality::keyPressEvent( QKeyEvent * event ) {
    if( event->key() == Qt::Key_Left )
    {
        rotate(4);
    } else if ( event->key() == Qt::Key_Right ) {
        rotate(-4);
    } else if ( event->key() == Qt::Key_Up ) {
        approximate(1.0);
    } else if ( event->key() == Qt::Key_Down ) {
        approximate(-1.0);
    } else if ( event->key() == Qt::Key_F ) {
        if (isFullScreen()) {
            showNormal();
        } else {
            showFullScreen();
        }
    }
}

void FigureFunctionality::rotate(GLuint angleToRotate) {
    rotateAngle += angleToRotate;
    updateGL();
}

void FigureFunctionality::timerEvent(QTimerEvent *e) {
    Q_UNUSED(e);

    rotate(2);
    updateGL();
}

void FigureFunctionality::approximate(GLfloat step) {
    zTranslation += step;
    updateGL();
}

GLuint FigureFunctionality::getRotateAngle() {
    return rotateAngle;
}
void FigureFunctionality::setRotateAngle(GLuint newRotateAngle) {
    rotateAngle = newRotateAngle;
}

GLfloat FigureFunctionality::getZtranslation() {
    return zTranslation;
}
void FigureFunctionality::setZtranslation(GLfloat newTraslation) {
    zTranslation = newTraslation;
}
QBasicTimer* FigureFunctionality::getTimer() {
    return timer;
}


