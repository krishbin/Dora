#include "vertexBuffer.hpp"

vertexBuffer::vertexBuffer(const void* data,GLuint size){
  glGenBuffers(1, &renderID);
  glBindBuffer(GL_ARRAY_BUFFER, renderID);
  glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}
vertexBuffer::~vertexBuffer(){
  glDeleteBuffers(1, &renderID);
}
void vertexBuffer::bind(){
  glBindBuffer(GL_ARRAY_BUFFER, renderID);
};
void vertexBuffer::unbind(){
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
