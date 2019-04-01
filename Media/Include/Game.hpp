#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <World.hpp>

class Game : private sf::NonCopyable
{
  public:
    Game();
    void run();

  private:
    void proccessEvents();
    void update(sf::Time elapsedTime);
    void render();
    void updateStatistics(sf::Time elapsedTime);
    void handlePlayerInput(sf::Keyboard::Key key, bool ispressed);
    void addPlanet(float x, float y);
    void spawnPlanet();
    void randomPlanetSpawn();
    bool checkPlanetsCollision(float x, float y);
    bool collisionAircraft(sf::FloatRect rect);

  private:

    typedef std::unique_ptr<World> Ptr;

    static const float PlayerSpeed;
    static const sf::Time TimePerFrame;
    static const float BorderDistance;
    static const float RadiusDistance;

    sf::RenderWindow mWindow;
    sf::Texture mTexture;
    sf::Sprite mPlayer;
    sf::Font mFont;
    sf::Text mStatisticsText;
    sf::Time mStatisticsUpdateTime;
    std::size_t mStatisticsNumFrames;
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingRight;
    bool mIsMovingLeft;
    std::vector<Ptr> mPlanetVector;

};
#endif //GAME_HPP
