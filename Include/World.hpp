#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>

#include <list>
#include <time.h>
#include <iostream>
#include <math.h>

const int SEGMENT_LIMIT = 1000; //segmenti massimi che comporranno il terreno
const int MAX_VIEWS = 5; //schermate massime
const int MIN_VIEWS = 3; //schermate massime

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 500;

const double VARIANCE = 0.55; //ruvidità di scalo tra displacement tra passaggi successivi
const double DISPLACEMENT = 400; // unità di spostamento (segs * displacement) in px rispetto al numero di segmenti

struct voxel {
  float x;
  float y;
};

class World{
  public:
    //spawn coordinate of the circle in the main window
    World(float x, float y);
    sf::CircleShape getCircle();
    sf::Vector2f getTerrain(int v);
    void nextView();
    void prevView();
  private:
    sf::CircleShape mPlanet;
    sf::Vector2f vx*;
    int seeds*;
    int views;
    int itV;  //iteratore per la view corrente
    void terrainGen(sf::Vector2f vx[], int start, int end, double displ);
};
#endif //WORLD_HPP
