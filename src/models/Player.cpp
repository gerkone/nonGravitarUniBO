
#include "Player.hpp"

namespace player{

  Player::Player(int fuel = STARTING_FUEL, int lives = STARTING_LIVES, double x_axis = 0; int y_axis = 0, sf::Texture image, double x_momentum = 0, double y_momentum = 0) {
    this.fuel = fuel;
    this.lives = lives;
    this.player.setTexture(image);
    this.player.setPosition(sf::Vector2f(x_axis, y_axis));
    this.x_momentum = x_momentum;
    this.y_momentum = y_momentum;
  }

  void Player::update_momentum() {
    x_momentum = x_momentum - DRAG_RATIO * x_momentum;
    y_momentum = y_momentum - DRAG_RATIO * y_momentum;
  }

  void Player::fire() {

  }

  void Player::tractor() {

  }

  void Player::moveDx() {

  }

  void Player::moveSx() {

  }

  void Player::moveDw() {

  }

  void Player::moveUp() {

  }

  double Player::getX() {
    return x_axis;
  }

  int Player::getY() {
    return y_axis;
  }

  int Player::getFuel() {
    return fuel;
  }

  int Player::getLives() {
    return lives;
  }
}
