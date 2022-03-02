#include "polygons.hpp"

cube::cube(GLfloat x, GLfloat y, GLfloat z,GLfloat edgelength){
  GLfloat halfLength = edgelength/2;
  data[0] =  x - halfLength;
  data[1] =  y + halfLength;
  data[2] =  z + halfLength;

  data[3] =  x + halfLength;
  data[4] =  y + halfLength;
  data[5] =  z + halfLength;

  data[6] =  x - halfLength;
  data[7] =  y - halfLength;
  data[8] =  z + halfLength;

  data[9] =  x + halfLength;
  data[10] = y - halfLength;
  data[11] = z + halfLength;

  data[12] = x - halfLength;
  data[13] = y + halfLength;
  data[14] = z - halfLength;

  data[15] = x + halfLength;
  data[16] = y + halfLength;
  data[17] = z - halfLength;

  data[18] = x - halfLength;
  data[19] = y - halfLength;
  data[20] = z - halfLength;

  data[21] = x + halfLength;
  data[22] = y - halfLength;
  data[23] = z - halfLength;
};
cube::~cube(){
};
GLfloat* cube::getVertexData(){
  return data;
};
GLuint* cube::getIndexData(){
  return indices;
};
