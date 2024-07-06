#pragma once
#include "SFML/Graphics.hpp"

class Boid : public sf::Drawable, public sf::Transformable {
friend class BoidSys;
public:
  Boid(const int, const int);
  sf::Vector2f getVel() const { return sf::Vector2f(m_vx, m_vy); }
  sf::Vector2f getPos() const { return m_position; }

public:
  void setvx(const float x) { m_vx = x; }
  void setvy(const float y) { m_vy = y; }
  void setPos(const sf::Vector2f pos) { 
    m_position = pos; 
    m_boid.setPosition(m_position.x, m_position.y);
  }

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates state) const;
  void createBoid();

private:
  sf::CircleShape m_boid;
  sf::Vector2f m_position;
  float m_vx;
  float m_vy;
};
