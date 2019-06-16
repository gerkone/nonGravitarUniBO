#include <ResourceHolder.hpp>
#include <cmath>

ResourceHolder::ResourceHolder(){
  if(!mBackgroundTexture.loadFromFile("Media/Textures/Background.png"))
    throw std::runtime_error("Background Texture - failed to load");

  if(!mProjectileTexture.loadFromFile("Media/Textures/Bullet.png"))
    throw std::runtime_error("Bullet Texture - failed to load");

  if(!mBunkerTexture.loadFromFile("Media/Textures/cropped.png"))
    throw std::runtime_error("Bunker Texture - failed to load");

  if(!mFuelTexture.loadFromFile("Media/Textures/Fuel.png"))
    throw std::runtime_error("Fuel Texture - failed to load");

  if(!mTerrainTexture.loadFromFile("Media/Textures/Terrain.jpg"))
    throw std::runtime_error("Terrain Texture - failed to load");

  if(!mAircraftTexture.loadFromFile("Media/Textures/Eagle.png"))
    throw std::runtime_error("Aircraft Texture - failed to load");

  if(!mFont.loadFromFile("Media/Sansation.ttf"))
    throw std::runtime_error("Font - failed to load");

  if(!mGameOver.loadFromFile("Media/Textures/GameOver.png"))
    throw std::runtime_error("GameOver Texture - failed to load");

  if(!mPlanet1.loadFromFile("Media/Textures/planet1.png"))
    throw std::runtime_error("Planet1 Texture - failed to load");

  if(!mPlanet2.loadFromFile("Media/Textures/planet2.png"))
    throw std::runtime_error("Planet2 Texture - failed to load");

  if(!mPlanet3.loadFromFile("Media/Textures/planet3.png"))
    throw std::runtime_error("Planet3 Texture - failed to load");

  if(!mPlanet4.loadFromFile("Media/Textures/planet4.png"))
    throw std::runtime_error("Planet4 Texture - failed to load");

  if(!mPlanet5.loadFromFile("Media/Textures/planet5.png"))
    throw std::runtime_error("Planet5 Texture - failed to load");

  if(!mPlanet6.loadFromFile("Media/Textures/planet6.png"))
    throw std::runtime_error("Planet6 Texture - failed to load");
}

sf::Texture& ResourceHolder::getTerrainTexture(){
  return mTerrainTexture;
}

sf::Texture& ResourceHolder::getBunkerTexture(){
  return mBunkerTexture;
}

sf::Texture& ResourceHolder::getBackgroundTexture(){
  return mBackgroundTexture;
}

sf::Texture& ResourceHolder::getProjectileTexture(){
  return mProjectileTexture;
}

sf::Texture& ResourceHolder::getFuelTexture(){
  return mFuelTexture;
}

sf::Texture& ResourceHolder::getAircraftTexture(){
  return mAircraftTexture;
}

sf::Texture& ResourceHolder::getGameOver(){
  return mGameOver;
}

sf::Font& ResourceHolder::getFont(){
  return mFont;
}

sf::Texture& ResourceHolder::getRandomPlanetTexture(){

  int random = rand() % 6;
  switch (random) {
    case 0:
      return mPlanet1;
      break;
    case 1:
      return mPlanet2;
      break;
    case 2:
      return mPlanet3;
      break;
    case 3:
      return mPlanet4;
      break;
    case 4:
      return mPlanet5;
      break;
    case 5:
      return mPlanet6;
      break;
  }
}
