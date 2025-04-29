#ifndef RENDERER
#define RENDERER

#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>





namespace renderer {

struct circle {

  float origin[2] = { 0.0f, 0.0f };
  float radius = 0.1f;

};

struct colour {

  float colour[3] = { 0.5f, 0.5f, 0.5f };

};

unsigned int VertexArrayObject, VertexBufferObject;

void init() {

    glGenBuffers(1, &VertexBufferObject);
    glGenVertexArrays(1, &VertexArrayObject);

    glBindVertexArray(VertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(4 * sizeof(float)));
    glEnableVertexAttribArray(1);

}

}



namespace render {

  void circle(renderer::circle object, renderer::colour colour) {

    int pointCount = 4*12;
    float* points = new float[pointCount*8];

    for (int counter = 0; counter < pointCount; counter++) {

      float angle = ((float)counter/pointCount)*360;
      // X Pos
      points[(counter*8)+0] = (cos((angle/180)*M_PI)*object.radius)+object.origin[0];
      // Y Pos
      points[(counter*8)+1] = (sin((angle/180)*M_PI)*object.radius)+object.origin[1];
    
      points[(counter*8)+2] = 0.0f;
      points[(counter*8)+3] = 1.0f;
      points[(counter*8)+4] = colour.colour[0];
      points[(counter*8)+5] = colour.colour[1];
      points[(counter*8)+6] = colour.colour[2];
      points[(counter*8)+7] = 1.0f;

    }

    glBindBuffer(GL_ARRAY_BUFFER, renderer::VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*pointCount*8, points, GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLE_FAN, 0, pointCount);

  }

}

#endif // RENDERER
