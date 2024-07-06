#include "boid.h"
#include "common.h"
#include <random>
#include <iostream>
using namespace std;

Boid::Boid(const int r1, const int r2) :
  m_boid(1.f, 5),
  m_vx(r1), m_vy(r2),
  m_position(0, 0) {

  createBoid();
  m_boid.setOrigin(sf::Vector2f(m_boid.getRadius(), m_boid.getRadius()));
}

void Boid::createBoid() {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> d1(0, SCREEN_WIDTH);
  std::uniform_int_distribution<std::mt19937::result_type> d2(0, SCREEN_HEIGHT);
  std::uniform_int_distribution<std::mt19937::result_type> d3(1, 4);
  switch (d3(rng)) {
  case 1:
    m_boid.setFillColor(sf::Color::Yellow);
    break;
  case 2:
    m_boid.setFillColor(sf::Color::Green);
    break;
  case 3:
    m_boid.setFillColor(sf::Color::Cyan);
    break;
  case 4:
    m_boid.setFillColor(sf::Color::Magenta);
    break;
  default:
    m_boid.setFillColor(sf::Color::Red);
    break;
  }
  m_boid.setOutlineThickness(1.f);
  m_boid.setOutlineColor(sf::Color::Black);

  setPos(sf::Vector2f(d1(rng), d2(rng)));
}

void Boid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  //states.transform *= getTransform();
  states.texture = NULL;
  target.draw(m_boid, states);
}

/* makes x amount of triangles in one VertexArray of the same size at random locations
void Boid::createBoids() {
  std::random_device dev;
  std::mt19937 rng(dev());
  std::uniform_int_distribution<std::mt19937::result_type> dist1(0, 780);
  std::uniform_int_distribution<std::mt19937::result_type> dist2(0, 780);
  for (int i = 0; i < m_boids.size(); i += 3) {
    int rand1 = dist1(rng);
    int rand2 = dist2(rng);
    sf::Vector2f top(10 + rand1, 0 + rand2);
    sf::Vector2f bottomLeft(0 + rand1, 20 + rand2);
    sf::Vector2f bottomRight(20 + rand1, 20 + rand2);

    m_vertices[i].position = top;
    m_vertices[i + 1].position = bottomLeft;
    m_vertices[i + 2].position = bottomRight;
    m_vertices[i].color = sf::Color::Red;
  }
}
*/
