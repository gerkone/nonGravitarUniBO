#include <World.hpp>
#include <time.h>
#include <cassert>

const int World::SEGMENT_LIMIT = 512;
const int World::MAX_VIEWS = 5;
const int World::MIN_VIEWS = 2;
const float World::VARIANCE = 0.65;
const float World::DISPLACEMENT = 200;
const int World::MAX_BUNKERS = 3;
const int World::MAX_FUELS = 2;


World::World(float x, float y, sf::RenderWindow& Window, ProjectileHandler& handler, ResourceHolder& holder)
: mWindow(&Window)
, mTerrain(SEGMENT_LIMIT)
, vx(nullptr)
, mText()
, mProjectileHandler(&handler)
, mResourceHolder(&holder)

{

    mText.setFont(mResourceHolder->getFont());
    mText.setPosition(5.f, 30.f);
    mText.setCharacterSize(10);
    mPlanet.setRadius(20);
    mPlanet.setTexture(&mResourceHolder->getRandomPlanetTexture());
    mPlanet.setPosition(x,y);
    sf::FloatRect rect = mPlanet.getGlobalBounds();
    mPlanet.setOrigin(rect.width/2, rect.height/2);
    //srand(time(0));
    int view = rand() % (MAX_VIEWS - MIN_VIEWS) + MIN_VIEWS;//number of seeds i.e number of terrains the world has
    mText.setString(
      "View = " + std::to_string(view) + "\n");

    vx = new voxel[SEGMENT_LIMIT];
    //voxel initialization
    for (size_t i = 0; i < SEGMENT_LIMIT - 3; i++) {
      vx[i].x = i * (mWindow->getSize().x / (double)SEGMENT_LIMIT);
      vx[i].y = 0;
    }
    vx[SEGMENT_LIMIT - 3].x = mWindow->getSize().x;//set the last point to the border
    for (size_t i = 0; i < view; i++) {
      mSeeds.push_back(rand());//initialize the vector of seeds
    }

    mIterator = mSeeds.begin();
    terrainGenerator();
    //bunker and fuel generation
    for (size_t i = 0; i < view; i++) {
      std::vector<Bunker> bunkerVector_tmp;
      std::vector<Fuel> fuelVector_tmp;
      int numberOfBunkers = rand()%MAX_BUNKERS + 1; // at least one bunker is generated
      int numberOfFuels = rand()%MAX_FUELS + 1;

      int bunkerCounter = 0;
      while(bunkerCounter < numberOfBunkers){
        int segment = rand()%(SEGMENT_LIMIT - 50);//avoid to spawn the bunker out of the screen
        float x = vx[segment].x;
        float y = mWindow->getSize().y - vx[segment].y - 88.2f/2; //adds half the height of the bunker so that it spawn above the ground
        Bunker bunker(*mWindow, *mProjectileHandler, *mResourceHolder, x, y);
        sf::FloatRect rect = bunker.getRectangle();
        bool check = checkBunkerCollision(bunkerVector_tmp, rect);
        if(!check){
          bunkerVector_tmp.push_back(bunker);
          bunkerCounter++;
        //   std::cout << k << std::endl;
        }
      }
      int fuel_counter = 0;
      while(fuel_counter < numberOfFuels){
        int segment = rand()%(SEGMENT_LIMIT - 20);//avoid to spawn the bunker out of the screen
        float x = vx[segment].x;
        float y = mWindow->getSize().y - vx[segment].y - 51.f/2; //adds half the height of the bunker so that it spawn above the ground
        Fuel fuel(*mWindow, *mResourceHolder, x, y);
        sf::FloatRect rect = fuel.getRectangle();
        bool check = checkBunkerCollision(bunkerVector_tmp, rect) || checkFuelCollision(fuelVector_tmp, rect);
        if(!check){
          fuelVector_tmp.push_back(fuel);
          fuel_counter++;
        //   std::cout << k << std::endl;
        }
      }

      mBunkerMatrix.push_back(bunkerVector_tmp);
      mFuelMatrix.push_back(fuelVector_tmp);
      mIterator++;
      terrainGenerator();

    }
    mBunkerIterator = mBunkerMatrix.begin();
    mIterator = mSeeds.begin();
    mFuelIterator = mFuelMatrix.begin();

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
  vx[0].y = mWindow->getSize().y /2 - 200;//should be a costant
  vx[SEGMENT_LIMIT-3].y = mWindow->getSize().y / 2 - 200;
  double displacement = DISPLACEMENT * VARIANCE;
  voxel_gen(0, SEGMENT_LIMIT-3, displacement);
  for (size_t i = 0; i < SEGMENT_LIMIT-2; i++) {
    mTerrain.setPoint(i, sf::Vector2f(vx[i].x, mWindow->getSize().y - vx[i].y));
  }
  mTerrain.setPoint(SEGMENT_LIMIT-2, sf::Vector2f(mWindow->getSize().x, mWindow->getSize().y));
  mTerrain.setPoint(SEGMENT_LIMIT-1, sf::Vector2f(0, mWindow->getSize().y));
  mTerrain.setTexture(&mResourceHolder->getTerrainTexture());
}

sf::ConvexShape World::getTerrain(){
  return mTerrain;
}

void World::nextView(){
  if(mIterator == std::prev(mSeeds.end()))//list iterator are bidirectional, but the last iterator points to the size of the list
    mIterator = mSeeds.begin();
  else
    mIterator++;

  if(mBunkerIterator == std::prev(mBunkerMatrix.end())) // vector iterator aren't bidirectional
    mBunkerIterator = mBunkerMatrix.begin();
  else
    mBunkerIterator++;

  if(mFuelIterator == std::prev(mFuelMatrix.end())) // vector iterator aren't bidirectional
    mFuelIterator = mFuelMatrix.begin();
  else
    mFuelIterator++;

  terrainGenerator();
}

void World::preView(){
  if(mIterator == mSeeds.begin())
    mIterator = std::prev(mSeeds.end());
  else
    mIterator--;

  if(mBunkerIterator == mBunkerMatrix.begin())
    mBunkerIterator = std::prev(mBunkerMatrix.end());//iterator before end(), end points after the last element
  else
    mBunkerIterator--;

  if(mFuelIterator == mFuelMatrix.begin())
    mFuelIterator = std::prev(mFuelMatrix.end());//iterator before end(), end points after the last element
  else
    mFuelIterator--;

  terrainGenerator();
}

void World::draw(){
  mWindow->draw(mTerrain);
  mWindow->draw(mText);
  auto iter = mBunkerIterator->begin();
  auto iter_fuel = mFuelIterator->begin();

  for (;iter != mBunkerIterator->end(); ++iter) {
    iter->draw();
  }
  for(;iter_fuel != mFuelIterator->end(); ++iter_fuel){
    iter_fuel->draw();
  }

}

bool World::checkBunkerCollision(std::vector<Bunker> bunkerVector, sf::FloatRect rect){
  for(auto x : bunkerVector){
    if(x.getRectangle().intersects(rect))
      return true;
  }
  return false;
}

bool World::checkFuelCollision(std::vector<Fuel> fuelVector, sf::FloatRect rect){
  for(auto x : fuelVector){
    if(x.getRectangle().intersects(rect))
      return true;
  }
  return false;
}

World::fuel_iterator& World::getFuelIterator(){
  return mFuelIterator;
}

World::bunker_iterator& World::getBunkerIterator(){
  return mBunkerIterator;
}

std::vector<std::vector<Bunker>> World::getBunkerMatrix(){
  return mBunkerMatrix;
}

World::voxel* World::getVoxel(){
  return vx;
}
