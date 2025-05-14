// https://learnopengl.com/Getting-started/Hello-Window

#include <cmath>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

//#include "physSolver.hpp"
#include "renderer.hpp"
#include "shader_s.hpp"


int windowWidth = 512;
int windowHeight = 512;


bool clickState = false;

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
  glfwSetFramebufferSizeCallback(window, renderer::framebuffer_size_callback);
  // initialise GLAD function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }



  //// SHADERS ////
  Shader ourShader("./shader.vert", "./shader.frag");

  renderer::colour black ({ 0.0f, 0.0f, 0.0f });
  renderer::colour red   ({ 1.0f, 0.0f, 0.0f }, 1.0f);
  renderer::colour green ({ 0.0f, 1.0f, 0.0f }, 1.0f);
  renderer::colour blue  ({ 0.0f, 0.0f, 1.0f }, 1.0f);
  renderer::colour white ({ 1.0f, 1.0f, 1.0f }, 1.0f);

  renderer::standard::circle exCircle({ -0.875f, 0.875f }, 0.125f);
  renderer::standard::rectangle exRectangle({ -0.75f, -0.5f }, { 0.75f, 1.0f });

  renderer::rectangle::rounded exRectangleRounded({ -0.50f, -0.25f }, {  0.75f,  1.0f  }, 0.1f);
  renderer::rectangle::bordered exRectangleBordered({ -0.25, 0.0f }, {  0.75, 1.0f }, 0.02f);
  renderer::rectangle::roundBordered exRectangleRoundBordered({ -1.0f, 1.0f }, { -1.0f, 1.0f }, 0.125f, 0.02f);

  float dist = 1.0f/3.0f;

  renderer::standard::circle circle1({
    (float)cos((((0.0f/3.0f*360)/180)+((1.0f/4.0f*360)/180))*M_PI)*dist,
    (float)sin((((0.0f/3.0f*360)/180)+((1.0f/4.0f*360)/180))*M_PI)*dist
  }, dist*2);
  renderer::standard::circle circle2({
    (float)cos((((1.0f/3.0f*360)/180)+((1.0f/4.0f*360)/180))*M_PI)*dist,
    (float)sin((((1.0f/3.0f*360)/180)+((1.0f/4.0f*360)/180))*M_PI)*dist
  }, dist*2);
  renderer::standard::circle circle3({
    (float)cos((((2.0f/3.0f*360)/180)+((1.0f/4.0f*360)/180))*M_PI)*dist,
    (float)sin((((2.0f/3.0f*360)/180)+((1.0f/4.0f*360)/180))*M_PI)*dist
  }, dist*2);

  std::vector<std::vector<float>> points = {};

  for (float i = -1.0f; i <= 1.0f; i+=0.01f) {

    points.push_back({i, (float)sin(i*M_PI)});

  }

  renderer::standard::line line(points);

  renderer::init();

  renderer::getWindowHandle(window);


  // uncomment this call to draw in wireframe polygons.
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!glfwWindowShouldClose(window)) {

    std::cout << renderer::getWindowDimensions()[0] << std::endl;

    processInput(window);

    //renderer::

    glClearColor(
      /*
      (sin(glfwGetTime() + (3.14f / 3 * 3)) + 1.0f) / 2.0f, // red
      (sin(glfwGetTime() + (3.14f / 3 * 2)) + 1.0f) / 2.0f, // green
      (sin(glfwGetTime() + (3.14f / 3 * 1)) + 1.0f) / 2.0f, // blue
      */
      0.00f, 0.00f, 0.00f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ourShader.use();


    render::rectangle::roundBordered(exRectangleRoundBordered, black, green);
    render::standard::circle(exCircle, red);
    render::standard::rectangle(exRectangle, green);
    render::rectangle::rounded(exRectangleRounded, blue);
    render::rectangle::bordered(exRectangleBordered, white, red);
    render::standard::line(line, green);

    //render::standard::circle(circle1, red);
    //render::standard::circle(circle2, green);
    //render::standard::circle(circle3, blue);


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
