#include "openglutils.hpp"

bool glUtilsCreateTextureFromImage(const QImage &glImg, GLuint *texId)
{
  if(glImg.isNull())
    return false;

  glEnable(GL_TEXTURE_2D);
  GL_TEST_ERR;

  glGenTextures(1, texId);
  GL_TEST_ERR;

  if(*texId == 0)
    return false;

  glBindTexture(GL_TEXTURE_2D, *texId);
  GL_TEST_ERR;

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
  GL_TEST_ERR;

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
               glImg.width(), glImg.height(),
               0, GL_RGBA, GL_UNSIGNED_BYTE, glImg.bits()
               );
  GL_TEST_ERR;

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  GL_TEST_ERR;

  glDisable(GL_TEXTURE_2D);
  GL_TEST_ERR;

  return true;
}
