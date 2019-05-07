#include <Player.hpp>

const float Player::PlayerSpeed = 200.f;
const float Player::BEAM_WIDTH = 10.f;
const float Player::BEAM_HEIGHT = 50.f;

Player::Player(std::string texturePath, sf::RenderWindow& window)
: mWindow(window)
, mTexture()
, mIsMovingUp(false)
, mIsMovingDown(false)
, mIsMovingLeft(false)
, mIsMovingRight(false)
, mTractor(false)
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
  else if(key == sf::Keyboard::Space)
    mTractor = isPressed;
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
bool Player::getTractor() {
  return mTractor;
}

sf::RectangleShape Player::getBeam() {
  return mBeam;
}

void Player::draw(){
  mWindow.draw(mBeam);
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

void Player::updateBeam() {
  float centerX = 29; //trovato a tentativi in attessa di un modo migliore
  float centerY = 13;
  if(mTractor) {
    mBeam.setSize(sf::Vector2f(BEAM_WIDTH, BEAM_HEIGHT));
    mBeam.setPosition(mPlayer.getPosition().x - centerX, mPlayer.getPosition().y - centerY);
  } else {
    mBeam.setSize(sf::Vector2f(BEAM_WIDTH, 0));
    mBeam.setPosition(mPlayer.getPosition().x - centerX, mPlayer.getPosition().y - centerY);
  }
}

sf::FloatRect Player::getLocalBounds(){
  return mPlayer.getLocalBounds();
}

sf::FloatRect Player::getBeamBounds(){
  return mBeam.getGlobalBounds();
}
