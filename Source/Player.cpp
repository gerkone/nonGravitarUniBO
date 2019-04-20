#include <Player.hpp>

const float Player::PlayerSpeed = 200.f;

Player::Player(std::string texturePath, sf::RenderWindow& window)
: mWindow(window)
, mTexture()
, mIsMovingUp(false)
, mIsMovingDown(false)
, mIsMovingLeft(false)
, mIsMovingRight(false)
, mMovement(0.f, 0.f)
{
    if(!mTexture.loadFromFile(texturePath)){
      mWindow.close();
    }
    mPlayer.setTexture(mTexture);
    mPlayer.setPosition(100.f, 100.f);
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
}

bool Player::getIsMovingUp(){
  return mIsMovingUp;
}

bool Player::getIsMovingDown(){
  return mIsMovingDown;
}

bool Player::getIsMovingLeft(){
  return mIsMovingLeft;
}

bool Player::getIsMovingRight(){
  return mIsMovingRight;
}

void Player::draw(){
  mWindow.draw(mPlayer);
}

void Player::setPosition(float x, float y){
  mPlayer.setPosition(x,y);
}

sf::Vector2f Player::getPosition(){
  return mPlayer.getPosition();
}

sf::FloatRect Player::getGlobalBounds(){
  return mPlayer.getGlobalBounds();
}

void Player::move(sf::Time elapsedTime){
  mPlayer.move(mMovement * elapsedTime.asSeconds());
}

void Player::setRotation(float rotation){
  mPlayer.setRotation(rotation);
}

void Player::update(sf::Time elapsedTime){
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

}

sf::FloatRect Player::getLocalBounds(){
  return mPlayer.getLocalBounds();
}
