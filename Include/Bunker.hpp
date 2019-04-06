#ifndef BUNKER_HPP
#define BUNKER_HPP

#include <time.h>
#include <iostream>

const int BUNKER_RADIUS = 40;
const int POINTS = 100; //punti ricevuti alla distruzione del bunker

class Bunker{
  public:
    Bunker(float x, float y, int v); //la y va settata rispetto al terreno
    sf::CircleShape getCircle();
    int getFireMode();
    bool isActive();
    void setY(float y); //necessaria per generazione graduale del terreno, va passato l'offset
    int getView();
    int getHitpoints();
    int hit();
  private:
    sf::CircleShape mBunker;
    // FireMode fireMode;
    bool isActive;
    int hitpoints; //quanti colpi riesce a sopportare il bunker
    int onView; //tiene la parte del pianeta su cui apparirà il bunker
};
#endif //BUNKER_HPP
