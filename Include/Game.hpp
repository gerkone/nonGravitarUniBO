#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <World.hpp>

class Game : private sf::NonCopyable
{

  private:

    enum gameState {
      universe,
      inWorld
    };

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
    bool checkPlanetsCollision(sf::CircleShape shape);
    bool collisionAircraft(sf::FloatRect rect);

  private:

    typedef std::unique_ptr<World> Ptr;

    static const float PlayerSpeed;
    static const sf::Time TimePerFrame;
    static const float BorderDistance;//distance from the border of the planet
    static const float RadiusDistance;//minimum distance between the planet in the main game state universe
    static const int MaxPlanet;//max number of planet generated
    static const int VIDEO_WIDTH;
    static const int VIDEO_HEIGHT;

    sf::RenderWindow mWindow;//main window
    sf::Texture mTexture;//texture of the player
    sf::Sprite mPlayer;//player's sprite
    //used for statistics of the game
    sf::Font mFont;
    sf::Text mStatisticsText;
    sf::Time mStatisticsUpdateTime;
    std::size_t mStatisticsNumFrames;
    //used to moving the spaceship
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingRight;
    bool mIsMovingLeft;
    std::vector<Ptr> mPlanetVector;//holds ol the planet generated
    gameState mState;//the state of the game
    World* mCurrentPlanet;//the current planet where the player is playing

};
#endif //GAME_HPP
