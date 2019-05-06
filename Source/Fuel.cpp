#include <Fuel.hpp>

Fuel::Fuel(float x, float y) {
  mFuel.setSize(sf::Vector2f(FUEL_HEIGHT, FUEL_WIDTH));
  mFuel.setPosition(x, y);
  active = true;

  srand(time(0));
  if(rand()%2 > 1) {  //estratta dimensione/colore del carburante
    mFuel.setOutlineColor(sf::Color::Yellow);
    capacity = FUEL_SMALL;
  } else {
    mFuel.setOutlineColor(sf::Color::Red);
    capacity = FUEL_BIG;
  }
}

float Fuel::getY() {
  return mFuel.getPosition().y;
}

float Fuel::getX() {
  return mFuel.getPosition().x;
}

sf::RectangleShape Fuel::getRectangle() {
  return mFuel;
}

int Fuel::getFuel() {
  active = false;
  return capacity;
}

bool Fuel::isActive() {
  return active;
}
