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

void Fire::move(sf::Time elapsedTime) {
  updateBullets();
  std::list<Bullet>::iterator it;
  for(it = mBullets.begin(); it != mBullets.end(); it++) {
    it->move(elapsedTime);
  }
}

void Fire::shoot(sf::Time elapsedTime) {
  if ((elapsedStep - elapsedTime.asMilliseconds()) < 0) {  // e passato abbastanza tempo per poter sparare dinuovo
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
  elapsedStep = (elapsedStep - elapsedTime.asMilliseconds())%fireStep;
  move(elapsedTime); // muove tutti i proiettili
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

std::list<sf::Sprite> Fire::getBullets() {
  std::list<sf::Sprite> bullets;
  std::list<Bullet>::iterator it;
  for(it = mBullets.begin(); it != mBullets.end();it++) {
    bullets.push_back(it->getBullet());
  }
  return bullets;
}

bool Fire::isEnemy() {
  return enemy;
}
