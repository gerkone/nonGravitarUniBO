#include <Game.hpp>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <cmath>

const float Game::PlayerSpeed = 100.f;
const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);
const float Game::BorderDistance = 50.f;
const float Game::RadiusDistance = 50.f;

Game::Game()
: mWindow(sf::VideoMode(1280,720), "NonGravitar", sf::Style::Close)
, mTexture()
, mPlayer()
, mFont()
, mStatisticsText()
, mStatisticsNumFrames(0)
, mStatisticsUpdateTime()
, mIsMovingUp(false)
, mIsMovingDown(false)
, mIsMovingLeft(false)
, mIsMovingRight(false)
, mPlanetVector()
 {
    if(!mTexture.loadFromFile("Media/Textures/Eagle.png")){
      mWindow.close();
    }
    srand(time(NULL));
    mPlayer.setTexture(mTexture);
    mPlayer.setPosition(100.f, 100.f);

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
        handlePlayerInput(event.key.code, true);
        break;
      case sf::Event::KeyReleased:
        handlePlayerInput(event.key.code, false);
        break;
      case sf::Event::Closed:
        mWindow.close();
        break;
    }
  }
}

void Game::update(sf::Time elapsedTime)
{
  sf::Vector2f movement(0.f, 0.f);
  if(mIsMovingUp)
    movement.y -= PlayerSpeed;
  if(mIsMovingDown)
    movement.y += PlayerSpeed;
  if(mIsMovingLeft)
    movement.x -= PlayerSpeed;
  if(mIsMovingRight)
    movement.x += PlayerSpeed;
  for(auto& x : mPlanetVector){
    if(collisionAircraft(x->getCircle().getGlobalBounds()))
      std::cout << "collision detected";
  }

  mPlayer.move(movement * elapsedTime.asSeconds());
}

void Game::render()
{
  mWindow.clear();
  mWindow.draw(mPlayer);
  mWindow.draw(mStatisticsText);
  //unique_ptr can't be copied only way to iterate is with reference
  for(auto& x : mPlanetVector){
    mWindow.draw(x->getCircle());
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

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{

  if (key == sf::Keyboard::W)
    mIsMovingUp = isPressed;
  else if(key == sf::Keyboard::S)
    mIsMovingDown = isPressed;
  else if(key == sf::Keyboard::A)
    mIsMovingLeft = isPressed;
  else if(key == sf::Keyboard::D)
    mIsMovingRight = isPressed;
}

void Game::randomPlanetSpawn()
{
  int i = rand() % 10 +1;
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
    sf::FloatRect rect = circle.getGlobalBounds();
    bool check = checkPlanetsCollision(x, y) || collisionAircraft(rect);
    if(!check){
      Ptr world(new World(x,y));
      mPlanetVector.push_back(std::move(world));
      k++;
    }
    std::cout << k;
  }
}

bool Game::checkPlanetsCollision(float x, float y){
  for(auto& planet : mPlanetVector){
    float a_square = pow(planet->getCircle().getPosition().x - x, 2);
    float b_square = pow(planet->getCircle().getPosition().y - y, 2);
    if(sqrt(a_square + b_square) <= (planet->getCircle().getRadius()*2+RadiusDistance))
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
