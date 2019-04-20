#include <World.hpp>
#include <iostream>
#include <time.h>

const int World::SEGMENT_LIMIT = 512;
const int World::MAX_VIEWS = 5;
const int World::MIN_VIEWS = 3;
const float World::VARIANCE = 0.65;
const float World::DISPLACEMENT = 200;



World::World(float x, float y, const sf::RenderWindow& Window)
 : mWindow(Window)
 , mTerrain(sf::LineStrip, SEGMENT_LIMIT)
 , vx(nullptr)
  {
    mPlanet.setRadius(20);
    mPlanet.setOutlineColor(sf::Color::Red);
    mPlanet.setOutlineThickness(5);
    mPlanet.setPosition(x,y);
    //srand(time(0));
    int view = rand() % (MAX_VIEWS - MIN_VIEWS) + MIN_VIEWS;
    vx = new voxel[SEGMENT_LIMIT];
    for (size_t i = 0; i < SEGMENT_LIMIT - 1; i++) {
      vx[i].x = i * (mWindow.getSize().x / (double)SEGMENT_LIMIT);
      vx[i].y = 0;
    }
    vx[SEGMENT_LIMIT - 1].x = mWindow.getSize().x;
    for (size_t i = 0; i < view; i++) {
      mSeeds.push_back(rand());
    }

    mIterator = mSeeds.begin();

  }

sf::CircleShape World::getCircle(){
  return mPlanet;
}

//recursive midpoint displacement terrain generation
void World::voxel_gen(int start, int end, float displacement){
  if(start + 1 >= end ){
    return;
  }
  else{
    int mid = (end + start) / 2;
    double rnd = (rand() / (double)RAND_MAX) - 0.5;
    float offset = displacement * rnd;
    vx[mid].y = ((vx[start].y + vx[end].y) / (double)2) + offset;
    displacement = displacement * VARIANCE;
    voxel_gen(start, mid, displacement);
    voxel_gen(mid, end, displacement);
  }
}

void World::test(){
  std::cout << "voxel after init : " << '\n';
  for (size_t i = 0; i < SEGMENT_LIMIT; i++) {
    std::cout << "\t" << "x : " << vx[i].x << "y : " << vx[i].y << '\n';
  }
}

// int World::getSegmentLimit(){
//   return SEGMENT_LIMIT;
// }
//
// float World::getDisplacement(){
//   return DISPLACEMENT;
// }

void World::terrainGenerator(){
  srand(*mIterator);
  vx[0].y = mWindow.getSize().y /2 - 200;//should be a costant
  vx[SEGMENT_LIMIT-1].y = mWindow.getSize().y / 2 - 200;
  double displacement = DISPLACEMENT * VARIANCE;
  voxel_gen(0, SEGMENT_LIMIT-1, displacement);
  for (size_t i = 0; i < SEGMENT_LIMIT; i++) {
    mTerrain[i].position = sf::Vector2f(vx[i].x, mWindow.getSize().y - vx[i].y);
  }
}

sf::VertexArray World::getTerrain(){
  return mTerrain;
}

void World::debugging() {
  std::cout << "current seed : " << *mIterator << '\n';
  std::cout << "all seeds in the list : ";
  for(auto x : mSeeds){
    std::cout << " " << x;
  }
  // terrainGenerator();
  // test();
}

void World::nextView(){
  mIterator++;
  terrainGenerator();
}

void World::preView(){
  mIterator--;
  terrainGenerator();
}
