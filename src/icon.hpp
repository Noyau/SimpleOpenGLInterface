#ifndef ICON_HPP
#define ICON_HPP

#include <string>

#include "object.hpp"
#include "openglutils.hpp"

/////////////////////////////////////////////////////
/// \brief The Icon class
///
/// An icon is an object that contains an OpenGL
/// texture.
/////////////////////////////////////////////////////
class Icon : public Object
{
public:
  Icon(Container *pParent);
  ~Icon();

  ///
  /// \brief Load image and create GL texture from file
  /// \param filename of the image to load
  /// \return true if success ; else false
  bool loadFromFile(const std::string &filename);

  /// \return the absolute size of the icon
  float size();

  /// \return the relative size of the icon
  float getVpSize();

  virtual bool containsPoint(const QPointF &p);

  virtual void draw();

protected:
  GLuint m_texId;
};

#endif // ICON_HPP
