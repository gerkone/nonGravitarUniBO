#include <Fire.hpp>

Fire::Fire(FireMode mode) {
  fireMode = mode;
  switch (mode)
  {
    case Player: firingAngle = 270; fireStep = MIN_FIRESTEP; isEnemy = false; break;
    case Vertical: firingAngle= 90; fireStep = 4*MIN_FIRESTEP; isEnemy = true; break;
    case Triple: firingAngle = 90; fireStep = 8*MIN_FIRESTEP; isEnemy = true; break;
  }
  fx = 0;
  fy = 0;
}

void updateBullets() {
  list<Bullet>::iterator it = bullets.begin();
  while(it != bullets.end()) {
    if(it.hasHit()) {
      it = bullets.erase(it);
    } else {
      it++;
    }
  }
}

void setPosition(float x, float y) {
  fx = x;
  fy = y;
}

int getFireStep() {
  return fireStep;
}

void setFiringAngle(int angle) {
  firingAngle = angle;
}

int getFiringAngle() {
  return firingAngle;
}

list<Bullet> Fire::getBullets() {
  return bullets;
}

bool Fire::isEnemy() {
  return isEnemy;
}
