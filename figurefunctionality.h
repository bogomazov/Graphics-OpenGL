#ifndef FIGUREFUNCTIONALITY_H
#define FIGUREFUNCTIONALITY_H

#include <QtOpenGL/QGLWidget>
#include <QBasicTimer>

class FigureFunctionality : public QGLWidget
{
    Q_OBJECT

public:
    FigureFunctionality(QWidget *parent = 0);
    GLuint getRotateAngle();
    GLfloat getZtranslation();
    QBasicTimer* getTimer();
    void setZtranslation(GLfloat newTraslation);
    void setRotateAngle(GLuint newRotateAngle);
    ~FigureFunctionality();

private:
    QBasicTimer *timer;
    GLuint rotateAngle;
    GLfloat zTranslation;
    void keyPressEvent( QKeyEvent * event );
    void rotate(GLuint rotateAngle);
    void timerEvent(QTimerEvent *e);
    void approximate(GLfloat step);

};

#endif // FIGUREFUNCTIONALITY_H
