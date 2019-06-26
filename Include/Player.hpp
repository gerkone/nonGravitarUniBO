#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <ProjectileHandler.hpp>
#include <Projectile.hpp>
#include <TextNode.hpp>
#include <ResourceHolder.hpp>

class Player {
  public:
    Player(sf::RenderWindow& Window, ProjectileHandler& handler, ResourceHolder& holder);
    void handlePlayerInput(sf::Keyboard::Key key, bool ispressed);
    void draw();//draw the sprite in the window,call to window.draw(sprite)
    void setPosition(float x, float y);
    sf::Vector2f getPosition();//get the player position
    sf::FloatRect getGlobalBounds();
    void move(sf::Time elapsedTime);//translate the aircraft
    void setRotation(float rotation);
    void update();//update the vector used to translate the aircraft
    sf::FloatRect getLocalBounds();
    void updateBeam();//update the fuel beam
    sf::Vector2f getCenter();//get the aircraft front position
    sf::FloatRect getBeam();//get the beam rect
    void updateFuel(float fuel);//update the fuel consumtion
    float getFuel();
    void shoot();//spawn a bullet
    void hit();//decrese lifepoints
    int getLife();

  private:
    sf::RenderWindow* mWindow;
    sf::Sprite mPlayer;
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;
    bool mBeamIsPressed;
    bool mIsShooting;
    sf::Vector2f mMovement;
    sf::RectangleShape mBeam;
    float mFuel;
    ProjectileHandler* mProjectileHandler;
    sf::Clock mClock;//used to limit the shooting function
    TextNode mText;
    int mLifePoints;
    sf::Texture mTexture;
    ResourceHolder* mResourceHolder;

  private:
    static const float PlayerSpeed;
    static const float BEAM_WIDTH;
    static const float BEAM_HEIGHT;
    static const float MAX_FUEL;
    static const float DECREASE_FUEL;
    static const sf::Time SHOOT_RATE;
    static const int LIFEPOINTS;
};

#endif//PLAYER_HPP
