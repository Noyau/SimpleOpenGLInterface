#include "container.hpp"

#include <cassert>
#include <cmath>

#include "object.hpp"
#include "openglutils.hpp"

Container::Container(Frame *pParent)
  : m_pParent(pParent),
    m_width(1.f), m_height(1.f),
    m_x(0.f), m_y(0.f),
    m_color(0xff00ff) // magenta
{

}

Container::~Container()
{
  ObjectArrayList::iterator it;
  for(it = m_objects.begin(); it != m_objects.end(); ++it)
    delete *it;
}

Frame *Container::getParent()
{
  return m_pParent;
}

float Container::width()
{
  return m_width;
}

float Container::height()
{
  return m_height;
}

float Container::x()
{
  return m_x;
}

float Container::y()
{
  return m_y;
}

void Container::addObject(Object *pObj)
{
  m_objects.push_back(pObj);
}

Object *Container::selectObject(const QPointF &mouse)
{
  Object *obj(0);

  ObjectArrayList::iterator it;
  for(it = m_objects.begin(); it != m_objects.end() && !obj; /*++it*/)
    if((*it)->containsPoint(mouse))
      {
        obj = *it;
        it = m_objects.erase(it);
      }
    else
      ++it;

  return obj;
}

QPointF Container::spaceToBounds(const QPointF &p) const
{
  float x((p.x() - m_x) / m_width);
  float y((p.y() - m_y) / m_height);
  return QPointF(x, y);
}

void Container::draw()
{
  glUtilsRGBColor(m_color);
  glRectf(m_x, m_y, m_x + m_width, m_y + m_height);
  GL_TEST_ERR;

  ObjectArrayList::iterator objIt;

  for(objIt = m_objects.begin(); objIt != m_objects.end(); ++objIt)
    (*objIt)->draw();
  GL_TEST_ERR;
}
