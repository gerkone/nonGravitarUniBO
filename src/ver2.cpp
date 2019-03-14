#include <list>
#include <iterator>
#include <time.h>
#include <iostream>
#include <math.h>

using namespace std;


const int SEGMENT_LIMIT = 4000; //segmenti massimi che comporranno il terreno
const int MAX_VIEWS = 5; //schermate massime

const int SCREEN_WIDTH = 440;
const int SCREEN_HEIGHT = 300;

const double VARIANCE = 0.95; //ruvidità di scalo tra displacement tra passaggi successivi
const double DISPLACEMENT = 300; // unità di spostamento (segs * displacement) in px rispetto al numero di segmenti


struct voxel {
  int x;
  int y;
};

void terrain_gen(voxel vx[], int start, int end, double displ, int max) {
  if(start >= end) {}
  else
  {
      int mid = (end + start) / 2;
      double rnd = ((double) rand()/(RAND_MAX)) - 0.5;
      vx[mid].y = SCREEN_HEIGHT + displ * rnd;
      displ = VARIANCE * displ; // displacement scalato del fattore variance
      terrain_gen(vx, start, mid, displ, max); // reiterazione sui lati sx e dx del segmento
      terrain_gen(vx, mid + 1, end, displ, max);
  }
}


int main() {
  srand(time(0));
  std::list <int> seeds;
  int views = rand()%MAX_VIEWS + 2;
  voxel vx[SEGMENT_LIMIT];
  for(int c = 0; c < views; c++)
  {
      seeds.push_back(rand());
  }
  for(int c = 0; c < SEGMENT_LIMIT; c++) {
    vx[c].x = SCREEN_WIDTH * ((double) ((1 + c)*10000/SEGMENT_LIMIT)/10000);
    vx[c].y = 0;
  }
  for(list<int> :: iterator it = seeds.begin(); it != seeds.end(); it++) {
    srand(*it);
    cout << "SEED:  "<< *it << "\n";
    terrain_gen(vx, 0, SEGMENT_LIMIT, DISPLACEMENT, SEGMENT_LIMIT);
    for(int c = 0; c < SEGMENT_LIMIT; c++) {
      cout << "x = " << vx[c].x << " | y = " << vx[c].y << "\n";
    }
  }
  return 0;
}
