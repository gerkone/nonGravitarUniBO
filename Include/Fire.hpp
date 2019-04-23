#ifndef FIRE_HPP
#define FIRE_HPP

#include <Bullet.hpp>
#include <time.h>
#include <iostream>

const int BULLET_SPEED = 10;
const int MIN_FIRESTEP = 500; //tempo minimo tra un colpo e l'altro (in millisec)
const int TRIPLE_ANGLE_STEP = 30; //angolo tra i tre bullet del bunker triplo

enum FireMode
{
  Player, //riservato al player -> firingAngle= 270; fireStep = min; isEnemy = false
  Single, //bunker standard -> firingAngle= 90; fireStep = 4*min; isEnemy = true
  Triple  //bunker triplo -> firingAngle= 60,90,120; fireStep = 8*min; isEnemy = true
};


class Fire{
  public:
    Fire(FireMode mode, float speed, float x, float y);
    std::list<sf::Vertex*> getBullets();
    void updateBullets(); //aggiorna la lista dei bullet rimuovendo quelli usciti dalla finestra/che hanno colpito; la gestione delle collisioni e il calo della vita è fatto nella classe game
    bool isEnemy();
    void setFiringAngle(int angle);
    int getFireStep();
    int getFiringAngle();
    void setPosition(float x, float y);
    void shoot();
  private:
    std::list<Bullet> mBullets;
    FireMode eFireMode;

    float fx;  //posizione da cui "partono" i bullet
    float fy;

    bool enemy;   //chi possiede l'istanza
    int fireStep;   //tempo tra un colpo e l'altro
    int elapsedStep; //tempo dall'ultimo colpo
    int firingAngle;  //angolo a cui vengono inizializzati i bullet sparati
    float speed;  //velocita' a cui si muovono i proiettili
    sf::Vector2f mMovement; //vettore spostamento del bullet
};

#endif //FIRE_HPP
