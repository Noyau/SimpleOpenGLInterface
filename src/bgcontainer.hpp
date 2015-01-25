#ifndef BGCONTAINER_HPP
#define BGCONTAINER_HPP

#include "container.hpp"

/////////////////////////////////////////////////////
/// \brief The BGContainer class
///
/// The Background container allow to scale, move or
/// rotate the objects from the HUD.
/////////////////////////////////////////////////////
class BGContainer : public Container
{
public:
  BGContainer(Frame *pParent);
  virtual ~BGContainer();
};

#endif // BGCONTAINER_HPP
