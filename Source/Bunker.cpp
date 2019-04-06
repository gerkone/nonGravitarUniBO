#include <Bunker.hpp>

Bunker::Bunker(float x, float y, int v) {
  mBunker.setRadius(BUNKER_RADIUS);
  mBunker.setPosition(x, y);
  isActive = true;
  onView = v;

  srand(time(0));
  if(rand()%2 > 1) {
    // fireMode = Vertical;
    hitpoints = 500;
  } else {
    // fireMode = Triple;
    hitpoints = 300;
  }
}

sf::CircleShape Bunker::getCircle() {
  return mBunker;
}

int Bunker::getFireMode() {
  return fireMode;
}

bool Bunker::isActive() {
  return isActive;
}

int Bunker::hit(int hp) {
  hitpoi = hitpoints - hp;
  if(hitpoints > 0) {
    return 0;
  } else {
    isActive = false;
    return POINTS;
  }
}

int getHitpoints() {
  return hitpoints;
}
void Bunker::setY(float offY) {
  mBunker.move(o, offY - BUNKER_RADIUS);  //- Bunker_HEIGHT per mantenerlo al di sopra del terreno
}

int Bunker::getView() {
  return onView;
}
