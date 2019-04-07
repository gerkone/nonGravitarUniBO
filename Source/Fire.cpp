#include <Fire.hpp>

Fire::Fire(FireMode mode, float speed, float x, float y) {
  fireMode = mode;
  switch (mode)
  {
    case Player: firingAngle = 270; fireStep = MIN_FIRESTEP; isEnemy = false; break;
    case Single: firingAngle = 90; fireStep = MIN_FIRESTEP; isEnemy = true; break;
    case Triple: firingAngle = 90; fireStep = MIN_FIRESTEP; isEnemy = true; break;
  }
  fx = x;
  fy = y;
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

void shoot() {
  if ((fireMode == Player) || (fireMode == Single)) {
    Bullet tmp = Bullet(fx, fy, firingAngle, isEnemy, fireStep/10);
    bullets.push_back(tmp);
  } else if(fireMode == Triple) {
    Bullet tmp1 = Bullet(fx, fy, firingAngle, isEnemy, fireStep/10);
    Bullet tmp2 = Bullet(fx, fy, firingAngle - TRIPLE_ANGLE_STEP, isEnemy, fireStep/10);  //aggiunti due bullets inclinati
    Bullet tmp3 = Bullet(fx, fy, firingAngle + TRIPLE_ANGLE_STEP, isEnemy, fireStep/10);
    bullets.push_back(tmp1);
    bullets.push_back(tmp2);
    bullets.push_back(tmp3);
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
