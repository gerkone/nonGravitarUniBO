#ifndef WORLD_HPP
#define WORLD_HPP

#include <SFML/Graphics.hpp>
#include <list>
#include <iostream>
#include <Bunker.hpp>
#include <Fuel.hpp>
#include <ProjectileHandler.hpp>
#include <ResourceHolder.hpp>

class World{

  private:
    struct voxel{
      double x;
      double y;
    };

  private:
    typedef std::vector<std::vector<Bunker>>::iterator bunker_iterator;
    typedef std::vector<std::vector<Fuel>>::iterator fuel_iterator;

  public:
    //spawn coordinate of the circle in the main window
    World(float x, float y, sf::RenderWindow& mWindow, ProjectileHandler& handler, ResourceHolder& holder);
    sf::CircleShape getCircle();
    sf::ConvexShape getTerrain();//return the VertexArray holding the terrain;use in window.draw(getTerrain)
    //used for debugging
    void debugging();
    void terrainGenerator();//initialize the VertexArray
    void nextView();
    void preView();
    void draw();//draw the terrain and the bunker
    fuel_iterator& getFuelIterator();
    bunker_iterator& getBunkerIterator();
    std::vector<std::vector<Bunker>> getBunkerMatrix();
    voxel* getVoxel();



  private:
    void voxel_gen(int start, int end, float displacement);//called in terrainGenerator(), initialize all the point
    void test(); //print the content of vx
    bool checkBunkerCollision(std::vector<Bunker> v, sf::FloatRect rect);
    bool checkFuelCollision(std::vector<Fuel> v, sf::FloatRect rect);

  public:
    static const int SEGMENT_LIMIT;//number of segment in the terrain

  private:
    static const int MAX_VIEWS;//max number of generated terrain
    static const int MIN_VIEWS;//min ""
    static const float VARIANCE;//roughness of the terrain
    static const float DISPLACEMENT;//
    static const int MAX_BUNKERS;//the max number of bunkers spawned in a view
    static const int MAX_FUELS; //the max number of fuels spawned in a view

    sf::CircleShape mPlanet;
    sf::RenderWindow* mWindow;//reference to the main window
    std::list<unsigned> mSeeds; //holds all the seeds used to initialize the terrain
    std::list<unsigned>::iterator mIterator;//hold the current seed used to generate the terrain
    voxel* vx; //holds all the point used to initialize the terrain
    sf::ConvexShape mTerrain;
    std::vector<std::vector<Bunker>> mBunkerMatrix; // v[i] contiene il vettore dei bunker nella schermata corrente
    std::vector<std::vector<Fuel>> mFuelMatrix; //v[i] holds the vector of fuel showed in the view
    bunker_iterator mBunkerIterator;
    fuel_iterator mFuelIterator;
    sf::Text mText;
    ProjectileHandler* mProjectileHandler;
    ResourceHolder* mResourceHolder;


};
#endif //WORLD_HPP
