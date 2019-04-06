#include <Bullet.hpp>

Bullet::Bullet(float x, float y, int angle, bool type) {
  mBullet =
  {
      sf::Vertex(sf::Vector2f(x, y)),
      sf::Vertex(sf::Vector2f(x + LENGHT, y))
  };
  mBullet.rotate(angle);

  damage = MIN_DAMAGE * dmg_multi;
  isEnemy = type;
}

sf::Vertex* Bullet::getLine() {
  return mBullet;
}

int getDamage() {
  return damage;
}

bool Bullet::isEnemy() {
  return isEnemy;
}

void hit() {
  hasHit = true;
}

bool hasHit() {
  return hasHit;
}
