#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QtOpenGL>
#include <glut.h>
#include <time.h>

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget* parent = 0);

protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);

public slots:
    void reset();
    void setRunPause();

private:
    QPoint lastPos;
    QVector2D origin;
    QVector2D lastOrigin;
    void drawAxis();
    QPoint world2Pixel(QVector2D &v);
    QVector2D pixel2World(QPoint &p);
    QVector2D pixel2World(int x, int y);
    double P2WScale;
    double timeStep;
    QVector2D mousePos;
    float lastFrame;
    bool pause;

    void coreLogic();

    QVector2D gravity;
};

#endif // GLWIDGET_H
