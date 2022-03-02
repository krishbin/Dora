#pragma once
#include <GL/glew.h>
class vertexBuffer{
  private:
  GLuint renderID;
  public:
  vertexBuffer(const void* data,GLuint size);
  ~vertexBuffer();
  void bind();
  void unbind();
};
