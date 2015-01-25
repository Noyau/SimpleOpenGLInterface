#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>

#include "frame.hpp"
#include "icon.hpp"

/////////////////////////////////////////////////////
/// \brief The GLWidget class
///
/// An OpenGL widget that contains the frame and all
/// the objects of the scene, and handles all the
/// events.
/////////////////////////////////////////////////////
class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    virtual ~GLWidget();

protected:
    virtual void initializeGL();
    virtual void paintGL();
    virtual void resizeGL(int width, int height);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);

    /// \return a point in screen coordinates
    QPoint spaceToScreen(const QPointF &p) const;

    /// \return a point in space coordinates
    QPointF screenToSpace(const QPoint &p) const;

private:
    /// \brief It checks which container contains the screen coordinates
    inline void checkBounds(const QPoint &pos);

    QPoint m_lastPos;

    Frame m_frame;
    Container *m_pBG;
    Container *m_pHUD;

    Icon *m_pIcon;
    QSizeF m_scale;
    float m_angle; // in degrees

    Container *m_pCurrentContainerOver;
};

#endif
