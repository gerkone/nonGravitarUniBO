#include <World.hpp>

World::World(float x, float y){
  mPlanet.setRadius(20);
  mPlanet.setOutlineColor(sf::Color::Red);
  mPlanet.setOutlineThickness(5);
  mPlanet.setPosition(x,y);

  srand(time(0));
  views = rand()%(MAX_VIEWS - MIN_VIEWS) + MIN_VIEWS; //inizializzazione terreno
  vx = new sf::Vector2f[SEGMENT_LIMIT];
  seeds = new int[views];
  for(int c = 0; c < views; c++)
  {
      seeds[c] = rand()%1337;
  }
  for(int c = 0; c < SEGMENT_LIMIT; c++) {
    vx[c] = ((float) ((SCREEN_WIDTH/SEGMENT_LIMIT) * c), (float) 0);
  }

  nFuel = rand()%MAX_FUEL;    //inizializzazione fuel array
  supply = new Fuel[nFuel];
  for(int i = 0; i< nFuel; i++) {
    supply[i] = Fuel(rand()%SCREEN_WIDTH, 0, rand()%views);
  }
}

sf::CircleShape World::getCircle(){
  return mPlanet;
}

int world::getNFuel() {
  return nFuel;
}

list<Fuel> World::getSupply() {
  list<Fuel> ret;
  for(int i = 0; i < nFuel; i++) {
    if (supply[i].isActive()) {
      ret.push_back(supply[i]);
    }
  }
  return ret;
}

void World::nextView() {
  itV = (itV + 1) % views;
}


void World::prevView() {
  itV = (itV - 1) % views;
}

sf::Vector2f* World::getTerrain() {
  // try {
    srand(seeds[itV]);
    terrainGen();
    return vx;
  // } catch {
  //
  // }
}

void World::terrainGen(int start = 0, int end = SEGMENT_LIMIT, double displ = DISPLACEMENT) {
  if(start + 1 >= end) {}
  else
  {
      int mid = (end + start) / 2;
      double rnd = ((double) rand()/(RAND_MAX)) - 0.5;
      float offset = displ * rnd;
      vx[mid].y = (vx[start].y + vx[end].y)/2 + offset;
      displ = VARIANCE * displ; // displacement scalato del fattore variance
      terrainGen(vx, start, mid, displ); // reiterazione sui lati sx e dx del segmento
      terrainGen(vx, mid, end, displ);
  }
}

float World::getHeight(int x) {
  if ((vx == nullptr) || (x > SCREEN_WIDTH) || (x < 0)) {
    return 0;
  } else {
    float retY = 0;
    while((i < SEGMENT_LIMIT) && (retY == 0)){
      if((vx[i].x > x - 10) && (vx[i].x < x + 10)) {  //vx[i] e' contenuto in un range accettabile di pixel
        retY = vx[i].y;
      }
      i++;
    }
    return retY;
  }
}
