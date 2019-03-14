#include <list>
#include <iterator>
#include <time.h>
#include <iostream>
#include <math.h>

using namespace std;


const int SEGMENT_LIMIT = 4000; //segmenti massimi che comporranno il terreno
const int MAX_VIEWS = 5; //schermate massime
const int MIN_VIEWS = 2;

const int SCREEN_WIDTH = 440;
const int SCREEN_HEIGHT = 300;

const double VARIANCE = 0.95; //ruvidità di scalo tra displacement tra passaggi successivi
const double DISPLACEMENT = 300; // unità di spostamento (segs * displacement) in px rispetto al numero di segmenti

class terrain {
  struct voxel {
    int x;
    int y;
  };
private:
  std::list <int> seeds;
  int views;
public:
  voxel vx[SEGMENT_LIMIT];
  terrain() {
      srand(time(0));
      views = rand()%MAX_VIEWS + MIN_VIEWS;
      for(int c = 0; c < views; c++)
      {
          seeds.push_back(rand());
      }
      for(int c = 0; c < SEGMENT_LIMIT; c++) {
        vx[c].x = SCREEN_WIDTH * ((double) ((1 + c)*10000/SEGMENT_LIMIT)/10000);
        vx[c].y = 0;
      }
  }

  void terrain_gen(int start, int end, double displ, int max) {
    if(start >= end) {}
    else
    {
        int mid = (end + start) / 2;
        double rnd = ((double) rand()/(RAND_MAX)) - 0.5;
        vx[mid].y = SCREEN_HEIGHT + displ * rnd;
        displ = VARIANCE * displ; // displacement scalato del fattore variance
        terrain_gen(start, mid, displ, max); // reiterazione sui lati sx e dx del segmento
        terrain_gen(mid + 1, end, displ, max);
    }
  }
};
