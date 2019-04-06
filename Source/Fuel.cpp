#include <Fuel.hpp>

Fuel::Fuel(float x, float y, int v) {
  mFuel.setSize(sf::Vector2f(FUEL_HEIGHT, FUEL_WIDTH));
  mFuel.setPosition(x, y);
  isActive = true;
  onView = v;

  srand(time(0));
  if(rand()%2 > 1) {  //estratta dimensione/colore del carburante
    mFuel.setOutlineColor(sf::Color::Orange);
    capacity = FUEL1;
  } else {
    mFuel.setOutlineColor(sf::Color::Red);
    capacity = FUEL2;
  }
}

sf::RectangleShape Fuel::getRectangle() {
  return mFuel;
}

int Fuel::getFuel() {
  isActive = false;
  return capacity;
}

bool Fuel::isActive() {
  return isActive;
}

void Fuel::setY(float offY) {
  mFuel.move(o, offY - FUEL_HEIGHT);  //- FUEL_HEIGHT per mantenerlo al di sopra del terreno
}

int Fuel::getView() {
  return onView;
}
