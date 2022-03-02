#pragma once
#include <GL/glew.h>
class cube{
  private:
    //vertices order
    //ftopleft tr bl br
    //btopleft tr bl br
    GLfloat data[24];
    GLuint indices[36] = {2,1,0,1,2,3,5,1,3,7,5,3,0,1,5,5,4,0,6,3,2,7,3,6,7,6,4,4,5,7,4,2,0,6,2,4};
  public:
  cube(GLfloat x, GLfloat y, GLfloat z,GLfloat edgelength);
  ~cube();
  GLfloat* getVertexData();
  GLuint* getIndexData();
};
