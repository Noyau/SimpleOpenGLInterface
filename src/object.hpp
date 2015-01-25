#ifndef OBJECT_HPP
#define OBJECT_HPP

#include <ostream>
#include <vector>

#include "container.hpp"

class Object;
typedef std::vector<Object *> ObjectArrayList;

/////////////////////////////////////////////////////
/// \brief The Object class
///
/// The Object class is a generic class that defines
/// the scene objects.
/////////////////////////////////////////////////////
class Object
{
public:
  Object(Container *pParent);
  virtual ~Object();

  const Container *getParent() const;
  void setParent(Container *pParent);

  /// Return absolute size and coordinates
  float width() const;
  float height() const;
  float x() const;
  float y() const;
  float angle() const;

  /// Return relatives size and coordinates
  float getVpWidth();
  float getVpHeight();
  float getVpX();
  float getVpY();

  QSizeF getScale();

  void setScale(float sx, float sy);
  void setScale(const QSizeF &s);

  QPointF getPosition();

  void setPosition(float x, float y);
  void setPosition(const QPointF &p);

  void setAngle(float a);

  virtual bool containsPoint(const QPointF &p);

  virtual void draw() = 0;

protected:
  Container *m_pParent;

  /// These data represent relative data
  /// to parent container
  float m_width, m_height;
  float m_x, m_y;
  float m_angle; // in degrees
};

std::ostream &operator<<(std::ostream &out, const Object &o);

#endif // OBJECT_HPP
