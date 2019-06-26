#include <Projectile.hpp>

const int Projectile::BULLET_VELOCITY = 500;

Projectile::Projectile(Type type, ResourceHolder& holder, sf::RenderWindow& window) : mType(type), mResourceHolder(&holder), mWindow(&window){
  mTargetDirection = sf::Vector2f(0.f, 0.f);
  mProjectile.setTexture(mResourceHolder->getProjectileTexture());
  mProjectile.setScale(0.05f, 0.05f);
  //mProjectile.setRotation(180.f);
}

void Projectile::guideTowards(sf::Vector2f position){
  mTargetDirection.x = position.x * BULLET_VELOCITY;
  mTargetDirection.y = position.y * BULLET_VELOCITY;
}

Projectile::Type Projectile::getType(){
  return mType;
}

sf::FloatRect Projectile::getRectangle(){
  return mProjectile.getGlobalBounds();
}

void Projectile::draw(){
  mWindow->draw(mProjectile);
}

void Projectile::move(sf::Time elapsedTime){
  mProjectile.move(mTargetDirection * elapsedTime.asSeconds());
}

sf::Vector2f Projectile::getPosition(){
  return mProjectile.getPosition();
}

void Projectile::setPosition(float x, float y){
  sf::Vector2f position(x, y);
  mProjectile.setPosition(position);
}
