#ifndef PLAYER_H
#define PLAYER_H

#include <SFLM/Grapics.hpp>
#include <Image.hpp>
#include <Sprite.hpp>
#include <Texture.hpp>

const STARTING_FUEL = 1000;
const STARTING_LIVES = 3;
const DRAG_RATIO = 0.05;

namespace player{
  class Player(){
  private:
    int lives;
    int fuel;
    // int x_axis;
    // int y_axis;
    // int rotation;
    sf::Sprite player;
    double x_momentum;
    double y_momentum;
  public:
    Player(int fuel, int lives, double x_axis, double y_axis, sf::Texture image, double x_momentum, double y_momentum){}
    //sparo navicella
    void fire(){}
    //raggio traente
    void tractor(){}

    void moveDx(){}
    void moveSx(){}
    void moveDw(){}
    void moveUp(){}
    double getX(){}
    double getY(){}
    int getLives(){}
    int getFuel(){}
    void setLives(int lives){}
    void setFuel(int fuel){}
    void update_momentum(){}

  };

}
#endif //PLAYER_H
