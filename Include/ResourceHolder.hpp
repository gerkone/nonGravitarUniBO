#ifndef RESOURCE_HOLDER
#define RESOURCE_HOLDER

#include <SFML/Graphics.hpp>

class ResourceHolder{
public:
  ResourceHolder();
  sf::Texture& getAircraftTexture();
  sf::Texture& getBackgroundTexture();
  sf::Texture& getProjectileTexture();
  sf::Texture& getBunkerTexture();
  sf::Texture& getTerrainTexture();
  sf::Texture& getFuelTexture();
  sf::Texture& getGameOver();
  sf::Font& getFont();
  sf::Texture& getRandomPlanetTexture();
  sf::Texture& getIntroTexture();

private:
  sf::Texture mAircraftTexture;
  sf::Texture mBackgroundTexture;
  sf::Texture mProjectileTexture;
  sf::Texture mBunkerTexture;
  sf::Texture mFuelTexture;
  sf::Texture mTerrainTexture;
  sf::Texture mGameOver;
  sf::Texture mPlanet1;
  sf::Texture mPlanet2;
  sf::Texture mPlanet3;
  sf::Texture mPlanet4;
  sf::Texture mPlanet5;
  sf::Texture mPlanet6;
  sf::Texture mIntro;
  sf::Font mFont;
};
#endif
