#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <string>

const float BEAM_WIDTH = 10.f;
const float BEAM_HEIGHT = 50.f;

class Player {
  public:
    Player(std::string texturePath, sf::RenderWindow& Window);//percorso texture, finestra su cui disegnare lo sprite
    void handlePlayerInput(sf::Keyboard::Key key, bool ispressed);
    void draw();//draw the sprite in the window,call to window.draw(sprite)
    bool getIsMovingUp();
    bool getIsMovingDown();
    bool getIsMovingLeft();
    bool getIsMovingRight();
    bool getTractor();
    sf::RectangleShape getBeam();
    void setPosition(float x, float y);
    sf::Vector2f getPosition();
    sf::FloatRect getGlobalBounds();
    void move(sf::Time elapsedTime);//translate the aircrafr
    void setRotation(float rotation);
    void update(sf::Time elapsedTime);//update the vector used to translate the aircraft
    sf::FloatRect getLocalBounds();
    sf::FloatRect getBeamBounds();
    void updateBeam();  //sets the beam, separate as it must be called only on the planet

  private:
    sf::RenderWindow& mWindow;
    sf::Texture mTexture;
    sf::Sprite mPlayer;
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;
    sf::Vector2f mMovement;
    sf::RectangleShape mBeam; //the sprite of the tractor beam
    bool mTractor;  //true if the beam is on

  private:
    static const float PlayerSpeed;
    static const float BEAM_WIDTH;
    static const float BEAM_HEIGHT;
};

#endif//PLAYER_HPP
