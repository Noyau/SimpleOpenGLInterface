#include "object.hpp"

#include <cassert>
#include <iostream>

#include "openglutils.hpp"
#include "utils.hpp"

Object::Object(Container *pParent)
  : m_pParent(pParent),
    m_width(1.f), m_height(1.f),
    m_x(0.f), m_y(0.f),
    m_angle(0.f)
{

}

Object::~Object()
{

}

const Container *Object::getParent() const
{
  return m_pParent;
}

void Object::setParent(Container *pParent)
{
  m_pParent = pParent;
}

float Object::width() const
{
  return m_width;
}

float Object::height() const
{
  return m_height;
}

float Object::x() const
{
  return m_x;
}

float Object::y() const
{
  return m_y;
}

float Object::angle() const
{
  return m_angle;
}

float Object::getVpWidth()
{
  assert(m_pParent);
  return m_width * m_pParent->width();
}

float Object::getVpHeight()
{
  assert(m_pParent);
  return m_height * m_pParent->height();
}

float Object::getVpX()
{
  assert(m_pParent);
  return m_x * m_pParent->width()  + m_pParent->x();
}

float Object::getVpY()
{
  assert(m_pParent);
  return m_y * m_pParent->height() + m_pParent->y();
}

QSizeF Object::getScale()
{
  return QSizeF(m_width, m_height);
}

void Object::setScale(float sx, float sy)
{
  m_width  = sx;
  m_height = sy;
}

void Object::setScale(const QSizeF &s)
{
  m_width  = s.width();
  m_height = s.height();
}

QPointF Object::getPosition()
{
  return QPointF(m_x, m_y);
}

void Object::setPosition(float x, float y)
{
  m_x = x;
  m_y = y;
}

void Object::setPosition(const QPointF &p)
{
  m_x = p.x();
  m_y = p.y();
}

void Object::setAngle(float a)
{
  m_angle = a;
}

bool Object::containsPoint(const QPointF &p)
{
  float x(getVpX()), w(getVpWidth());
  float y(getVpY()), h(getVpHeight());

  return isPointInBounds<QPointF, float>(
        p,
        QPointF(x, y),
        QPointF(x + w, y + h)
        );
}

void Object::draw()
{
  float x(getVpX()), w(getVpWidth());
  float y(getVpY()), h(getVpHeight());

  float w_2(w * .5f), h_2(h * .5f);

  glColor3f(1.f, 0.f, 1.f); // magenta
  glRectf(x - w_2, y - h_2, x + w_2, y + h_2);
  GL_TEST_ERR;
}


std::ostream &operator<<(std::ostream &out, const Object &o)
{
  out << "Object { " << o.getParent() << ", [" << o.x() << ", " << o.y() << "], [" << o.width() << ", " << o.height() << "] }";
  return out;
}
