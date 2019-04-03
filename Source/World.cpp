#include <World.hpp>

World::World(float x, float y){
  mPlanet.setRadius(20);
  mPlanet.setOutlineColor(sf::Color::Red);
  mPlanet.setOutlineThickness(5);
  mPlanet.setPosition(x,y);

  srand(time(0));
  views = rand()%(MAX_VIEWS - MIN_VIEWS) + MIN_VIEWS;
  vx = new sf::Vector2f[SEGMENT_LIMIT];
  seeds = new int[views];
  for(int c = 0; c < views; c++)
  {
      seeds[c] = rand()%1337;
  }
  for(int c = 0; c < SEGMENT_LIMIT; c++) {
    vx[c] = ((float) ((SCREEN_WIDTH/SEGMENT_LIMIT) * c), (float) 0);
  }
}

void nextView() {
  itV = (itV + 1) % views;
}


void prevView() {
  itV = (itV - 1) % views;
}

sf::Vector2f* getTerrain() {
  // try {
    srand(seeds[itV]);
    terrainGen();
    return vx;
  // } catch {
  //
  // }
}

void terrainGen(int start = 0, int end = SEGMENT_LIMIT, double displ = DISPLACEMENT) {
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


sf::CircleShape World::getCircle(){
  return mPlanet;
}
