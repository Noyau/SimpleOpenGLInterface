#ifndef FRAME_HPP
#define FRAME_HPP

#include <vector>

class Container;
typedef std::vector<Container *> ContainerArrayList;

/////////////////////////////////////////////////////
/// \brief The Frame class
///
/// The Frame class contains all containers that will
/// contains objects.
/// The Frame defines the viewport of the scene.
/////////////////////////////////////////////////////
class Frame
{
public:
  Frame();
  ~Frame();

  /// Screen size
  int width();
  int height();

  void setSize(int w, int h);

  void addContainer(Container *pCont);

  void draw();

protected:
  int m_width, m_height;

  ContainerArrayList m_containers;
};

#endif // FRAME_HPP
