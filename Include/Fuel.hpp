#ifndef FUEL_HPP
#define FUEL_HPP

#include <time.h>
#include <iostream>
const int FUEL_SMALL = 1000;
const int FUEL_BIG = 2000;
const int FUEL_WIDTH = 15;
const int FUEL_HEIGHT = 30;

class Fuel{
  public:
    Fuel(float x = 0, float y = 0, int v = 1); //la y va settata rispetto al terreno
    sf::RectangleShape getRectangle();
    int getFuel();  //restituisce il valore del carburante e setta isActive a false
    bool isActive();
    void setY(float y); //necessaria per generazione graduale del terreno, va passato l'offset di cui abbassare la RectangleShape
    int getView();  //disegnare i fuel nelle y giuste e nelle view giuste e' delegato alla classe game, istanziarli alla classe world
    float getY();
    float getX();
  private:
    sf::RectangleShape mFuel;
    int capacity;
    bool active;
    int onView; //tiene la parte del pianeta su cui apparirà il fuel
};
#endif //FUEL_HPP
