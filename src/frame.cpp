#include "frame.hpp"

#include "container.hpp"
#include "openglutils.hpp"

Frame::Frame()
{
}

Frame::~Frame()
{
  ContainerArrayList::iterator it;
  for(it = m_containers.begin(); it != m_containers.end(); ++it)
    delete *it;
}

int Frame::width()
{
  return m_width;
}

int Frame::height()
{
  return m_height;
}

void Frame::setSize(int w, int h)
{
  m_width  = w;
  m_height = h;
}

void Frame::addContainer(Container *pCont)
{
  m_containers.push_back(pCont);
}

void Frame::draw()
{
  ContainerArrayList::iterator itCont;

  for(itCont = m_containers.begin(); itCont != m_containers.end(); ++itCont)
    (*itCont)->draw();

  GL_TEST_ERR;
}
