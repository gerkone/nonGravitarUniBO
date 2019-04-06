#ifndef BULLET_HPP
#define BULLET_HPP

#include <Bullet.hpp>

#include <time.h>
#include <iostream>
#include <list>

const int MIN_DAMAGE = 50;  //vita tolta se si viene colpiti
const float LENGHT = 30.0; //lunghezza del segmento linea

class Bullet{
  public:
    Bullet(float x, float y, int angle, bool type, float dmg_multi); //x,y rispetto a chi spara; type per chi ha sparato (player o bunker); dmg_multi per settare il moltiplicatore del danno
    sf::Vertex* getLine();
    bool isEnemy();
    void hit();
    int getDamage();
    bool hasHit();
  private:
    sf::Vertex mBullet[2];  //linea
    int damage; //danni fatti se si viene colpiti(si colpisce)
    bool isEnemy; //bullet alleati non possono danneggiare il player
    bool hasHit; //true se il proiettile ha colpito/è uscito dallo schermo
};
#endif //BULLET_HPP
