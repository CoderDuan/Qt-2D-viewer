#include "glwidget.h"

GLWidget::GLWidget(QWidget* parent)
    :QGLWidget((QGLWidget*)parent)
{
    origin = QVector2D(0, 0);
    P2WScale = 0.01f;
    lastFrame = 0;
    mousePos = QVector2D(0,0);
    setMouseTracking(true);
    pause = false;
    gravity = QVector2D(0, -10);
}

void GLWidget::initializeGL()
{
    int x = this->x();
    int y = this->y();
    int width = this->width();
    int height = this->height();
    setGeometry(x, y, width, height);

    glMatrixMode(GL_PROJECTION);
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void GLWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    int width = this->width();
    int height = this->height();
    gluOrtho2D( origin.x() - width/2*P2WScale, origin.x() + width/2*P2WScale,
                origin.y() - height/2*P2WScale, origin.y() + height/2*P2WScale );
    drawAxis();

    coreLogic();

    update();
}

void GLWidget::coreLogic()
{
    if(!pause)
    {
        if(lastFrame == 0)
        {
            lastFrame = clock();
        }
        else
        {
            float currFrame = clock();
            float dt = (currFrame - lastFrame)/1000.0f;
            lastFrame = currFrame;
            //for(int i = 0; i < 20; i++)
                //moveDt(dt/20.0f);
        }
    }
}

void GLWidget::resizeGL(int width, int height)
{
    if(0 == height)
        height = 1;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluOrtho2D( origin.x() - width/2*P2WScale, origin.x() + width/2*P2WScale,
                origin.y() - height/2*P2WScale, origin.y() + height/2*P2WScale );
}

void GLWidget::drawAxis()
{
    glBegin(GL_LINES);
    int iMax = 100;
    for(int i = -iMax; i <= iMax; i++)
    {
        if( i == 0)
            glColor3f(1.0f, 0.6f, 0.6f);
        else
            glColor3f(0.6f, 0.6f, 0.6f);
        glVertex3f((double)i, -iMax, 0);
        glVertex3f((double)i, iMax, 0);
        glVertex3f(-iMax, i, 0);
        glVertex3f(iMax, i, 0);
    }
    glEnd();
}


QPoint GLWidget::world2Pixel(QVector2D &v)
{
    return QPoint(v.x(),v.y());
}

QVector2D GLWidget::pixel2World(QPoint &p)
{
    int width = this->width();
    int height = this->height();
    QVector2D v(p.x()*P2WScale + origin.x() - width/2*P2WScale,
                (height - p.y())*P2WScale + origin.y() - height/2*P2WScale);
    return v;
}

QVector2D GLWidget::pixel2World(int x, int y)
{
    int width = this->width();
    int height = this->height();
    QVector2D v(x*P2WScale+ origin.x() - width/2*P2WScale,
                (height - y)*P2WScale + origin.y() - height/2*P2WScale);
    return v;
}
// -----------------------  Event Handler --------------------------

void GLWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->buttons() & Qt::RightButton)
    {
        lastPos = QPoint(e->x(), e->y());
        mousePos = pixel2World(e->x(), e->y());
        lastOrigin = origin;
    }
    update();
}

void GLWidget::mouseMoveEvent(QMouseEvent *e)
{
    mousePos = pixel2World(e->x(), e->y());
    if(e->buttons() & Qt::RightButton)
    {
        int dx = e->x() - lastPos.x();
        int dy = e->y() - lastPos.y();
        origin = QVector2D(lastOrigin.x() - dx*P2WScale, lastOrigin.y() + dy*P2WScale);
    }
    update();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *e)
{

}

void GLWidget::wheelEvent(QWheelEvent *e)
{
    double angle = e->delta() / 120.0f;
    P2WScale *= pow(1.09, -angle);
}

// -------------------------- Slots -----------------------------

void GLWidget::reset()
{

}

void GLWidget::setRunPause()
{
    pause = !pause;
    lastFrame = 0;
}
