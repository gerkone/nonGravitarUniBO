#include <Bullet.hpp>

Bullet::Bullet(float x, float y, int angle, bool type, float dmg_multi) {
  mBullet[0] = sf::Vertex(sf::Vector2f(x, y));
  mBullet[1] = sf::Vertex(sf::Vector2f(x + LENGHT, y));

  damage = MIN_DAMAGE * dmg_multi;
  enemy = type;
}

sf::Vertex* Bullet::getLine() {
  return mBullet;
}

int Bullet::getDamage() {
  return damage;
}

bool Bullet::isEnemy() {
  return enemy;
}

void Bullet::doHit() {
  hit = true;
}

bool Bullet::hasHit() {
  return hit;
}
