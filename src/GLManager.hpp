#ifndef GLMANAGER
#define GLMANAGER

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

namespace glThings {

class glManager {
private:
  struct ShapeData {

    unsigned int pointCount;

    float* points;

    unsigned int VertexArrayObject, VertexBufferObject;

    unsigned int renderMode;

  };

  std::vector<ShapeData> shapes;


public:
  
  void createSquare(float left = -0.5f, float right = 0.5f, float bottom = -0.5f, float top = 0.5f) {

    ShapeData square;


    square.pointCount = 4;

    square.points = new float[4*8] {
      left, bottom, 0.0f, 1.0f,  // Bottom Left
          0.9f, 0.0f, 0.0f, 1.0f, // Colour

       right, bottom, 0.0f, 1.0f,  // Bottom Right
          0.9f, 0.0f, 0.0f, 1.0f, // Colour

      right, top, 0.0f, 1.0f,  // Top Right
          0.9f, 0.0f, 0.0f, 1.0f, // Colour

      left, top, 0.0f, 1.0f,  // Top Left
          0.9f, 0.0f, 0.0f, 1.0f  // Colour
    };

    glGenBuffers(1, &square.VertexBufferObject);
    glGenVertexArrays(1, &square.VertexArrayObject);

    glBindVertexArray(square.VertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, square.VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*4*8, square.points, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(4 * sizeof(float)));
    glEnableVertexAttribArray(1);

    square.renderMode = 6;


    shapes.push_back(square);
  }

  void renderObjects() {

    for (const auto& shape : shapes) {

      glBindVertexArray(shape.VertexArrayObject);
      if (shape.renderMode == 0) glDrawArrays(GL_POINTS, 0, shape.pointCount);
      else if (shape.renderMode == 1) glDrawArrays(GL_LINES, 0, shape.pointCount);
      else if (shape.renderMode == 2) glDrawArrays(GL_LINE_STRIP, 0, shape.pointCount);
      else if (shape.renderMode == 3) glDrawArrays(GL_LINE_LOOP, 0, shape.pointCount);
      else if (shape.renderMode == 4) glDrawArrays(GL_TRIANGLES, 0, shape.pointCount);
      else if (shape.renderMode == 5) glDrawArrays(GL_TRIANGLE_STRIP, 0, shape.pointCount);
      else if (shape.renderMode == 6) glDrawArrays(GL_TRIANGLE_FAN, 0, shape.pointCount);

    }

  }

};

} // namespace glThings

#endif // GLMANAGER
