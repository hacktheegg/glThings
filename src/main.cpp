// https://learnopengl.com/Getting-started/Hello-Window

#include <cmath>
#include <iostream>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "GLManager.hpp"
#include "shader_s.hpp"

const float pi = 3.14159265;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
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
  GLFWwindow *window = glfwCreateWindow(512, 512, "glThings", NULL, NULL);
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



  float points[] = {
     0.90f,  0.90f,  0.00f,  1.00f,  0.90f, 0.90f, 0.90f, 1.00f,
     0.90f,  0.00f,  0.00f,  1.00f,  0.00f, 0.00f, 0.90f, 1.00f,
     0.00f,  0.90f,  0.00f,  1.00f,  0.90f, 0.00f, 0.00f, 1.00f,
     0.00f,  0.00f,  0.00f,  1.00f,  0.90f, 0.90f, 0.90f, 1.00f,
    -0.90f, -0.00f, -0.00f,  1.00f,  0.00f, 0.00f, 0.90f, 1.00f,
    -0.00f, -0.90f, -0.00f,  1.00f,  0.90f, 0.00f, 0.00f, 1.00f,
    -0.90f, -0.90f, -0.00f,  1.00f,  0.90f, 0.90f, 0.90f, 1.00f
  };

  unsigned int indices[] = {
    0, 1, 3,
    0, 2, 3,
    3, 4, 6, 5
  };

  //// SHADERS ////
  Shader ourShader("./shader.vert", "./shader.frag");
  /*
  unsigned int VAO, VBO, EBO;

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);


  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(4 * sizeof(float)));
  glEnableVertexAttribArray(1);
  */


  glThings::glManager newManager;
  newManager.createSquare(0.0f,1.0f,0.0f,1.0f);
  newManager.createSquare(0.0f,-1.0f,0.0f,-1.0f);


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
      0.80f, 0.40, 0.20, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);


    ourShader.use();

    newManager.renderObjects();

    /*
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * 0));

    glDrawElements(GL_LINE_LOOP, 4, GL_UNSIGNED_INT, (void*)(sizeof(unsigned int) * 6));
    */

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
