#include <Bullet.hpp>

Bullet::Bullet(float x, float y, int angle, bool type, float dmg_multi) {
  mTexture.loadFromFile("Media/Textures/laser.png");  //gestire gli errori
  mBullet.setTexture(mTexture);
  mBullet.setPosition(x, y);
  mBullet.setRotation(angle);

  mVector = sf::Vector2f(SPEED * sin(angle), SPEED * cos(angle));
  damage = MIN_DAMAGE * dmg_multi;
  enemy = type;
}

void Bullet::move(sf::Time elapsedTime){
  mBullet.move(mVector * elapsedTime.asSeconds());
}


sf::Sprite Bullet::getBullet() {
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
