#include <QtWidgets>
#include <QtOpenGL>

#include <cmath>
#include <string>

#include "glwidget.hpp"
#include "openglutils.hpp"
#include "utils.hpp"

#include "bgcontainer.hpp"
#include "hudcontainer.hpp"
#include "icon.hpp"

static const std::string iconFilename("assets/unnamed.png"); // FIXME

GLWidget::GLWidget(QWidget *parent)
  : QGLWidget(QGLFormat(QGL::DoubleBuffer | QGL::DepthBuffer), parent),
    m_pBG(0), m_pHUD(0),
    m_pIcon(0), m_angle(0.f),
    m_pCurrentContainerOver(0)
{

}

GLWidget::~GLWidget()
{
  if(m_pIcon)
    delete m_pIcon;
}

void GLWidget::initializeGL()
{
  glClearColor(1.f, 0.f, 1.f, 1.f); // magenta

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LEQUAL);
  GL_TEST_ERR;

  m_pBG  = new BGContainer(&m_frame);
  m_pHUD = new HUDContainer(&m_frame);

  m_frame.addContainer((Container *) m_pBG);
  m_frame.addContainer((Container *) m_pHUD);

  Icon *pIco = new Icon((Container *) m_pHUD);
  float icoS_2(pIco->getVpSize() * .5f);
  pIco->setPosition(.5f, icoS_2);

  if(!pIco->loadFromFile(iconFilename))
    qWarning(("Error creating icon from \"" + iconFilename + "\"").c_str());

  m_pHUD->addObject((Object *) pIco);
}

void GLWidget::paintGL()
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glLoadIdentity();
  GL_TEST_ERR;

  m_frame.draw();
  GL_TEST_ERR;

  if(m_pIcon)
    m_pIcon->draw();
  GL_TEST_ERR;
}

void GLWidget::resizeGL(int w, int h)
{
  m_frame.setSize(w, h);

  glViewport(0, 0, w, h);
  GL_TEST_ERR;

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0.0, 1.0, 0.0, 1.0, -10.0, 10.0);
  glMatrixMode(GL_MODELVIEW);
  GL_TEST_ERR;
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
  m_lastPos = event->pos();

  checkBounds(m_lastPos);

  if(m_pCurrentContainerOver)
    {
      QPointF s2sPos(screenToSpace(m_lastPos));

      Icon *pIco((Icon *) m_pCurrentContainerOver->selectObject(s2sPos));

      if(pIco)
        {
          if(m_pIcon)
            m_pCurrentContainerOver->addObject(m_pIcon);

          m_pIcon = pIco;
          m_scale = m_pIcon->getScale();
          m_angle = m_pIcon->angle();
        }
    }

  event->accept();
  update();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
  bool bShift(event->modifiers() & Qt::ShiftModifier);
  bool bCntrl(event->modifiers() & Qt::ControlModifier);

  m_lastPos = event->pos();

  checkBounds(m_lastPos);

  if(m_pIcon && m_pCurrentContainerOver)
    {
      if(m_pCurrentContainerOver == m_pHUD)
        {
          m_pIcon->setAngle(0.f);
          m_pIcon->setScale(1.f, 1.f);
          float icoS_2(m_pIcon->getVpSize() * .5f);
          m_pIcon->setPosition(.5f, icoS_2);
        }


      if(!bShift && m_pCurrentContainerOver == m_pBG)
        m_pIcon->setScale(m_scale);

      if(!bCntrl && m_pCurrentContainerOver == m_pBG)
        m_pIcon->setAngle(m_angle);

      if(m_pIcon->width() > 1e-3f && m_pIcon->height() > 1e-3f)
        m_pCurrentContainerOver->addObject(m_pIcon);
      else
        {
          m_pIcon->setParent(m_pHUD);
          m_pIcon->setAngle(0.f);
          m_pIcon->setScale(1.f, 1.f);
          m_pHUD->addObject(m_pIcon);
          float icoS_2(m_pIcon->getVpSize() * .5f);
          m_pIcon->setPosition(.5f, icoS_2);
          qWarning("Warning: too small icon removed and new one created in HUD"); // kind of
        }

      m_pIcon = 0;
    }

  event->accept();
  update();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
  bool bShift(event->modifiers() & Qt::ShiftModifier);
  bool bCntrl(event->modifiers() & Qt::ControlModifier);

  if(!bShift && !bCntrl)
    checkBounds(event->pos());

  if(m_pIcon && m_pCurrentContainerOver)
    {
      m_pIcon->setParent(m_pCurrentContainerOver);

      if(m_pCurrentContainerOver == m_pBG && bShift)
        {
          float ratio(width() / float(height()));
          float len(QVector2D(screenToSpace(event->pos()) - m_pIcon->getPosition()).length() * ratio);

          m_pIcon->setScale(len, len);
        }
      else if(m_pCurrentContainerOver == m_pBG && bCntrl)
        {
          QVector2D u(screenToSpace(m_lastPos)    - m_pIcon->getPosition());
          QVector2D v(screenToSpace(event->pos()) - m_pIcon->getPosition());

          u.normalize();
          v.normalize();

          float xatan2(u.x() * v.y() - u.y() * v.x());
          float yatan2(QVector2D::dotProduct(u, v));

          float radians(std::atan2(xatan2, yatan2));
          float degrees(360.f - qRadiansToDegrees(radians));

          m_pIcon->setAngle(degrees);
        }
      else
        {
          QPointF s2sPos(screenToSpace(event->pos()));
          QPointF s2bPos(m_pCurrentContainerOver->spaceToBounds(s2sPos));

          m_pIcon->setAngle(m_angle);
          m_pIcon->setScale(m_scale);
          m_pIcon->setPosition(s2bPos);
        }
    }

  event->accept();
  update();
}

QPoint GLWidget::spaceToScreen(const QPointF &p) const
{
  int x(std::floor(p.x() * width()));
  int y(std::floor(p.y() * height()));
  return QPoint(x, y);
}

QPointF GLWidget::screenToSpace(const QPoint &p) const
{
  float x(p.x() / float(width()));
  float y(p.y() / float(height()));
  return QPointF(x, y);
}

void GLWidget::checkBounds(const QPoint &pos)
{
  QPointF s2sPos(screenToSpace(pos));

  bool bMouseOverBG(isPointInBounds<QPointF, float>(
                      s2sPos,
                      QPointF(m_pBG->x(), m_pBG->y()),
                      QPointF(m_pBG->x() + m_pBG->width(), m_pBG->y() + m_pBG->height())
                      ));

  bool bMouseOverHUD(isPointInBounds<QPointF, float>(
                       s2sPos,
                       QPointF(m_pHUD->x(), m_pHUD->y()),
                       QPointF(m_pHUD->x() + m_pHUD->width(), m_pHUD->y() + m_pHUD->height())
                       ));

  if(bMouseOverBG)
    m_pCurrentContainerOver = m_pBG;
  else if(bMouseOverHUD)
    m_pCurrentContainerOver = m_pHUD;
  else
    m_pCurrentContainerOver = 0;
}
