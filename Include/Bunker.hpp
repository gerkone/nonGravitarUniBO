#ifndef BUNKER_HPP
#define BUNKER_HPP

#include <SFML/Graphics.hpp>
#include <ProjectileHandler.hpp>
#include <Projectile.hpp>
#include <ResourceHolder.hpp>

class Bunker{
  private:
    enum Type {
      Basic,
      Advanced
    };

  public:
    Bunker(sf::RenderWindow& window, ProjectileHandler& handler, ResourceHolder& holder, float x, float y);
    sf::FloatRect getRectangle();//get the rectangle around the bunker sprite
    int getHitpoints();//get the lifepoints of the bunker
    void hit();//lifepoints--
    void draw();//draw he bunker in the window passed in the constructor
    void shoot();//spawn projectile
    sf::Vector2f getPosition();//get the position of the top center of the bunker
    int getPoints();//use when a bunker is destroyed, return a score

  private:
    void createBullet(sf::Vector2f movement);//push a bullet in the projectile vector

  private:
    sf::Sprite mBunker;
    sf::RenderWindow* mWindow;//where to draw the sprite
    int mHitpoints; //quanti colpi riesce a sopportare il bunker
    //health below the bunker
    sf::RectangleShape mHealth;
    sf::RectangleShape mHealthBorder;
    Type mType;//type of the bunker
    ProjectileHandler* mProjectileHandler;
    sf::Clock mClock;
    ResourceHolder* mResourceHolder;

  private:
    static const int POINTS;//punti ricevuti alla distruzione del bunker
    static const int LIFEPOINTS;
    static const sf::Time SHOOT_RATE;
};
#endif //BUNKER_HPP
