#ifndef PROJECTILE_HANDLER_HPP
#define PROJECTILE_HANDLER_HPP

#include <Projectile.hpp>
#include <vector>
class ProjectileHandler{
public:
  ProjectileHandler(sf::RenderWindow& mWindow);
  void addProjectile(Projectile& projectile);
  std::vector<Projectile>* getProjectileVector();
  void updateVector(sf::Time elapsedTime);
  void draw();

private:
  void removeFromVector();

private:
  std::vector<Projectile> mProjectileVector;
  sf::RenderWindow* mWindow;

};
#endif //PROJECTILE_HANDLER_HPP
