#include <list>
#include <iterator>
#include <time.h>
#include <iostream>
#include <math.h>

#include <SFML/Graphics.hpp>


using namespace std;


const int SEGMENT_LIMIT = 1000; //segmenti massimi che comporranno il terreno
const int MAX_VIEWS = 5; //schermate massime

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 500;

const double VARIANCE = 0.55; //ruvidità di scalo tra displacement tra passaggi successivi
const double DISPLACEMENT = 400; // unità di spostamento (segs * displacement) in px rispetto al numero di segmenti


struct voxel {
  float x;
  float y;
};


public:
  std::list <int> seeds;
  int views;
public:
  voxel vx[SEGMENT_LIMIT];
  terrain() {
      srand(time(0));
      views = rand()%MAX_VIEWS + MIN_VIEWS;
      vx = new voxel[SEGMENT_LIMIT];
      for(int c = 0; c < views; c++)
      {
          seeds.push_back(rand());
      }
      for(int c = 0; c < SEGMENT_LIMIT; c++) {
        vx[c].x = SCREEN_WIDTH * ((double) ((1 + c)*10000/SEGMENT_LIMIT)/10000);
        vx[c].y = 0;
      }
  }

  void terrain_gen(voxel vx[], int start, int end, double displ) {
    if(start + 1 >= end) {}
    else
    {
        int mid = (end + start) / 2;
        double rnd = ((double) rand()/(RAND_MAX)) - 0.5;
        float offset = displ * rnd;
        vx[mid].y = (vx[start].y + vx[end].y)/2 + offset;
        displ = VARIANCE * displ; // displacement scalato del fattore variance
        terrain_gen(vx, start, mid, displ); // reiterazione sui lati sx e dx del segmento
        terrain_gen(vx, mid, end, displ);
    }
  }
};
