#ifndef BUNKER_HPP
#define BUNKER_HPP

#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>

const int BUNKER_RADIUS = 10;
const int POINTS = 100; //punti ricevuti alla distruzione del bunker

class Bunker{
  public:
    Bunker(float x, float y); //la y va settata rispetto al terreno
    sf::CircleShape getCircle();
    //int getFireMode();
    bool isActive();
    int getHitpoints();
    int hit(int hp);
    float getY();
    float getX();
  private:
    sf::CircleShape mBunker;

    bool active;
    int hitpoints; //quanti colpi riesce a sopportare il bunker
};
#endif //BUNKER_HPP
