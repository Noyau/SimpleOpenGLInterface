#include "bgcontainer.hpp"

#include "openglutils.hpp"

BGContainer::BGContainer(Frame *pParent)
  : Container(pParent)
{
  m_width  = .8f;
  m_height = 1.f;
  m_color  = 0xffffff; // white
}

BGContainer::~BGContainer()
{

}
