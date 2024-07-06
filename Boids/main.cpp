#include "boidsys.h"
#include "particles.h"
#include "imgui.h"
#include "imgui-SFML.h"
#include <iostream>
#include <random>
#include <SFML/Window.hpp>
using namespace std;
// https://people.ece.cornell.edu/land/courses/ece4760/labs/s2021/Boids/Boids.html#Boids!

const int FPS = 3000;
const int NUM_BOIDS = 500;

int main() {
  sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Boid Simluator", sf::Style::Default);
  window.setFramerateLimit(FPS);

  sf::Texture bgTexture;
  sf::Sprite bg;
  sf::Vector2u textureSize;
  sf::Vector2u windowSize;

  if (!bgTexture.loadFromFile("./Textures/background.png"))
    return -1;
  else {
    textureSize = bgTexture.getSize();
    windowSize = window.getSize();
    float scaleX = (float)windowSize.x / textureSize.x;
    float scaleY = (float)windowSize.y / textureSize.y;
    bg.setTexture(bgTexture);
    bg.setScale(scaleX, scaleY);
  }

  // random starting velocity
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> d1(MIN_SPEED, MAX_SPEED);
  std::uniform_int_distribution<std::mt19937::result_type> d2(MIN_SPEED, MAX_SPEED);
  // initialize boids
  BoidSys boidSys;
  std::vector<Boid> boids;
  boids.reserve(NUM_BOIDS);
  for (int i = 0; i < NUM_BOIDS; ++i) {
    boids.push_back(Boid(d1(rng), d2(rng)));
  }
  float visualRange = 150;
  float protectedRange = 30;
  float centeringfactor = 0.0005;
  float avoidfactor = 0.5;
  float matchingfactor = 0.5;

  // initialize particles
  ParticleSystem particles(1000);
  // create a clock to track the elapsed time
  sf::Clock clock;
  sf::Clock dtClock;

  while (window.isOpen()) {
    sf::Event event;
    const float dt = dtClock.restart().asSeconds();

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }

    /* particles
    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    particles.setEmitter(window.mapPixelToCoords(mouse));
    sf::Time elapsed = clock.restart();
    particles.update(elapsed);
    */

    // update boids
    for (int i = 0; i < NUM_BOIDS; ++i) {
      float xavg = 0, yavg = 0, xvel = 0, yvel = 0, neighbor = 0, closedx = 0, closedy = 0;
      float x = boids[i].getPos().x, y = boids[i].getPos().y;
      float vx = boids[i].getVel().x, vy = boids[i].getVel().y;

      for (int j = 0; j < NUM_BOIDS; ++j) {
        float dx = x - boids[j].getPos().x, dy = y - boids[j].getPos().y;
        
        // boids are within the visual range
        if (abs(dx) < visualRange && abs(dy) < visualRange) {
          float squared_distance = dx * dx + dy * dy;
          // boids are inside the protected range
          if (squared_distance < protectedRange) {
            closedx += dx;
            closedy += dy;
          }
          // boid inside visual but not protected
          else if (squared_distance < visualRange) {
            xavg += boids[j].getPos().x;
            yavg += boids[j].getPos().y;
            xvel += boids[j].getVel().x;
            yvel += boids[j].getVel().y;
            neighbor += 1;
          }
        }
      }
     
      // alignment+cohesion
      if (neighbor > 0) {
        xavg = xavg / neighbor;
        yavg = yavg / neighbor;
        xvel = xvel / neighbor;
        yvel = yvel / neighbor;
       
        // steers boids together and matches velocity
        float centering_x = (vx + (xavg - x) * centeringfactor + (xvel - vx) * matchingfactor);
        float centering_y = (vy + (yavg - y) * centeringfactor + (yvel - vy) * matchingfactor);
        boids[i].setvx(centering_x);
        boids[i].setvy(centering_y);
      }

      // avoid boids that are too close together
      vx = boids[i].getVel().x;
      vy = boids[i].getVel().y;
      boids[i].setvx(vx + (closedx * avoidfactor));
      boids[i].setvy(vy + (closedy * avoidfactor));

      boidSys.update(boids[i], dt);
    }

    // rendering
    window.clear(sf::Color::Black);
    window.draw(bg);
    window.draw(particles);
    for (int i = 0; i < NUM_BOIDS; ++i) {
      window.draw(boids[i]);
    }
    window.display();
  }
  return 0;
}