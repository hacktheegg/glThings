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
}

int main() {
  std::cout << "Hello, World!" << std::endl;


  GLFWwindow *window = renderer::init(windowWidth, windowHeight, 1.0f);


  //// SHADERS ////
  Shader ourShader("./shader.vert", "./shader.frag");

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

    points.push_back({i*2, (float)sin(i*M_PI)});

  }

  renderer::standard::line line(points);

  renderer::getWindowHandle(window);


  renderer::container PositivePositive = renderer::container({0.0f,1.0f},{0.0f,1.0f});

  // uncomment this call to draw in wireframe polygons.
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  while (!glfwWindowShouldClose(window)) {

    //std::cout << static_cast<float>(sin(glfwGetTime()*0.5f)) << std::endl;

    /*
    renderer::baseContainer.wallsX[0] = static_cast<float>(sin(
      (glfwGetTime()*M_PI + (M_PI /4 *0)) * 0.5f
    ));
    renderer::baseContainer.wallsX[1] = static_cast<float>(sin(
      (glfwGetTime()*M_PI + (M_PI /4 *2)) * 0.5f
    ));
    renderer::baseContainer.wallsY[0] = static_cast<float>(sin(
      (glfwGetTime()*M_PI + (M_PI /4 *4)) * 0.5f
    ));
    renderer::baseContainer.wallsY[1] = static_cast<float>(sin(
      (glfwGetTime()*M_PI + (M_PI /4 *6)) * 0.5f
    ));
    */

    processInput(window);


    // std::vector<int> screenWidthHeight = renderer::getWindowDimensions();

    // renderer::desiredScreenRatio = (float)screenWidthHeight[0]/screenWidthHeight[1];
    //renderer::framebuffer_size_callback(window, screenWidthHeight[0], screenWidthHeight[1]);


    glClearColor(
      /*
      (sin(glfwGetTime() + (3.14f / 3 * 3)) + 1.0f) / 2.0f, // red
      (sin(glfwGetTime() + (3.14f / 3 * 2)) + 1.0f) / 2.0f, // green
      (sin(glfwGetTime() + (3.14f / 3 * 1)) + 1.0f) / 2.0f, // blue
      */
      0.10f, 0.10f, 0.10f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    ourShader.use();


    render::rectangle::roundBordered(exRectangleRoundBordered, renderer::colour({0,0,0}), renderer::colour({0,1,0}));
    render::standard::circle(exCircle, renderer::colour({1,0,0}));
    //render::standard::rectangle(exRectangle, renderer::colour({0,1,0}));
    render::rectangle::rounded(exRectangleRounded, renderer::colour({0,0,1}));
    render::rectangle::bordered(exRectangleBordered, renderer::colour({1,1,1}), renderer::colour({1,0,0}));
    //render::standard::line(line, renderer::colour({0,1,0}));


    render::standard::rectangle(&PositivePositive,
      renderer::standard::rectangle({-1.0f,1.0f},{-1.0f,1.0f}),
      renderer::colour({0,1,0}));
    

    //renderer::desiredScreenRatio = ( sin( ( glfwGetTime() / 10 ) * M_PI * 2 ) + 1.0f ) * 4;

    //render::standard::circle(circle1, renderer::colour({1,0,0},0.5));
    //render::standard::circle(circle2, renderer::colour({0,1,0},0.5));
    //render::standard::circle(circle3, renderer::colour({0,0,1},0.5));


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
