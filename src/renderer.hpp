#ifndef RENDERER
#define RENDERER

#define _USE_MATH_DEFINES
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vector>

#define M_PI 3.141592653589f




namespace renderer {

static GLFWwindow* exwindow = nullptr;
static std::vector<float> posMultiplier = { 1.0f, 1.0f };
static float desiredScreenRatio = 1.0f;

namespace standard {
  struct circle {
    std::vector<float> origin;
    float radius;
    circle() { origin = { 0.0f, 0.0f }; radius = 0.25; }
    circle(std::vector<float> inputOrigin, float inputRadius) { origin = inputOrigin; radius = inputRadius; }
  };
  struct rectangle {
    std::vector<float> wallsX;
    std::vector<float> wallsY;
    rectangle() { wallsX = { -0.25f, 0.25f }; wallsY = { -0.25f, 0.25f }; }
    rectangle(std::vector<float> inputWallsX, std::vector<float> inputWallsY) {
      wallsX = inputWallsX; wallsY = inputWallsY;
    }
  };
  struct line {
    std::vector<std::vector<float>> points;
    line() { points = {{ -0.25f, -0.25f }, { 0.0f, 0.5f }, { 0.25f, 0.25f }}; }
    line(std::vector<std::vector<float>> inputPoints) {
      points = inputPoints;
    }
  };
}

namespace rectangle {
  struct bordered {
    std::vector<float> wallsX = { -0.25f, 0.25f };
    std::vector<float> wallsY = { -0.25f, 0.25f };
    float borderWidth = 0.02f;
    bordered() { wallsX = { -0.25f, 0.25f }; wallsY = { -0.25f, 0.25f }; borderWidth = 0.02f; }
    bordered(std::vector<float> inputWallsX, std::vector<float> inputWallsY, float inputBorderWidth) {
      wallsX = inputWallsX; wallsY = inputWallsY; borderWidth = inputBorderWidth;
    }
  };
  struct rounded {
    std::vector<float> wallsX = { -0.25f, 0.25f };
    std::vector<float> wallsY = { -0.25f, 0.25f };
    float radius = 0.1f;
    rounded() { wallsX = { -0.25f, 0.25f }; wallsY = { -0.25f, 0.25f }; radius = 0.1f; }
    rounded(std::vector<float> inputWallsX, std::vector<float> inputWallsY, float inputRadius) {
      wallsX = inputWallsX; wallsY = inputWallsY; radius = inputRadius;
    }
  };
  struct roundBordered {
    std::vector<float> wallsX = { -0.25f, 0.25f };
    std::vector<float> wallsY = { -0.25f, 0.25f };
    float radius = 0.1f;
    float borderWidth = 0.02f;
    roundBordered() { wallsX = { -0.25f, 0.25f }; wallsY = { -0.25f, 0.25f }; radius = 0.1f; borderWidth = 0.02f; }
    roundBordered(std::vector<float> inputWallsX, std::vector<float> inputWallsY,
      float inputRadius, float inputBorderWidth
    ) {
      wallsX = inputWallsX; wallsY = inputWallsY; radius = inputRadius; borderWidth = inputBorderWidth;
    }
  };
}


struct colour {
  std::vector<float> rgb = { 0.5f, 0.5f, 0.5f };
  float alpha = 1.0f;
  colour() { rgb = { 0.5f, 0.5f, 0.5f }; alpha = 1.0f; }
  colour(std::vector<float> inputRgb) { rgb = inputRgb; alpha = 1.0f; }
  colour(std::vector<float> inputRgb, float inputAlpha) { rgb = inputRgb; alpha = inputAlpha; }
};
static void addPoint(float *points, int counter,
  float p1, float p2, float p3, float p4,
  renderer::colour colour
) {
  points[(counter*8)+0] = posMultiplier[0]*(p1);
  points[(counter*8)+1] = posMultiplier[1]*(p2);
  points[(counter*8)+2] = p3;
  points[(counter*8)+3] = p4;
  points[(counter*8)+4] = colour.rgb[0];
  points[(counter*8)+5] = colour.rgb[1];
  points[(counter*8)+6] = colour.rgb[2];
  points[(counter*8)+7] = colour.alpha;
}

static unsigned int VertexArrayObject, VertexBufferObject;

static std::vector<int> getWindowDimensions() {

  std::vector<int> dimensions = { 0, 0 };

  glfwGetWindowSize(exwindow, &dimensions[0], &dimensions[1]);

  return dimensions;

}
static void framebuffer_size_callback(GLFWwindow *window, int width, int height) {

  if ((float)width > (float)height*desiredScreenRatio) {
    posMultiplier[0] = (float)(height*desiredScreenRatio)/width;
    posMultiplier[1] = 1.0f;
  } else {
    posMultiplier[0] = 1.0f;
    posMultiplier[1] = (float)width/((float)height*desiredScreenRatio);
  }

  glViewport(0, 0, width, height);

}
static void getWindowHandle(GLFWwindow* windowHandle) {
  exwindow = windowHandle;
}
static GLFWwindow* init(int width, int height, float desiredscrRatio) {

  // initialise GLFW
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
  // initialise GLFW window
  GLFWwindow *window = glfwCreateWindow(width, height, "glThings", NULL, NULL);
  if (window == NULL) {
    glfwTerminate();
    throw "Failed to create GLFW window";
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, renderer::framebuffer_size_callback);
  // initialise GLAD function pointers
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw "Failed to initialize GLAD";
  }

  glGenBuffers(1, &VertexBufferObject);
  glGenVertexArrays(1, &VertexArrayObject);

  glBindVertexArray(VertexArrayObject);
  glBindBuffer(GL_ARRAY_BUFFER, VertexBufferObject);

  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(4 * sizeof(float)));
  glEnableVertexAttribArray(1);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  exwindow = window;

  desiredScreenRatio = desiredscrRatio;

  return window;

}
}



namespace render {

class standard {
  public:
  static void circle(renderer::standard::circle object, renderer::colour colour) {

    int pointCount = 4*12;
    float* points = new float[pointCount*8];

    for (int counter = 0; counter < pointCount; counter++) {

      float angle = ((float)counter/pointCount)*360;

      renderer::addPoint(
        points, counter,
        ((cos((angle/180)*M_PI)*object.radius/renderer::desiredScreenRatio)+object.origin[0]),
        (sin((angle/180)*M_PI)*object.radius)+object.origin[1],
        0.0f, 1.0f, colour
      );

    }

    glBindBuffer(GL_ARRAY_BUFFER, renderer::VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*pointCount*8, points, GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLE_FAN, 0, pointCount);

    delete [] points;

  }
  static void rectangle(renderer::standard::rectangle object, renderer::colour colour) {

    int pointCount = 4;
    float* points = new float[pointCount*8];

    int counter = 0;

    for (int i = 0; i < 4; i++) {

      addPoint(
        points, counter,
        object.wallsX[((i+0)/2)%2],
        object.wallsY[((i+1)/2)%2],
        0.0f, 1.0f, colour
      );

      counter++;
    }
    

    glBindBuffer(GL_ARRAY_BUFFER, renderer::VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*pointCount*8, points, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLE_FAN, 0, pointCount);

    delete [] points;

  }
  static void line(renderer::standard::line object, renderer::colour colour) {

    int pointCount = (int)object.points.size();
    float* points = new float[pointCount*8];

    for (int i = 0; i < pointCount; i++) {

      addPoint(
        points, i,
        object.points[i][0],
        object.points[i][1],
        0.0f, 1.0f, colour
      );

    }

    glBindBuffer(GL_ARRAY_BUFFER, renderer::VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*pointCount*8, points, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_LINE_STRIP, 0, pointCount);

    delete [] points;

  }
};

class rectangle {
  public:
  static void rounded(renderer::rectangle::rounded object, renderer::colour colour) {

    int pointCount = (4*12)+4;
    float* points = new float[pointCount*8];
    int counter = 0;
    int counterOffset = 0;

    for (int i = 0; i < 4; i++) {

      int xIndex = ((i+3)/2)%2;
      int yIndex = ((i+2)/2)%2;

      float wallsXRadiusModifier;
      float wallsYRadiusModifier;
      if (xIndex == 0) { wallsXRadiusModifier = object.radius; } else { wallsXRadiusModifier = -object.radius; }
      if (yIndex == 0) { wallsYRadiusModifier = object.radius; } else { wallsYRadiusModifier = -object.radius; }

      for (int j = 0; j < (pointCount-4)/4; j++) {

        float angle = ((float)(((float)(pointCount-4)/4)*i+j)/(pointCount-4))*360;

        addPoint(
          points, counter,
          cos((angle/180)*M_PI)*object.radius/renderer::desiredScreenRatio+object.wallsX[((i+3)/2)%2]+wallsXRadiusModifier/renderer::desiredScreenRatio,
          sin((angle/180)*M_PI)*object.radius                             +object.wallsY[((i+2)/2)%2]+wallsYRadiusModifier,
          0.0f, 1.0f, colour
        );

        counter++;
      }

      float allignmentAngle = ((float)(((float)(pointCount-4)/4)*i+((float)(pointCount-4)/4))/(pointCount-4))*360;

      addPoint(
        points, counter+counterOffset,
        cos(allignmentAngle/180*M_PI)*object.radius/renderer::desiredScreenRatio+object.wallsX[xIndex]+wallsXRadiusModifier/renderer::desiredScreenRatio,
        sin(allignmentAngle/180*M_PI)*object.radius                             +object.wallsY[yIndex]+wallsYRadiusModifier,
        0.0f, 1.0f, colour
      );

      counter++;

    }
    
    glBindBuffer(GL_ARRAY_BUFFER, renderer::VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*pointCount*8, points, GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLE_FAN, 0, pointCount);

    delete [] points;

  }
  static void bordered(renderer::rectangle::bordered object, renderer::colour colourInternal,
    renderer::colour colourBorder
  ) {

    int pointCount = 4;
    float* pointsInternal = new float[pointCount*8];
    float* pointsExternal = new float[pointCount*8];

    int counter = 0;

    for (int i = 0; i < 4; i++) {
    
      float wallsXBorderModifier;
      if (((i+0)/2)%2 == 0) { wallsXBorderModifier = object.borderWidth; }
      if (((i+0)/2)%2 == 1) { wallsXBorderModifier = -object.borderWidth; }
      
      float wallsYBorderModifier;
      if (((i+1)/2)%2 == 0) { wallsYBorderModifier = object.borderWidth; }
      if (((i+1)/2)%2 == 1) { wallsYBorderModifier = -object.borderWidth; }

      addPoint(
        pointsInternal, counter,
        object.wallsX[((i+0)/2)%2]+wallsXBorderModifier/renderer::desiredScreenRatio,
        object.wallsY[((i+1)/2)%2]+wallsYBorderModifier,
        0.0f, 1.0f, colourBorder
      );

      addPoint(
        pointsExternal, counter,
        object.wallsX[((i+0)/2)%2],
        object.wallsY[((i+1)/2)%2],
        0.0f, 1.0f, colourInternal
      );

      counter++;
    }
    

    glBindBuffer(GL_ARRAY_BUFFER, renderer::VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*pointCount*8, pointsExternal, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLE_FAN, 0, pointCount);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*pointCount*8, pointsInternal, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLE_FAN, 0, pointCount);

    delete [] pointsInternal;
    delete [] pointsExternal;

  }
  static void roundBordered(const renderer::rectangle::roundBordered object,
    const renderer::colour colourInternal, const renderer::colour colourBorder
  ) {

    int pointCount = (4*12)+4;
    float* pointsInternal = new float[pointCount*8];
    float* pointsExternal = new float[pointCount*8];
    int counter = 0;
    int counterOffset = 0;

    for (int i = 0; i < 4; i++) {
        
      int xIndex = ((i+3)/2)%2;
      int yIndex = ((i+2)/2)%2;

      float wallsXRadiusModifier;
      float wallsYRadiusModifier;
      if (xIndex == 0) { wallsXRadiusModifier = object.radius; } else { wallsXRadiusModifier = -object.radius; }
      if (yIndex == 0) { wallsYRadiusModifier = object.radius; } else { wallsYRadiusModifier = -object.radius; }

      float wallsXBorderModifier;
      float wallsYBorderModifier;
      if (xIndex == 0) { wallsXBorderModifier = object.borderWidth; } else { wallsXBorderModifier = -object.borderWidth; }
      if (yIndex == 0) { wallsYBorderModifier = object.borderWidth; } else { wallsYBorderModifier = -object.borderWidth; }

      for (int j = 0; j < (pointCount-4)/4; j++) {

        float angle = ((float)(((float)(pointCount-4)/4)*i+j)/(pointCount-4))*360;

        addPoint(
          pointsExternal, counter+counterOffset,
          cos(angle/180*M_PI)*object.radius/renderer::desiredScreenRatio+object.wallsX[xIndex]+wallsXRadiusModifier/renderer::desiredScreenRatio,
          sin(angle/180*M_PI)*object.radius                             +object.wallsY[yIndex]+wallsYRadiusModifier,
          0.0f, 1.0f, colourBorder
        );

        addPoint(
          pointsInternal, counter+counterOffset,
          cos(angle/180*M_PI)*(object.radius-object.borderWidth)/renderer::desiredScreenRatio+object.wallsX[xIndex]+(wallsXBorderModifier+wallsXRadiusModifier)/renderer::desiredScreenRatio,
          sin(angle/180*M_PI)*(object.radius-object.borderWidth)                             +object.wallsY[yIndex]+(wallsYBorderModifier+wallsYRadiusModifier),
          0.0f, 1.0f, colourInternal
        );

        counter++;
      }

      float allignmentAngle = ((float)(((float)(pointCount-4)/4)*i+((float)(pointCount-4)/4))/(pointCount-4))*360;

      addPoint(
        pointsExternal, counter+counterOffset,
        cos(allignmentAngle/180*M_PI)*object.radius/renderer::desiredScreenRatio+object.wallsX[xIndex]+wallsXRadiusModifier/renderer::desiredScreenRatio,
        sin(allignmentAngle/180*M_PI)*object.radius                             +object.wallsY[yIndex]+wallsYRadiusModifier,
        0.0f, 1.0f, colourBorder
      );

      addPoint(
        pointsInternal, counter+counterOffset,
        cos(allignmentAngle/180*M_PI)*(object.radius-object.borderWidth)/renderer::desiredScreenRatio+object.wallsX[xIndex]+(wallsXBorderModifier+wallsXRadiusModifier)/renderer::desiredScreenRatio,
        sin(allignmentAngle/180*M_PI)*(object.radius-object.borderWidth)                             +object.wallsY[yIndex]+(wallsYBorderModifier+wallsYRadiusModifier),
        0.0f, 1.0f, colourInternal
      );

      counterOffset++;

    }

    glBindBuffer(GL_ARRAY_BUFFER, renderer::VertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*pointCount*8, pointsExternal, GL_DYNAMIC_DRAW);
    glDrawArrays(GL_TRIANGLE_FAN, 0, pointCount);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*pointCount*8, pointsInternal, GL_DYNAMIC_DRAW);

    glDrawArrays(GL_TRIANGLE_FAN, 0, pointCount);

    delete [] pointsInternal;
    delete [] pointsExternal;

  }
};

}

#endif // RENDERER
