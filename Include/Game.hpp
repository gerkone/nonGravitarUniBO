#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <World.hpp>
#include <Player.hpp>
#include <ProjectileHandler.hpp>
#include <ResourceHolder.hpp>

class Game : private sf::NonCopyable
{

  private:

    enum gameState {
      universe,
      inWorld,
      gameOver
    };

  public:
    Game();
    void run();//run the game

  private:
    void proccessEvents();//handle the game events i.e player input
    void update(sf::Time elapsedTime);//update the object in the game
    void render();//draw all the object in the window
    void updateStatistics(sf::Time elapsedTime);//print on the window game statistics and player info
    void randomPlanetSpawn();//spawn all the planet
    bool checkPlanetsCollision(sf::CircleShape shape);//check collision between the planets on spawn
    bool collisionAircraft(sf::FloatRect rect);//collision rect with the aircraft
    void adaptPlayerPosition();//bound the aircraft in the window view
    void changeWorldView();//change the ingame view of the world, advance/decrease the iterator to the seed used to generate the terrain
    void checkFuelPickup();//check if the player is picking up some fuel
    void checkBulletCollision();//check if the bullets are hitting something
    void checkFuel();//check the player fuel
    void destroyBunker();
    void BunkerShot();
    void checkGameOver();
    void updateGameInfo();
    bool checkPlanetDistruction();//return true if all the bunker inside mCurrentPlanet are destroyed when leaving the planet
    bool checkAllPlanetDestruction();//return true if all the planet are destroyed
    void checkAircraftTerrainCollision();

  private:

    typedef std::unique_ptr<World> Ptr;

    static const sf::Time TimePerFrame;
    static const float BorderDistance;//distance from the border of the window of every planet
    static const float RadiusDistance;//minimum distance between the planet in the main game state universe
    static const int MaxPlanet;//max number of planet generated
    static const int VIDEO_WIDTH;
    static const int VIDEO_HEIGHT;

    sf::RenderWindow mWindow;//main window
    //used for statistics of the game
    sf::Text mStatisticsText;
    sf::Time mStatisticsUpdateTime;
    std::size_t mStatisticsNumFrames;
    //used to moving the spaceship
    std::vector<Ptr> mPlanetVector;//holds all the planet generated
    gameState mState;//the state of the game
    World* mCurrentPlanet;//the current planet where the player is playing
    std::vector<Ptr>::iterator mPlanetIterator;
    Player mPlayer;
    sf::Sprite mBackground;
    sf::Text mFuelInfo;
    ProjectileHandler mProjectileHandler;
    ResourceHolder mResourceHolder;
    int mScore;
    sf::Text mScoreText;
    sf::Sprite mGameOver;

};
#endif //GAME_HPP
