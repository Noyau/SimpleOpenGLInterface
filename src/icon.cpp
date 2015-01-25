#include "icon.hpp"

#include <QGLWidget>

#include "utils.hpp"

Icon::Icon(Container *pParent)
  : Object(pParent), m_texId(0)
{

}

Icon::~Icon()
{
  glBindTexture(GL_TEXTURE_2D, 0);
  glDeleteTextures(1, &m_texId);
  GL_TEST_ERR;
}

bool Icon::loadFromFile(const std::string &filename)
{
  QImage img;

  if(!img.load(QString(filename.c_str())))
    {
      qWarning(("Error loading image: \"" + filename + "\"").c_str());
      return false;
    }

  QImage glImg = QGLWidget::convertToGLFormat(img);

  return glUtilsCreateTextureFromImage(glImg, &m_texId);
}

float Icon::size()
{
  return qMin<float>(m_width, m_height);
}

float Icon::getVpSize()
{
  return size() * qMin<float>(m_pParent->width(), m_pParent->height());
}

bool Icon::containsPoint(const QPointF &p)
{
  float x(getVpX()), y(getVpY());
  float s(getVpSize());
  float s_2(s * .5f);

  return isPointInBounds<QPointF, float>(
        p,
        QPointF(x - s_2, y - s_2),
        QPointF(x + s_2, y + s_2)
        );
}

void Icon::draw()
{
  float x(getVpX()), y(getVpY());
  float size(getVpSize());
  float size_2(size * .5f);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, m_texId);
  GL_TEST_ERR;

  glPushMatrix();
  glTranslatef(x - size_2, 1.f - y - size_2, 0.f);
  glScalef(size, size, 1.0f);
  GL_TEST_ERR;

  glTranslatef( x,  y, 0.f);
  glRotatef(m_angle, 0.f, 0.f, 1.f);
  glTranslatef(-x, -y, 0.f);
  GL_TEST_ERR;

  if(m_texId == 0)
    {
      qWarning("Error no such icon");
      glColor3f(1.f, 0.f, 1.f); // magenta
      glRectf(0.f, 0.f, 1.f, 1.f);
    }
  else
    glUtilsTexturedQuad();
  GL_TEST_ERR;

  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
  GL_TEST_ERR;
}
