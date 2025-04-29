#ifndef PHYSSOLVER
#define PHYSSOLVER

#include <vector>

#include "renderer.hpp"





namespace physSolver {

struct physObject {

  float origin[2] = { 0.0f, 0.0f };
  float radius = 0.1f;

};



std::vector<physObject> objects = {};

int newPhysObj(std::vector<float> origin = { 0.0f, 0.0f }, float radius = 0.1f) {

  physObject object;
  object.origin[0] = origin[0];
  object.origin[1] = origin[1];
  object.radius = radius;

  objects.push_back(object);

  return objects.size()-1;

}

void renderObjects() {

  for (auto &obj : objects) {
  
    renderer::circle tmpCircle;
    tmpCircle.origin[0] = obj.origin[0];
    tmpCircle.origin[1] = obj.origin[1];
    tmpCircle.radius = obj.radius;

    render::circle(tmpCircle);

  }

}

}

#endif // PHYSSOLVER
