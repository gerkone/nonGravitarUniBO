#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Player {
  public:
    Player(std::string texturePath, sf::RenderWindow& Window);//percorso texture, finestra su cui disegnare lo sprite
    void handlePlayerInput(sf::Keyboard::Key key, bool ispressed);
    void draw();//draw the sprite in the window,call to window.draw(sprite)
    bool getIsMovingUp();
    bool getIsMovingDown();
    bool getIsMovingLeft();
    bool getIsMovingRight();
    void setPosition(float x, float y);
    sf::Vector2f getPosition();
    sf::FloatRect getGlobalBounds();
    void move(sf::Time elapsedTime);//translate the aircrafr
    void rotate(float rotation);
    void update(sf::Time elapsedTime);//update the vector used to translate the aircraft

  private:
    sf::RenderWindow& mWindow;
    sf::Texture mTexture;
    sf::Sprite mPlayer;
    bool mIsMovingUp;
    bool mIsMovingDown;
    bool mIsMovingLeft;
    bool mIsMovingRight;
    sf::Vector2f mMovement;

  private:
    static const float PlayerSpeed;
};

#endif//PLAYER_HPP
