#ifndef FUEL_HPP
#define FUEL_HPP

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
const int FUEL_SMALL = 1000;
const int FUEL_BIG = 2000;
const int FUEL_WIDTH = 15;
const int FUEL_HEIGHT = 30;

class Fuel{
  public:
    Fuel(float x = 0, float y = 0); //la y va settata rispetto al terreno
    sf::RectangleShape getRectangle();
    int getFuel();  //restituisce il valore del carburante e setta isActive a false
    bool isActive();
    float getY();
    float getX();
  private:
    sf::RectangleShape mFuel;
    int capacity;
    bool active;
};
#endif //FUEL_HPP
