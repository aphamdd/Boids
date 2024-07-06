#pragma once
#include "boid.h"
#include "common.h"
#include "SFML/Graphics.hpp"

class BoidSys {
public:
  BoidSys();

  void update(Boid&, const float dt);
  void speedometer(Boid&);
};
