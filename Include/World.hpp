#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>

#include <Fuel.hpp>
#include <Bunker.hpp>

class World{

  private:
    struct voxel{
      double x;
      double y;
    };

  public:
    //spawn coordinate of the circle in the main window
    World(float x, float y, const sf::RenderWindow& mWindow);
    sf::CircleShape getCircle();
    // int getSegmentLimit();
    // float getDisplacement();
    sf::VertexArray getTerrain();//return the VertexArray holding the terrain;use in window.draw(getTerrain)
    std::list<sf::CircleShape> getBunkers();  //return the fuels/bunkers sprites in the current view
    std::list<sf::RectangleShape> getFuels();
    //used for debugging
    void debugging();
    void terrainGenerator();//initialize the VertexArray
    void itemsGenerator();
    void nextView();
    void preView();
    int getView();


  private:
    void voxel_gen(int start, int end, float displacement);//called in terrainGenerator(), initialize all the point
    void bunkerGenerator();
    void fuelGenerator();
    bool visited(int v); //true if view has already been visited
    void test(); //print the content of vx


  private:

    static const int SEGMENT_LIMIT;//number of segment in the terrain
    static const int MAX_VIEWS;//max number of generated terrain
    static const int MIN_VIEWS;//min ""
    static const float VARIANCE;//roughness of the terrain
    static const float DISPLACEMENT;//
    static const float TERRAIN_TRANSLATION;   //the terrain will be subject to a translation to move it in the game area
    static const int MAX_BUNKERS_PER_VIEW;
    static const int MAX_FUELS_PER_VIEW;

    sf::CircleShape mPlanet;
    const sf::RenderWindow& mWindow;//reference to the main window
    std::list<unsigned> mSeeds; //holds all the seeds used to initialize the terrain
    std::list<unsigned>::iterator mIterator;//hold the current seed used to generate the terrain
    int mView; //current view
    std::list<int> visitList; //holds the views already visited
    voxel* vx; //holds all the point used to initialize the terrain
    sf::VertexArray mTerrain;

    std::list<Fuel> mFuels;
    std::list<Bunker> mBunkers;


};
#endif //WORLD_HPP
