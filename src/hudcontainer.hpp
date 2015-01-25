#ifndef HUDCONTAINER_HPP
#define HUDCONTAINER_HPP

#include "container.hpp"

/////////////////////////////////////////////////////
/// \brief The HUDContainer class
///
/// The HUD contains the objects to be used in
/// BG container.
/////////////////////////////////////////////////////
class HUDContainer : public Container
{
public:
  HUDContainer(Frame *pParent);
  virtual ~HUDContainer();
};

#endif // HUDCONTAINER_HPP
