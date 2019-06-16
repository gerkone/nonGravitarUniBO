#ifndef PROJECTILE_HPP
#define PROJECTILE_HPP

#include <SFML/Graphics.hpp>
#include <ResourceHolder.hpp>

class Projectile {
public:
  enum Type {
    Allied,
    Enemy
  };

public:
  Projectile(Type type, ResourceHolder& holder, sf::RenderWindow& window);
  void guideTowards(sf::Vector2f position);
  Type getType();
  sf::FloatRect getRectangle();
  void draw();
  void move(sf::Time elapsedTime);
  sf::Vector2f getPosition();
  void setPosition(float x, float y);

private:
  Type mType;
  sf::Vector2f mTargetDirection;
  sf::Sprite mProjectile;
  sf::RenderWindow* mWindow;
  ResourceHolder* mResourceHolder;

private:
  static const int BULLET_VELOCITY;

};
#endif //PROJECTILE_HPP
