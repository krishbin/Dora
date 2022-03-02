// position
#include <GLFW/glfw3.h>
#include <iostream>
extern GLFWwindow* window;
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"

glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}
glm::vec3 position = glm::vec3( 0, 10, 10 );
// horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// vertical angle : 0, look at the horizon
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 55.0f;

float speed = 20.0f; // 3 units / second
float mouseSpeed = 0.1f;

void computeMatricesFromInputs(){
    // glfwGetTime is called only once, the first time this function is called
    static double lastTime = glfwGetTime();
    double currentTime = glfwGetTime();
    float deltaTime = float(currentTime - lastTime);
    double xpos, ypos;
    glfwGetCursorPos(window,&xpos, &ypos);
    glfwSetCursorPos(window,1024/2, 768/2);// Compute new orientation

    horizontalAngle += mouseSpeed * deltaTime * float(1024/2 - xpos );
    verticalAngle   += mouseSpeed * deltaTime * float( 768/2 - ypos );
    if(verticalAngle < -1.0f) verticalAngle = -1.0f;
    if(verticalAngle > 1.0f) verticalAngle = 1.0f;

    glm::vec3 direction(
        cos(verticalAngle) * sin(horizontalAngle),
        sin(verticalAngle),
        cos(verticalAngle) * cos(horizontalAngle)
    );

    // Right vector
    glm::vec3 right = glm::vec3(
        sin(horizontalAngle - 3.14f/2.0f),
        0,
        cos(horizontalAngle - 3.14f/2.0f)
    );

    glm::vec3 up = glm::cross( right, direction );

    // Move forward
    if (glfwGetKey(window, GLFW_KEY_UP ) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_W ) == GLFW_PRESS){
        position += direction * deltaTime * speed;
    }
    // Move backward
    if (glfwGetKey(window, GLFW_KEY_DOWN ) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_S ) == GLFW_PRESS){
        position -= direction * deltaTime * speed;
    }
    // Strafe right
    if (glfwGetKey(window, GLFW_KEY_RIGHT ) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_D ) == GLFW_PRESS){
        position += right * deltaTime * speed;
    }
    // Strafe left
    if (glfwGetKey(window, GLFW_KEY_LEFT ) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_A ) == GLFW_PRESS){
        position -= right * deltaTime * speed;
    }

    float FoV = initialFoV;// - 5 * glfwGetseWheel();

    // Projection matrix : 45&deg; Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
    ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 500.0f);
    // Camera matrix
    ViewMatrix       = glm::lookAt(
        position,           // Camera is here
        position+direction, // and looks here : at the same position, plus "direction"
        up                  // Head is up (set to 0,-1,0 to look upside-down)
    );
    lastTime = currentTime;
};
