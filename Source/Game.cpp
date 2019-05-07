#include <Game.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);
const float Game::BorderDistance = 50.f;
const float Game::RadiusDistance = 50.f;
const int Game::VIDEO_WIDTH = 1280;
const int Game::VIDEO_HEIGHT = 720;
const int Game::MaxPlanet = 10;

Game::Game()
: mWindow(sf::VideoMode(VIDEO_WIDTH,VIDEO_HEIGHT), "NonGravitar", sf::Style::Close)
, mFont()
, mStatisticsText()
, mStatisticsNumFrames(0)
, mStatisticsUpdateTime()
, mPlanetVector()
, mState(gameState::universe)
, mCurrentPlanet(nullptr)
, mPlayer("Media/Textures/Eagle.png", mWindow)
{
    srand(time(NULL));

    mFont.loadFromFile("Media/Sansation.ttf");
    mStatisticsText.setFont(mFont);
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

  mPlayer.update(elapsedTime);

  if(mState == gameState::universe){
    mPlayer.move(elapsedTime);
    adaptPlayerPosition();
    for(auto& x : mPlanetVector){
      if(collisionAircraft(x->getCircle().getGlobalBounds())){
        mState = gameState::inWorld;
        mCurrentPlanet = x.get();
        mCurrentPlanet->terrainGenerator();
        mCurrentPlanet->itemsGenerator();
        mPlayer.setPosition(mWindow.getSize().x/2, 100);
        mPlayer.setRotation(180.f);
      }
    }
  }
  if(mState == gameState::inWorld){
    changeWorldView();
    mPlayer.move(elapsedTime);
    mPlayer.updateBeam();
    if(mCurrentPlanet != nullptr) {
      std::list<sf::RectangleShape> tmpFuels = mCurrentPlanet->getFuels();
      for(std::list<sf::RectangleShape>::iterator f = tmpFuels.begin(); f != tmpFuels.end(); f++) {
        if(tractorFuel(f->getGlobalBounds())) {
          mCurrentPlanet->getFuelAt(f->getPosition().x);  //returns the value of the fuel and deactivates it //TODO: ritornerebbe quantita' fuel, da sommare al totale
        }
      }
    }
  }

}

void Game::render()
{
  mWindow.clear();
  mPlayer.draw();
  mWindow.draw(mStatisticsText);
  if (mState == gameState::universe){
  //unique_ptr can't be copied only way to iterate is with reference
    for(auto& x : mPlanetVector){
      mWindow.draw(x->getCircle());
    }
  }
  else{
    mWindow.draw(mCurrentPlanet->getTerrain());
    std::list<sf::CircleShape> bunkers = mCurrentPlanet->getBunkers();
    std::list<sf::CircleShape>::iterator bit;
    for(bit = bunkers.begin(); bit != bunkers.end(); bit++) {
      mWindow.draw(*bit);
    }
    std::list<sf::RectangleShape> fuels = mCurrentPlanet->getFuels();
    std::list<sf::RectangleShape>::iterator fit;
    for(fit = fuels.begin(); fit != fuels.end(); fit++) {
      mWindow.draw(*fit);
    }

    //mCurrentPlanet->debugging();
  }
  mWindow.display();
}

void Game::updateStatistics(sf::Time elapsedTime)
{
  mStatisticsUpdateTime += elapsedTime;
  mStatisticsNumFrames += 1;

  if(mStatisticsUpdateTime >= sf::seconds(1.0f))
  {
    std::string str = "";
    if(mCurrentPlanet != nullptr) {     //avoids that we access to a null object while in the universe
      str = "view: " + std::to_string(mCurrentPlanet->getView()) + "\n";
      str += "bunkers(real/drawn): " + std::to_string(mCurrentPlanet->nBunkers()) + "/" + std::to_string(mCurrentPlanet->getBunkers().size()) + "\n";
      str += "fuels(real/drawn): " + std::to_string(mCurrentPlanet->nFuels()) + "/"  + std::to_string(mCurrentPlanet->getFuels().size()) + "\n";
    }
    mStatisticsText.setString(
      "Frames / Second = " + std::to_string(mStatisticsNumFrames) + "\n" + str);

    mStatisticsUpdateTime -= sf::seconds(1.f);
    mStatisticsNumFrames = 0;

  }
}

void Game::randomPlanetSpawn()
{
  int i = rand() % MaxPlanet + 1; //spawn atleast one planet
  int k = 0;
  sf::CircleShape circle;
  while(k < i){
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
      Ptr world(new World(x,y, mWindow));
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

bool Game::tractorFuel(sf::FloatRect rect) {
  sf::FloatRect beamBounds = mPlayer.getBeamBounds();
  if(beamBounds.intersects(rect))
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
  position.x = std::max(position.x, distance);
  position.x = std::min(position.x, view.x - distance - width);
  position.y = std::max(position.y, distance);
  position.y = std::min(position.y, view.y - distance - height);
  mPlayer.setPosition(position.x, position.y);
}

void Game::changeWorldView(){
  sf::Vector2f position = mPlayer.getPosition();
  float width = mPlayer.getLocalBounds().width;
  float height = mPlayer.getLocalBounds().height;
  auto view = mWindow.getSize();
  if(position.x > view.x){//right border
    mPlayer.setPosition(width, position.y);
    mCurrentPlanet->nextView();
  }
  else if(position.x - width < 0){//left border
    mPlayer.setPosition(view.x, position.y);
    mCurrentPlanet->preView();
  }
  else if(position.y < 0){
    mState = gameState::universe;
    mPlayer.setRotation(0);
    mPlayer.setPosition(mCurrentPlanet->getCircle().getPosition().x - 100, mCurrentPlanet->getCircle().getPosition().y - 100);
    //mPlayer.setPosition(100.f, 100.f);
    mCurrentPlanet = nullptr;

  }
}
