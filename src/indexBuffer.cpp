#include "indexBuffer.hpp"

indexBuffer::indexBuffer(const void* data,GLuint count){
  glGenBuffers(1, &renderID);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(GLuint), data, GL_STATIC_DRAW);
}
indexBuffer::~indexBuffer(){
  glDeleteBuffers(1, &renderID);
}
void indexBuffer::bind() const{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderID);
};
void indexBuffer::unbind() const{
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
