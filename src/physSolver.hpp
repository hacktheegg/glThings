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

void newPhysObj(physObject object) {

  objects.push_back(object);

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
