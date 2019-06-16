#include <Player.hpp>
#include <iostream>
#include <cassert>

const float Player::PlayerSpeed = 200.f;
const float Player::BEAM_WIDTH = 10.f;
const float Player::BEAM_HEIGHT = 50.f;
const float Player::MAX_FUEL = 1000.f;
const float Player::DECREASE_FUEL = 0.5f;
const sf::Time Player::SHOOT_RATE = sf::seconds(0.5f);
const int Player::LIFEPOINTS = 5;

Player::Player(sf::RenderWindow& window, ProjectileHandler& handler, ResourceHolder& holder)
: mWindow(&window)
, mIsMovingUp(false)
, mIsMovingDown(false)
, mIsMovingLeft(false)
, mIsMovingRight(false)
, mMovement(0.f, 0.f)
, mBeamIsPressed(false)
, mIsShooting(false)
, mBeam()
, mFuel(MAX_FUEL)
, mProjectileHandler(&handler)
, mClock()
, mText("", window)
, mLifePoints(LIFEPOINTS)
, mResourceHolder(&holder)

{
    if(!mTexture.loadFromFile("Media/Textures/Eagle.png"))
      mWindow->close();

    // mTexture = mResourceHolder->getAircraftTexture();//!!DOESN'T RETURN THE CORRECT AIRCRAFT TEXTURE, WHEN CALLED HERE
    mPlayer.setTexture(mTexture);
    mPlayer.setPosition(100.f, 100.f);

    std::string text = std::to_string(mLifePoints) + " HP";
    mText.setString(text);

    sf::Vector2f position = getPosition();
    sf::FloatRect rect = mPlayer.getGlobalBounds();
    // position.x += rect.width;
    position.y -= rect.height;
    mText.setPosition(position.x, position.y);
    mText.setFont(mResourceHolder->getFont());

    mPlayer.setOrigin(rect.width/2, rect.height/2);
}

void Player::handlePlayerInput(sf::Keyboard::Key key, bool isPressed){
  if (key == sf::Keyboard::W)
    mIsMovingUp = isPressed;
  else if(key == sf::Keyboard::S)
    mIsMovingDown = isPressed;
  else if(key == sf::Keyboard::A)
    mIsMovingLeft = isPressed;
  else if(key == sf::Keyboard::D)
    mIsMovingRight = isPressed;
  else if(key == sf::Keyboard::B)
    mBeamIsPressed = isPressed;
  else if(key == sf::Keyboard::Space)
    mIsShooting = isPressed;
}

void Player::draw(){
  mWindow->draw(mPlayer);
  mWindow->draw(mBeam);
  mText.draw();
}

void Player::setPosition(float x, float y){
  mPlayer.setPosition(x, y);
}

sf::Vector2f Player::getPosition(){
  return mPlayer.getPosition();
}

sf::FloatRect Player::getGlobalBounds(){
  return mPlayer.getGlobalBounds();
}

void Player::move(sf::Time elapsedTime){
  mPlayer.move(mMovement * elapsedTime.asSeconds());
  sf::Vector2f position = getPosition();
  sf::FloatRect rect = mPlayer.getLocalBounds();
  position.x -= rect.width/2 - 10.f;
  position.y -= rect.height / 2 + 30.f;
  mText.setPosition(position.x, position.y);

}

void Player::setRotation(float rotation){
  mPlayer.setRotation(rotation);
}

void Player::update(){
  mMovement.x = 0.f;
  mMovement.y = 0.f;
  if(mIsMovingUp)
    mMovement.y -= PlayerSpeed;
  if(mIsMovingDown)
    mMovement.y += PlayerSpeed;
  if(mIsMovingLeft)
    mMovement.x -= PlayerSpeed;
  if(mIsMovingRight)
    mMovement.x += PlayerSpeed;
  if(mIsMovingUp || mIsMovingDown || mIsMovingLeft || mIsMovingRight)
    mFuel -= DECREASE_FUEL;

}

sf::FloatRect Player::getLocalBounds(){
  return mPlayer.getLocalBounds();
}

sf::Vector2f Player::getCenter(){
  sf::Vector2f center;
  sf::FloatRect sprite = mPlayer.getLocalBounds();
  center.x = 0;
  center.y = sprite.height/2;
  return center;
}

void Player::updateBeam(){
  sf::Vector2f center = getCenter();
  if(mBeamIsPressed){
    mBeam.setSize(sf::Vector2f(BEAM_WIDTH, BEAM_HEIGHT));
    mBeam.setPosition(mPlayer.getPosition().x - BEAM_WIDTH/2, mPlayer.getPosition().y + center.y);
  }
  else{
    mBeam.setSize(sf::Vector2f(0, 0));
    mBeam.setPosition(mPlayer.getPosition().x - BEAM_WIDTH/2, mPlayer.getPosition().y + center.y);
  }
}

sf::FloatRect Player::getBeam(){
  return mBeam.getGlobalBounds();
}

void Player::updateFuel(float fuel){
  if(mFuel + fuel > MAX_FUEL)
    mFuel = MAX_FUEL;
  else
    mFuel += fuel;
}

float Player::getFuel(){
  return mFuel;
}

void Player::shoot(){
  if(mIsShooting){
    sf::Time elapsedTime = mClock.getElapsedTime();
    if(elapsedTime > SHOOT_RATE){//limit the shooting to 1 bullet per second
      Projectile projectile(Projectile::Allied, *mResourceHolder, *mWindow);
      sf::Vector2f movement(0.f, 1.f);
      projectile.guideTowards(movement);
      sf::Vector2f position = getCenter();
      projectile.setPosition(mPlayer.getPosition().x, mPlayer.getPosition().y + position.y);
      mProjectileHandler->addProjectile(projectile);
      std::cout << "Bullet Size = " << mProjectileHandler->getProjectileVector()->size() << std::endl;
      sf::Time temp = mClock.restart(); //return the elapsed time
    }
  }
}

void Player::hit(){
  mLifePoints--;
  std::string text = std::to_string(mLifePoints) + " HP";
  mText.setString(text);
}

int Player::getLife(){
  return mLifePoints;
}
