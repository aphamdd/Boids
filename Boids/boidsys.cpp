#pragma once
#include "boidsys.h"
#include <iostream>
using namespace std;

BoidSys::BoidSys() {}

void BoidSys::update(Boid& boid, const float dt) {
  speedometer(boid);
  sf::Vector2f pos(boid.getPos());
  sf::Vector2f vel(boid.getVel());
  float turnfactor = 10;

  // turn factor
  if (pos.x < SCREEN_WIDTH - SCREEN_WIDTH + MARGIN)
    boid.setvx(vel.x + turnfactor);
  if (pos.x > SCREEN_WIDTH - MARGIN)
    boid.setvx(vel.x - turnfactor);
  if (pos.y < SCREEN_HEIGHT - SCREEN_HEIGHT + MARGIN)
    boid.setvy(vel.y + turnfactor);
  if (pos.y > SCREEN_HEIGHT - MARGIN)
    boid.setvy(vel.y - turnfactor);

  /* bouncing
  if (pos.x < 50 || pos.x > 750)
    boid.setvx(-vel.x);
  else if (pos.y < 50 || pos.y > 750)
    boid.setvy(-vel.y);
    */
  /* reset
  if (pos.x > 800 || pos.x < 0 || pos.y > 800 || pos.y < 0)
    boid.setPos(sf::Vector2f(400, 400));
  */

  vel = boid.getVel();
  boid.setPos(sf::Vector2f(pos.x + (vel.x*dt), pos.y + (vel.y*dt)));
}

void BoidSys::speedometer(Boid& boid) {
  sf::Vector2f pos(boid.getPos());
  sf::Vector2f vel(boid.getVel());

  // alpha max plus beta min algorithm
  float speed = sqrt(vel.x * vel.x + vel.y * vel.y);
  if (speed < MIN_SPEED) {
    boid.setvx((vel.x / speed) * MIN_SPEED);
    boid.setvy((vel.y / speed) * MIN_SPEED);
  }
  else if (speed > MAX_SPEED) {
    boid.setvx((vel.x / speed) * MAX_SPEED);
    boid.setvy((vel.y / speed) * MAX_SPEED);
  }
}
