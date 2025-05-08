// https://learnopengl.com/Getting-started/Hello-Window

#include <cmath>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

//#include "physSolver.hpp"
#include "renderer.hpp"
#include "shader_s.hpp"


int windowWidth = 512;
int windowHeight = 512;


bool clickState = false;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
  /*
  if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS && !clickState) {
    clickState = true;
    double xpos = 0.0;
    double ypos = 0.0;
    glfwGetCursorPos(window, &xpos, &ypos);
    physSolver::newPhysObj(
      {
        ((float)xpos/windowWidth*2)-1.0f,
        -(((float)ypos/windowHeight*2)-1.0f)
      },
      0.02f
    );
  } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) != GLFW_PRESS) {
    clickState = false;
  }
  if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
    double xpos = 0.0;
    double ypos = 0.0;
    glfwGetCursorPos(window, &xpos, &ypos);
    physSolver::newPhysObj(
      {
        ((float)xpos/windowWidth*2)-1.0f,
        -(((float)ypos/windowHeight*2)-1.0f)
      },
      0.02f
    );
  }
  */
}

int main() {
  std::cout << "Hello, World!" << std::endl;

  // initialise GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  // initialise GLFW window
  GLFWwindow *window = glfwCreateWindow(windowWidth, windowHeight, "glThings", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  // initialise GLAD function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }



  //// SHADERS ////
  Shader ourShader("./shader.vert", "./shader.frag");

  renderer::colour black;
  renderer::colour red;
  renderer::colour green;
  renderer::colour blue;
  renderer::colour white;

  black.rgb = { 0.0f, 0.0f, 0.0f };
  red.rgb =   { 1.0f, 0.0f, 0.0f };
  green.rgb = { 0.0f, 1.0f, 0.0f };
  blue.rgb =  { 0.0f, 0.0f, 1.0f };
  white.rgb = { 1.0f, 1.0f, 1.0f };


  renderer::standard::rectangle background({ -1.0f, 1.0f }, { -1.0f, 1.0f });

  renderer::standard::circle exCircle({ -0.875f, 0.875f }, 0.125f);

  renderer::standard::rectangle exRectangle ({ -0.75f, -0.5f }, { 0.75f, 1.0f });
  
  renderer::rectangle::rounded exRectangleRounded({ -0.50f, -0.25f }, {  0.75f,  1.0f  }, 0.1f);
  
  renderer::rectangle::bordered exRectangleBordered({ -0.25, 0.0f }, {  0.75, 1.0f }, 0.02f);

  renderer::rectangle::roundBordered exRectangleRoundBordered({ -0.75, 0.75f }, { -0.75, 0.75f }, 0.1, 0.02f);

  renderer::init();


  // uncomment this call to draw in wireframe polygons.
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!glfwWindowShouldClose(window)) {

    processInput(window);

    glClearColor(
      /*
      (sin(glfwGetTime() + (3.14f / 3 * 3)) + 1.0f) / 2.0f, // red
      (sin(glfwGetTime() + (3.14f / 3 * 2)) + 1.0f) / 2.0f, // green
      (sin(glfwGetTime() + (3.14f / 3 * 1)) + 1.0f) / 2.0f, // blue
      */
      0.80f, 0.40, 0.20, 0.5f);
    glClear(GL_COLOR_BUFFER_BIT);

    ourShader.use();


    //render::rectangle(background, black);

    render::standard::circle(exCircle, red);

    render::standard::rectangle(exRectangle, green);
	
    render::rectangle::rounded(exRectangleRounded, blue);

    render::rectangle::bordered(exRectangleBordered, white, red);

    render::rectangle::roundBordered(exRectangleRoundBordered, white, green);


    // Modes (Swap out the first object given to glDrawElements
    /*
    * GL_POINTS
    * GL_LINES
    * GL_LINE_STRIP
    * GL_LINE_LOOP
    * GL_TRIANGLES
    * GL_TRIANGLE_STRIP
    * GL_TRIANGLE_FAN
    * autocomplete says there are others as well
    */
    glfwSwapBuffers(window);
    glfwPollEvents();
  }










  /*
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  */
  glfwTerminate();
  return 0;
}
