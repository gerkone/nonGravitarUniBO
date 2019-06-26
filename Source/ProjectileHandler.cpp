#include <ProjectileHandler.hpp>
#include <iostream>

ProjectileHandler::ProjectileHandler(sf::RenderWindow& window) : mWindow(&window), mProjectileVector(){

}

void ProjectileHandler::addProjectile(Projectile& projectile){
  mProjectileVector.push_back(projectile);
}

std::vector<Projectile>* ProjectileHandler::getProjectileVector(){
  return &mProjectileVector;
}

void ProjectileHandler::removeFromVector(){//delete the bullet if outside the window
  for (auto it = mProjectileVector.begin(); it!=mProjectileVector.end(); ) {
    if(it->getPosition().x < 0){
      it = mProjectileVector.erase(it);
    }
    else if(it->getPosition().x > mWindow->getSize().x){
      it = mProjectileVector.erase(it);
    }
    else if(it->getPosition().y > mWindow->getSize().y){
      // std::cout << "here" << std::endl;
      it = mProjectileVector.erase(it);
      // std::cout << "erased" << std::endl;
    }
    else if(it->getPosition().y < 0)
      it = mProjectileVector.erase(it);

    else
      ++it;
  }
}

void ProjectileHandler::updateVector(sf::Time elapsedTime){
  for(auto& x : mProjectileVector){
    x.move(elapsedTime);
  }
  removeFromVector();
}

void ProjectileHandler::draw(){
  for(auto& projectile : mProjectileVector){
    projectile.draw();
    // std::cout << "drawing Projectile" << std::endl;
  }
}
