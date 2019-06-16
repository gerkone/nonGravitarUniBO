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
    sf::FloatRect getRectangle();
    int getHitpoints();
    void hit();
    void draw();
    void shoot();
    sf::Vector2f getPosition();
    int getPoints();

  private:
    void createBullet(sf::Vector2f movement);

  private:
    sf::Sprite mBunker;
    sf::RenderWindow* mWindow;
    int mHitpoints; //quanti colpi riesce a sopportare il bunker
    sf::RectangleShape mHealth;
    sf::RectangleShape mHealthBorder;
    Type mType;
    ProjectileHandler* mProjectileHandler;
    sf::Clock mClock;
    ResourceHolder* mResourceHolder;

  private:
    static const int BUNKER_RADIUS;
    static const int POINTS;//punti ricevuti alla distruzione del bunker
    static const int LIFEPOINTS;
    static const sf::Time SHOOT_RATE;
};
#endif //BUNKER_HPP
