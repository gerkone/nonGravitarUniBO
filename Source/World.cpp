#include <World.hpp>

World::World(float x, float y){
  mPlanet.setRadius(20);
  mPlanet.setOutlineColor(sf::Color::Red);
  mPlanet.setOutlineThickness(5);
  mPlanet.setPosition(x,y);
}

sf::CircleShape World::getCircle(){
  return mPlanet;
}
