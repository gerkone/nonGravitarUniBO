#include <Fire.hpp>

Fire::Fire(FireMode mode, float speed, float x, float y) {
  eFireMode = mode;
  switch (mode)
  {
    case Player: firingAngle = 270; fireStep = MIN_FIRESTEP; enemy = false; break;
    case Single: firingAngle = 90; fireStep = MIN_FIRESTEP; enemy = true; break;
    case Triple: firingAngle = 90; fireStep = MIN_FIRESTEP; enemy = true; break;
  }
  fx = x;
  fy = y;
}

void Fire::updateBullets() {
  std::list<Bullet>::iterator it = mBullets.begin();
  while(it != mBullets.end()) {
    if(it->hasHit()) {
      it = mBullets.erase(it);
    } else {
      it++;
    }
  }
}

void Fire::shoot() {
  if ((eFireMode == Player) || (eFireMode == Single)) {
    Bullet tmp = Bullet(fx, fy, firingAngle, enemy, fireStep/10);
    mBullets.push_back(tmp);
  } else if(eFireMode == Triple) {
    Bullet tmp1 = Bullet(fx, fy, firingAngle, enemy, fireStep/10);
    Bullet tmp2 = Bullet(fx, fy, firingAngle - TRIPLE_ANGLE_STEP, enemy, fireStep/10);  //aggiunti due mBullets inclinati
    Bullet tmp3 = Bullet(fx, fy, firingAngle + TRIPLE_ANGLE_STEP, enemy, fireStep/10);
    mBullets.push_back(tmp1);
    mBullets.push_back(tmp2);
    mBullets.push_back(tmp3);
  }
}

void Fire::setPosition(float x, float y) {
  fx = x;
  fy = y;
}

int Fire::getFireStep() {
  return fireStep;
}

void Fire::setFiringAngle(int angle) {
  firingAngle = angle;
}

int Fire::getFiringAngle() {
  return firingAngle;
}

std::list<sf::Vertex*> Fire::getBullets() {
  std::list<sf::Vertex  *> lines;
  std::list<Bullet>::iterator it;
  for(it = mBullets.begin();it != mBullets.end();it++) {
    lines.push_back(it->getLine());
  }
  return lines;
}

bool Fire::isEnemy() {
  return enemy;
}
