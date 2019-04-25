#include <World.hpp>
#include <iostream>
#include <time.h>

const int World::SEGMENT_LIMIT = 512;
const int World::MAX_VIEWS = 5;
const int World::MIN_VIEWS = 3;
const float World::VARIANCE = 0.65;
const float World::DISPLACEMENT = 200;

const float World::TERRAIN_TRANSLATION = 200.0;

const int World::MAX_BUNKERS_PER_VIEW = 5;
const int World::MAX_FUELS_PER_VIEW = 3;


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
    mView = 0;
  }

sf::CircleShape World::getCircle(){
  return mPlanet;
}

int World::getView() {
  return mView;
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
  vx[0].y = mWindow.getSize().y /2 - TERRAIN_TRANSLATION;//should be a costant
  vx[SEGMENT_LIMIT-1].y = mWindow.getSize().y / 2 - TERRAIN_TRANSLATION;
  double displacement = DISPLACEMENT * VARIANCE;
  voxel_gen(0, SEGMENT_LIMIT-1, displacement);
  for (size_t i = 0; i < SEGMENT_LIMIT; i++) {
    mTerrain[i].position = sf::Vector2f(vx[i].x, mWindow.getSize().y - vx[i].y);
  }
}

sf::VertexArray World::getTerrain(){
  return mTerrain;
}

std::list<sf::CircleShape> World::getBunkers() {
  std::list<sf::CircleShape> items;
  std::list<Bunker>::iterator bit;
  for(bit = mBunkers.begin(); bit != mBunkers.end(); bit++) {
    if((bit->getView() == mView) && (bit->isActive())) {
      items.push_back(bit->getCircle());
    }
  }
  return items;
}

std::list<sf::RectangleShape> World::getFuels() {
  std::list<sf::RectangleShape> items;
  std::list<Fuel>::iterator fit;
  for(fit = mFuels.begin(); fit != mFuels.end(); fit++) {
    if((fit->getView() == mView) && (fit->isActive())) {
      items.push_back(fit->getRectangle());
    }
  }
  return items;
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
  mView = (mView + 1)%mSeeds.size();
  terrainGenerator(); //the order is important!
  itemsGenerator();
}

void World::preView(){
  mIterator--;
  if(mView - 1 < 0) { //bad way to solve an annoying problem
    mView = mSeeds.size() - 1;
  } else {
    mView--;
  }
  terrainGenerator(); //the order is important!
  itemsGenerator();
}

bool World::visited(int v) {
  std::list<int>::iterator it;
  for(it = visitList.begin(); it!= visitList.end();it++) {
    if(*it == v) {
      return true;
    }
  }
  return false;
}

void World::bunkerGenerator() {
  int bunkers = rand()&MAX_BUNKERS_PER_VIEW;
  int pos;
  for(int i = 0; i < bunkers; i++) {
    pos = rand()%SEGMENT_LIMIT;
    Bunker tmpB = Bunker(mTerrain[pos].position.x, mTerrain[pos].position.y, mView);
    mBunkers.push_back(tmpB);
  }
}

void World::fuelGenerator() {
  int fuels = rand()&MAX_FUELS_PER_VIEW;
  int pos;
  for(int i = 0; i < fuels; i++) {
    pos = rand()%SEGMENT_LIMIT;
    Fuel tmpF = Fuel(mTerrain[pos].position.x, mTerrain[pos].position.y, mView);
    mFuels.push_back(tmpF);
  }
}

void World::itemsGenerator() {
  if(!visited(mView)) {
    srand(*mIterator);
    bunkerGenerator();
    fuelGenerator();
    visitList.push_back(mView); //after generating the items adds the view to the already visited
  }
}
