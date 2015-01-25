#ifndef CONTAINER_HPP
#define CONTAINER_HPP

#include <cstdint>
#include <vector>

#include <QGLWidget>

#include "frame.hpp"

class Container;
class Object;

typedef std::vector<Container *> ContainerArrayList;
typedef std::vector<Object *> ObjectArrayList;

/////////////////////////////////////////////////////
/// \brief The Container class
///
/// The Container class is a generic class that
/// contains objects in the scene.
/////////////////////////////////////////////////////
class Container
{
public:
  Container(Frame *pParent);
  virtual ~Container();

  Frame *getParent();

  float width();
  float height();
  float x();
  float y();

  void addObject(Object *pObj);

  ///
  /// \brief Find an object that contains the mouse coordinates
  /// \param mouse coordinates
  /// \return the object pointer if found ; else NULL
  Object *selectObject(const QPointF &mouse);

  ///
  /// \brief Return coordinates relative to bounds of the container
  /// \param p point to be converted
  /// \return the converted point
  QPointF spaceToBounds(const QPointF &p) const;

  virtual void draw();

protected:
  Frame *m_pParent;

  float m_width, m_height;
  float m_x, m_y;

  uint32_t m_color;

  ObjectArrayList m_objects;
};

#endif // CONTAINER_HPP
