#include <Game.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <sstream>
#include <cassert>

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);
const float Game::BorderDistance = 50.f;
const float Game::RadiusDistance = 50.f;
const int Game::VIDEO_WIDTH = 1280;
const int Game::VIDEO_HEIGHT = 720;
const int Game::MaxPlanet = 10;

Game::Game()
: mWindow(sf::VideoMode(VIDEO_WIDTH,VIDEO_HEIGHT), "NonGravitar", sf::Style::Close)
, mResourceHolder()
, mStatisticsText()
, mStatisticsNumFrames(0)
, mStatisticsUpdateTime()
, mPlanetVector()
, mState(gameState::universe)
, mCurrentPlanet(nullptr)
, mProjectileHandler(mWindow)
, mPlayer(mWindow, mProjectileHandler, mResourceHolder)
, mScoreText()
, mScore(0)

{
    srand(time(NULL));

    sf::Vector2u TextureSize;
    sf::Vector2u WindowSize;
    sf::Texture background = mResourceHolder.getBackgroundTexture();
    TextureSize = background.getSize();
    WindowSize = mWindow.getSize();
    float scaleX = (float) WindowSize.x / TextureSize.x;
    float scaleY = (float) WindowSize.y / TextureSize.y;
    mBackground.setTexture(mResourceHolder.getBackgroundTexture());
    mBackground.setScale(scaleX, scaleY);

    sf::Texture gameOver = mResourceHolder.getGameOver();
    TextureSize = gameOver.getSize();
    scaleX = (float) WindowSize.x / TextureSize.x;
    scaleY = (float) WindowSize.y / TextureSize.y;
    mGameOver.setTexture(mResourceHolder.getGameOver());
    mGameOver.setScale(scaleX, scaleY);

    mStatisticsText.setFont(mResourceHolder.getFont());
    mStatisticsText.setPosition(5.f, 5.f);
    mStatisticsText.setCharacterSize(10);

    randomPlanetSpawn();

}

void Game::run()
{
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  while(mWindow.isOpen())
  {
    sf::Time elapsedTime = clock.restart();//return the elapsed time since the last start
    timeSinceLastUpdate += elapsedTime;
    //check to ensure that events and update are called once every TimePerFrame
    while(timeSinceLastUpdate > TimePerFrame)
    {
      timeSinceLastUpdate -= TimePerFrame;

      proccessEvents();
      update(TimePerFrame);
    }

    updateStatistics(elapsedTime);
    render();

  }
}

void Game::proccessEvents()
{
  sf::Event event;
  while(mWindow.pollEvent(event))
  {
    switch(event.type)
    {
      case sf::Event::KeyPressed:
        mPlayer.handlePlayerInput(event.key.code, true);
        break;
      case sf::Event::KeyReleased:
        mPlayer.handlePlayerInput(event.key.code, false);
        break;
      case sf::Event::Closed:
        mWindow.close();
        break;
    }
  }
}

void Game::update(sf::Time elapsedTime)
{

  if(mState == gameState::universe){
    updateGameInfo();
    checkGameOver();
    mPlayer.update();
    mPlayer.move(elapsedTime);
    adaptPlayerPosition();
    for(auto iter = mPlanetVector.begin(); iter != mPlanetVector.end(); ++iter){
      auto ptr = iter->get();
      if(collisionAircraft(ptr->getCircle().getGlobalBounds())){
        mState = gameState::inWorld;
        mCurrentPlanet = ptr;
        mPlanetIterator = iter;
        mCurrentPlanet->terrainGenerator();
        mPlayer.setPosition(mWindow.getSize().x/2, 100);
        mPlayer.setRotation(180.f);
      }
    }
  }
  else if(mState == gameState::inWorld){
    updateGameInfo();
    checkFuelPickup();
    BunkerShot();
    checkBulletCollision();
    destroyBunker();
    checkAircraftTerrainCollision();
    changeWorldView();//all access to mCurrentPlanet have to be done before calling changeWorldView()
    mPlayer.update();
    mPlayer.move(elapsedTime);
    mPlayer.updateBeam();
    mPlayer.shoot();
    mProjectileHandler.updateVector(elapsedTime);
    checkGameOver();

  }

}

void Game::render()
{
  mWindow.clear();

  if (mState == gameState::universe){
  //unique_ptr can't be copied only way to iterate is with reference
    mWindow.draw(mBackground);
    mPlayer.draw();
    mWindow.draw(mStatisticsText);
    mWindow.draw(mFuelInfo);
    mWindow.draw(mScoreText);
    for(auto& x : mPlanetVector){
      mWindow.draw(x->getCircle());
    }
  }
  else if (mState == gameState::inWorld){
    mWindow.draw(mBackground);
    mPlayer.draw();
    mWindow.draw(mStatisticsText);
    mWindow.draw(mFuelInfo);
    mWindow.draw(mScoreText);
    mCurrentPlanet->draw();
    mProjectileHandler.draw();
    //mCurrentPlanet->debugging();
  }
  else if(mState == gameState::gameOver){
    mWindow.draw(mGameOver);
    mWindow.draw(mScoreText);
  }
  mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
  mStatisticsUpdateTime += elapsedTime;
  mStatisticsNumFrames += 1;

  if(mStatisticsUpdateTime >= sf::seconds(1.0f))
  {
    mStatisticsText.setString(
      "Frames / Second = " + std::to_string(mStatisticsNumFrames) + "\n" );

    mStatisticsUpdateTime -= sf::seconds(1.f);
    mStatisticsNumFrames = 0;

  }

}

void Game::randomPlanetSpawn()
{
  int i = (rand() % (MaxPlanet - 3)) + 3; //spawn atleast one planet
  int k = 0;
  sf::CircleShape circle;
  while(k < i){//while i haven't spawned all the planets
    float x = rand() % (mWindow.getSize().x);
    float y = rand() % (mWindow.getSize().y);
    x = std::max(x, BorderDistance);
    x = std::min(x, mWindow.getSize().x - BorderDistance);
    y = std::max(y, BorderDistance);
    y = std::min(y, mWindow.getSize().y - BorderDistance);
    //check for collision
    circle.setRadius(20);
    circle.setPosition(x,y);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    sf::FloatRect rect = circle.getGlobalBounds();
    bool check = checkPlanetsCollision(circle) || collisionAircraft(rect);
    if(!check){
      Ptr world(new World(x,y, mWindow, mProjectileHandler, mResourceHolder));
      mPlanetVector.push_back(std::move(world));
      k++;
    }
  }
}

bool Game::checkPlanetsCollision(sf::CircleShape shape){

  for(auto& planet : mPlanetVector){
    sf::Vector2f planet_global_coordinates = planet->getCircle().getPosition() + planet->getCircle().getOrigin();
    sf::Vector2f shape_global_coordinates = shape.getPosition() + shape.getOrigin();
    float a_square = pow(planet_global_coordinates.x - shape_global_coordinates.x, 2);
    float b_square = pow(planet_global_coordinates.y - shape_global_coordinates.y, 2);
    if(sqrt(a_square + b_square) <= shape.getRadius()*2 + RadiusDistance)
      return true;
  }

  return false;

}

bool Game::collisionAircraft(sf::FloatRect rect){
  sf::FloatRect aircraftRect = mPlayer.getGlobalBounds();
  if(aircraftRect.intersects(rect))
    return true;
  else
    return false;
}

void Game::adaptPlayerPosition(){
  const float distance = 10.f;
  sf::Vector2f position = mPlayer.getPosition();
  float width = mPlayer.getLocalBounds().width;
  float height = mPlayer.getLocalBounds().height;
  auto view = mWindow.getSize();
  position.x = std::max(position.x - width/2, distance);
  position.x = std::min(position.x + width/2, view.x - distance - width/2);
  position.y = std::max(position.y - height/2, distance);
  position.y = std::min(position.y + height/2, view.y - distance - height/2);
  mPlayer.setPosition(position.x, position.y);
}

void Game::changeWorldView(){
  sf::Vector2f position = mPlayer.getPosition();
  float width = mPlayer.getLocalBounds().width;
  float height = mPlayer.getLocalBounds().height;
  auto view = mWindow.getSize();
  if(position.x > view.x){//right border
    mPlayer.setPosition(0, position.y);
    mCurrentPlanet->nextView();
  }
  else if(position.x < 0){//left border
    mPlayer.setPosition(view.x, position.y);
    mCurrentPlanet->preView();
  }
  else if(position.y - height/2 < 0){
    mState = gameState::universe;
    mPlayer.setRotation(0);
    mPlayer.setPosition(mCurrentPlanet->getCircle().getPosition().x - 100, mCurrentPlanet->getCircle().getPosition().y - 100);
    bool destroy = checkPlanetDistruction();
    if(destroy){
      mScore += 1000;
      auto iter = mPlanetVector.erase(mPlanetIterator);
      bool check = checkAllPlanetDestruction();
      if(check)
        randomPlanetSpawn();
    }
    mCurrentPlanet = nullptr;

  }
}

void Game::checkFuelPickup(){
  sf::FloatRect beam = mPlayer.getBeam();
  auto iter = mCurrentPlanet->getFuelIterator();
  for (auto it = iter->begin(); it != iter->end(); ++it){
    if(beam.intersects(it->getRectangle())){
      mPlayer.updateFuel(it->getFuel());
      it = iter->erase(it);
      break;
    }
  }
}

void Game::checkBulletCollision(){
  auto bunkerIt = mCurrentPlanet->getBunkerIterator();
  auto bulletVector = mProjectileHandler.getProjectileVector();
  for(auto bullet = bulletVector->begin(); bullet != bulletVector->end();){
    Projectile::Type type = bullet->getType();
    bool collision = false;
    if(type == Projectile::Type::Allied){
      for(auto bunker = bunkerIt->begin(); bunker != bunkerIt->end(); ++bunker){
        if(bunker->getRectangle().intersects(bullet->getRectangle())){
          collision = true;
          bunker->hit();
          break;
        }
      }
      if(collision)
        bullet = bulletVector->erase(bullet);
      else
        ++bullet;
    }
    else{//bunker bullet
      if(mPlayer.getGlobalBounds().intersects(bullet->getRectangle())){
        bullet = bulletVector->erase(bullet);
        mPlayer.hit();
      }
      else
        ++bullet;
    }
  }
}

void Game::destroyBunker(){
  auto bunkerIt = mCurrentPlanet->getBunkerIterator();
  for(auto bunker = bunkerIt->begin(); bunker != bunkerIt->end();){
    int hitPoints = bunker->getHitpoints();
    if(hitPoints <= 0){
      mScore += bunker->getPoints();
      bunker = bunkerIt->erase(bunker);
    }
    else
      ++bunker;
  }
}

void Game::BunkerShot(){
  auto bunkerIt = mCurrentPlanet->getBunkerIterator();
  for(auto bunker = bunkerIt->begin(); bunker != bunkerIt->end(); ++bunker){
    bunker->shoot();
  }
}

void Game::checkGameOver(){
  int life = mPlayer.getLife();
  if(life <= 0 || mPlayer.getFuel() <= 0){
    mState = gameState::gameOver;
    mScoreText.setString(
      "FINAL SCORE = " + std::to_string(mScore) );
    mScoreText.setCharacterSize(60.f);
    sf::FloatRect size = mScoreText.getLocalBounds();
    mScoreText.setPosition(mWindow.getSize().x /2 - size.width/2, mWindow.getSize().y / 2);
  }
}

void Game::updateGameInfo(){

  //fuel info
  std::stringstream stream;
  stream << std::fixed << std::setprecision(2) << mPlayer.getFuel();
  std::string s = stream.str();
  mFuelInfo.setString(
    "Fuel = " + s );

  mFuelInfo.setFont(mResourceHolder.getFont());
  mFuelInfo.setPosition(5.f, 55.f);
  mFuelInfo.setCharacterSize(10.f);

  //score
  mScoreText.setString(
    "Score = " + std::to_string(mScore) );

  mScoreText.setFont(mResourceHolder.getFont());
  mScoreText.setPosition(5.f, 80.f);
  mScoreText.setCharacterSize(10.f);

}

bool Game::checkPlanetDistruction(){
  auto matrix = mCurrentPlanet->getBunkerMatrix();
  bool destroy = true;
  for(auto iter = matrix.begin(); iter != matrix.end(); ++iter){
    int size = iter->size();
    if(size > 0){
      destroy = false;
      break;
    }
  }
  return destroy;
}

bool Game::checkAllPlanetDestruction(){
  if(mPlanetVector.size() == 0)
    return true;
  else
  return false;
}

void Game::checkAircraftTerrainCollision(){
    auto vx = mCurrentPlanet->getVoxel();
    sf::Vector2f position = mPlayer.getCenter();
    position.x = mPlayer.getPosition().x;
    position.y += mPlayer.getPosition().y;

    for(int i = 1; i < World::SEGMENT_LIMIT - 2; ++i){
      if(vx[i-1].x < position.x && position.x < vx[i].x && position.x >= 0){
        float y1 = mWindow.getSize().y - vx[i-1].y;
        float y2 = mWindow.getSize().y - vx[i].y;
        float y = y2 - y1;
        float x = vx[i].x - vx[i-1].x;
        float coefficient = y / x;
        float q = -(y2-y1)*vx[i-1].x/(vx[i].x - vx[i-1].x) + y1;
        float absolute = coefficient * position.x + q;
        if(absolute <= position.y){
          mPlayer.setPosition(mWindow.getSize().x/2, 100.f);
          mPlayer.hit();
        }
        break;
      }
    }
}
