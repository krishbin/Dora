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
#include <common/mesh.h>
#include <common/model.hpp>
#include "vertexBuffer.hpp"
#include "indexBuffer.hpp"
#include "polygons.hpp"
#include <common/filesystem.h>
#include <stb_image.h>
#include "dijkstra.hpp"

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
  //hide cursor for testing
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

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

  stbi_set_flip_vertically_on_load(false);
  GLuint programID = LoadShaders( FileSystem::getPath("src/VertexShader.glsl"), FileSystem::getPath("src/FragmentShader.glsl") );

  GLuint MatrixID = glGetUniformLocation(programID, "MVP");

  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  Model house(FileSystem::getPath("assets/house.obj"));

  int offseth = -10;
  int offsetv = 10;
  vector<vec3> houseModelTranslation;
  houseModelTranslation.push_back(vec3(0+offsetv,0,0+offseth));

  houseModelTranslation.push_back(vec3(-30,0,20+offseth));
  houseModelTranslation.push_back(vec3(30+offsetv,0,20));

  houseModelTranslation.push_back(vec3(-30,0,50+offseth));
  houseModelTranslation.push_back(vec3(30+offsetv,0,50));
  houseModelTranslation.push_back(vec3(0,0,50));

  houseModelTranslation.push_back(vec3(-30,0,80+offseth));
  houseModelTranslation.push_back(vec3(30+offsetv,0,80));

  houseModelTranslation.push_back(vec3(0,0,100));

  vector<float> houseModelRotation;
  houseModelRotation.push_back(180.0f);

  houseModelRotation.push_back(-90.0f);
  houseModelRotation.push_back(90.0f);

  houseModelRotation.push_back(-90.0f);
  houseModelRotation.push_back(90.0f);
  houseModelRotation.push_back(0.0f);

  houseModelRotation.push_back(-90.0f);
  houseModelRotation.push_back(90.0f);

  houseModelRotation.push_back(0);

  vec3 vertexLocation[] = {
    vec3(0,0,0),
    vec3(-30+10,0,20),
    vec3(-30+10,0,50),
    vec3(-30+10,0,80),
    vec3(0,0,100),
    vec3(30,0,80-5),
    vec3(30,0,50-5),
    vec3(30,0,20-5),
    vec3(0,0,50),
  };

  Graph simpleGraph(9,vertexLocation);
  simpleGraph.addEdge(0, 1, 4);
  simpleGraph.addEdge(0, 7, 8);
  simpleGraph.addEdge(1, 2, 8);
  simpleGraph.addEdge(1, 7, 11);
  simpleGraph.addEdge(2, 3, 7);
  simpleGraph.addEdge(2, 8, 2);
  simpleGraph.addEdge(2, 5, 4);
  simpleGraph.addEdge(3, 4, 9);
  simpleGraph.addEdge(3, 5, 14);
  simpleGraph.addEdge(4, 5, 10);
  simpleGraph.addEdge(5, 6, 2);
  simpleGraph.addEdge(6, 7, 1);
  simpleGraph.addEdge(6, 8, 6);
  simpleGraph.addEdge(7, 8, 7);

  /*
   * vertex 1: 0,0,0
   */
  do{
    //clear screen
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(programID);

    computeMatricesFromInputs();
    glm::mat4 ProjectionMatrix = getProjectionMatrix();
    glm::mat4 ViewMatrix = getViewMatrix();
    glm::mat4 ModelMatrix = glm::mat4(1.0);

    vector<vec3>::iterator it;
    vector<float>::iterator itr;
    for(it = houseModelTranslation.begin(),itr = houseModelRotation.begin(); it != houseModelTranslation.end(); ++it,++itr){
      glm::mat4 translate = glm::translate(*it);
      glm::mat4 rotate = glm::rotate(glm::radians(*itr),vec3(0,1,0));
      glm::mat4 MVP = ProjectionMatrix * ViewMatrix * translate * rotate * ModelMatrix;
      glUniformMatrix4fv(MatrixID,1,GL_FALSE,&MVP[0][0]);
      house.Draw(programID);
    }
    glm::mat4 pvm = ProjectionMatrix * ViewMatrix * ModelMatrix;
    simpleGraph.drawShortestPath(0,3,pvm);
    simpleGraph.drawAllNodes(pvm);

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
