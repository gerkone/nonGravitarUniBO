#ifndef FUEL_HPP
#define FUEL_HPP

#include <SFML/Graphics.hpp>
#include <iostream>
#include <ResourceHolder.hpp>

class Fuel{
  public:
    Fuel(sf::RenderWindow& window, ResourceHolder& holder, float x, float y);
    sf::FloatRect getRectangle();//get the rectangle around the sprite
    int getFuel();//return the fuel
    void draw();//draw the sprite in the window passed in the constructor

  private:
    sf::Sprite mFuel;
    sf::RenderWindow* mWindow;
    int mCapacity;
    ResourceHolder* mResourceHolder;

  private:
    static const int FUEL_SMALL;
    static const int FUEL_BIG;
};

#endif //FUEL_HPP
