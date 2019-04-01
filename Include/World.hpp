#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
class World{
  public:
    //spawn coordinate of the circle in the main window
    World(float x, float y);
    sf::CircleShape getCircle();

  private:
    sf::CircleShape mPlanet;

};
#endif //WORLD_HPP
