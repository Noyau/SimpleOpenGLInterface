#ifndef OPENGLUTILS_HPP
#define OPENGLUTILS_HPP

#ifdef __WIN32
#include <Windows.h>
#include <GL/GL.h>
#include <GL/GLU.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif // __WIN32

#include <QImage>
#include <cstdint>

#ifndef NO_OPENGL_DEBUG
#include <iostream>
#define GL_TEST_ERR \
{\
  GLenum eCode(glGetError());\
  if(eCode != GL_NO_ERROR)\
    std::cerr << "OpenGL error (" << eCode << ") in " << __FILE__ << " at " << __LINE__ << std::endl;\
}
#else //-----------------
#define GL_TEST_ERR
#endif // NO_OPENGL_DEBUG

/// \brief It draws a textured quad
inline void glUtilsTexturedQuad()
{
  glBegin(GL_QUADS);
  glTexCoord2f(0.f, 0.f);
  glVertex2f(0.f, 0.f);

  glTexCoord2f(1.f, 0.f);
  glVertex2f(1.f, 0.f);

  glTexCoord2f(1.f, 1.f);
  glVertex2f(1.f, 1.f);

  glTexCoord2f(0.f, 1.f);
  glVertex2f(0.f, 1.f);
  glEnd();
}

/// \brief It set OpenGL color from uint32 rgb color
inline void glUtilsRGBColor(const uint32_t &rgb)
{
  uint8_t r((rgb >> 16) & 0xff);
  uint8_t g((rgb >>  8) & 0xff);
  uint8_t b( rgb        & 0xff);

  glColor3f(r / 255.f, g / 255.f, b / 255.f);
}

/// \brief It creates an OpenGL texture from QGLWidget converted image
bool glUtilsCreateTextureFromImage(const QImage &glImg, GLuint *texId);

#endif // OPENGLUTILS_HPP
