#include <Bunker.hpp>
#include <iostream>

const int Bunker::POINTS = 100;
const int Bunker::LIFEPOINTS = 3;
const sf::Time Bunker::SHOOT_RATE = sf::seconds(2.f);

Bunker::Bunker(sf::RenderWindow& window, ProjectileHandler& handler, ResourceHolder& holder, float x, float y)
: mWindow(&window)
, mHealth()
, mHealthBorder()
, mProjectileHandler(&handler)
, mClock()
, mResourceHolder(&holder)
{

  mBunker.setTexture(mResourceHolder->getBunkerTexture());
  mBunker.setPosition(x, y);
  mBunker.setScale(0.3, 0.3);//scale the texture
  mHitpoints = LIFEPOINTS;

  sf::Vector2f position = mBunker.getPosition();
  sf::FloatRect rect = mBunker.getGlobalBounds();
  position.y += rect.height + 3.f;

  sf::Vector2f size(120.f, 20.f);
  mHealth.setSize(size);
  mHealth.setPosition(position);
  mHealth.setFillColor(sf::Color::Red);

  mHealthBorder.setSize(size);
  mHealthBorder.setPosition(position);
  mHealthBorder.setOutlineColor(sf::Color::White);
  mHealthBorder.setOutlineThickness(1);
  mHealthBorder.setFillColor(sf::Color::Transparent);

  if(rand()%2 == 1){
    mType = Basic;
  }
  else{
    mType = Advanced;
  }

}

sf::FloatRect Bunker::getRectangle() {
  return mBunker.getGlobalBounds();
}

// int Bunker::getFireMode() {
//   return fireMode;
// }


void Bunker::hit() {
  mHitpoints -= 1;
  float scale = mHitpoints / (float)LIFEPOINTS;
  mHealth.setScale(scale, 1.f);
}

int Bunker::getHitpoints() {
  return mHitpoints;
}

void Bunker::draw(){
  mWindow->draw(mHealth);
  mWindow->draw(mHealthBorder);
  mWindow->draw(mBunker);
}

sf::Vector2f Bunker::getPosition(){
  sf::Vector2f position = mBunker.getPosition();
  sf::FloatRect rect = mBunker.getGlobalBounds();
  position.x += (rect.width/2);
  return position;
}

void Bunker::shoot(){
  sf::Time elapsedTime = mClock.getElapsedTime();
  if(elapsedTime > SHOOT_RATE){
    if(mType == Basic){
      sf::Vector2f movement(1.f, -1.f);
      createBullet(movement);

      sf::Vector2f movement2(-1.f, -1.f);
      createBullet(movement2);

    }
    else{
      sf::Vector2f movement(1.f, -1.f);
      createBullet(movement);

      sf::Vector2f movement2(-1.f, -1.f);
      createBullet(movement2);

      sf::Vector2f movement3(0, -1.f);
      createBullet(movement3);
    }

    sf::Time temp = mClock.restart();
  }
}

void Bunker::createBullet(sf::Vector2f movement){
  Projectile projectile(Projectile::Type::Enemy, *mResourceHolder, *mWindow);
  projectile.guideTowards(movement);
  sf::Vector2f position = getPosition();
  projectile.setPosition(position.x, position.y);
  mProjectileHandler->addProjectile(projectile);
}

int Bunker::getPoints(){
  return POINTS;
}
