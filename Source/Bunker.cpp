#include <Bunker.hpp>

Bunker::Bunker(float x, float y, int v) {
  mBunker.setRadius(BUNKER_RADIUS);
  mBunker.setPosition(x, y);
  active = true;
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

// int Bunker::getFireMode() {
//   return fireMode;
// }

bool Bunker::isActive() {
  return active;
}

int Bunker::hit(int hp) {
  hitpoints = hitpoints - hp;
  if(hitpoints > 0) {
    return 0;
  } else {
    active = false;
    return POINTS;
  }
}

int Bunker::getHitpoints() {
  return hitpoints;
}

int Bunker::getView() {
  return onView;
}
