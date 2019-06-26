#include <Fuel.hpp>

const int Fuel::FUEL_SMALL = 100;
const int Fuel::FUEL_BIG = 200;

Fuel::Fuel(sf::RenderWindow& window, ResourceHolder& holder, float x, float y)
: mWindow(&window)
, mResourceHolder(&holder)

{
    mFuel.setTexture(mResourceHolder->getFuelTexture());
    mFuel.setPosition(x, y);
    mFuel.scale(0.1f, 0.1f);
    mCapacity = ((rand() % 2 == 0) ? FUEL_SMALL : FUEL_BIG);
}

sf::FloatRect Fuel::getRectangle(){
  return mFuel.getGlobalBounds();
}

int Fuel::getFuel(){
  return mCapacity;
}

void Fuel::draw(){
  mWindow->draw(mFuel);
}
