#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

GLFWwindow* window;

int width=1024,height=768;

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <common/shader.hpp>
#include <common/controls.hpp>
#include "vertexBuffer.hpp"
#include "indexBuffer.hpp"
#include "polygons.hpp"

using namespace glm;

int main(){
  //initialize glfw
  glewExperimental = true; // Needed for core profile
  if( !glfwInit() )
  {
    fprintf( stderr, "Failed to initialize GLFW\n" );
    return -1;
  }
  glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL 

  // Open a window and create its OpenGL context
  window = glfwCreateWindow( width, height, "Dora", NULL, NULL);
  if( window == NULL ){
    fprintf( stderr, "Failed to open GLFW window.\n" );
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window); // Initialize GLEW
  if (glewInit() != GLEW_OK) {
    fprintf(stderr, "Failed to initialize GLEW\n");
    return -1;
  }

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
  // Enable depth test
  glEnable(GL_DEPTH_TEST);
  // Accept fragment if it closer to the camera than the former one
  // Cull triangles which normal is not towards the camera
  glEnable(GL_CULL_FACE);
  glDepthFunc(GL_LESS);

  GLuint VertexArrayID;
  glGenVertexArrays(1, &VertexArrayID);
  glBindVertexArray(VertexArrayID);

  GLuint programID = LoadShaders( "../src/VertexShader.glsl", "../src/FragmentShader.glsl" );

  GLuint MatrixID = glGetUniformLocation(programID, "MVP");

  cube c(1,1,1,2);
  vertexBuffer vbo(c.getVertexData(),24*sizeof(float));
  indexBuffer ebo(c.getIndexData(),36);

  do{
    //clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(programID);

    computeMatricesFromInputs();
    glm::mat4 ProjectionMatrix = getProjectionMatrix();
    glm::mat4 ViewMatrix = getViewMatrix();

    for(int i = -16; i < 15; ++i){
    for(int j = -16; j < 15; ++j){
    glm::mat4 ModelMatrix = glm::mat4(1.0);
    glm::mat4 translate = glm::translate(vec3(i*5+4,0,j*4+4));
    glm::mat4 MVP = ProjectionMatrix * ViewMatrix * translate * ModelMatrix;
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
    glEnableVertexAttribArray(0);
    vbo.bind();
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);
    ebo.bind();
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
   }
   }

    glfwSwapBuffers(window);
    glfwPollEvents();

  } // Check if the ESC key was pressed or the window was closed
  while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
      glfwWindowShouldClose(window) == 0 );
  glDeleteProgram(programID);
  glDeleteVertexArrays(1, &VertexArrayID);
  // Close OpenGL window and terminate GLFW
  glfwTerminate();

  return 0;
}
