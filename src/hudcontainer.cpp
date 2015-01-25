#include "hudcontainer.hpp"

HUDContainer::HUDContainer(Frame *pParent)
  : Container(pParent)
{
  m_width  = .2f;
  m_height = 1.f;
  m_x      = .8f;
  m_color  = 0x000000; // black
}

HUDContainer::~HUDContainer()
{

}
