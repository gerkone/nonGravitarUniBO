#include <SFML/Graphics.hpp>

#include <list>
#include <iterator>
#include <time.h>
#include <iostream>
#include <math.h>

using namespace std;

struct voxel_2d {
  int x;
  int y;
  voxel_2d *next;
  voxel_2d(int a = 0, int b = 0, voxel_2d *n = nullptr) : x(a), y(b), next(n) {
  }
};

const int SEGMENT_LIMIT = 20; //segmenti massimi che comporranno il terreno
const int SEGMENT_MIN = 10; //segmenti massimi che comporranno il terreno
const int MAX_VIEWS = 5; //schermate massime

const int SCREEN_WIDTH = 440;
const int SCREEN_HEIGHT = 300;

const int VARIANCE = 0.25; //ruvidità di scalo tra displacement tra passaggi successivi
const float DISPLACEMENT = 0.5; // unità di spostamento (segs * displacement) in px rispetto al numero di segmenti

voxel_2d *push_back(voxel_2d *vx, voxel_2d *ad) {
  if(vx->next == nullptr) {
    vx->next = ad;
  } else {
    push_back(vx->next, ad);
  }
}

voxel_2d *push_front(voxel_2d *vx, voxel_2d *ad) {
  if(ad != nullptr) {
    voxel_2d *id = ad;
    while(id->next != nullptr) {
      id = id->next;
    }
    id->next = vx;
    return ad;
  } else {
    return vx;
  }
}


voxel_2d *terrain_gen(voxel_2d *vx, int seed, int start, int end, int displ, int max)
{
    if((start + 1) == end) { return vx;}
    else
    {
        int mid = (end - start) / 2;
        srand(seed);
        voxel_2d x = voxel_2d( (end/max) * SCREEN_WIDTH, floor((double) (rand()%2 - 1) * displ), nullptr);
        voxel_2d *tmp = &x;
        displ = VARIANCE * displ; // displacement scalato del fattore variance
        push_front(vx, terrain_gen(tmp, seed, start, mid, displ, max)); // reiterazione sui lati sx e dx del segmento
        push_back(vx, terrain_gen(tmp, seed, mid, end, displ, max));
        return vx;
    }
}

void printL(voxel_2d *l) {
  if(l->next == nullptr) {
    printf("niente");
  } else {
    std::cout << "x = " << l->x << "\n";
    cout << "y = " << l->y << "\n";
    cout << "  ------\n";
    printL(l->next);
  }
}

int main()
{
    srand(time(0));
    std::list <int> seeds;
    std::list <int> segs;
    for(int c = 0; c < rand()%MAX_VIEWS; c++)
    {
        seeds.push_back(rand());
        segs.push_back(rand()%(SEGMENT_LIMIT - SEGMENT_MIN) + SEGMENT_MIN);
    }

    list <int> :: iterator id = seeds.begin();
    list <int> :: iterator it = segs.begin();
    voxel_2d *voxels = nullptr;
    while(true) {
        advance(id,1);
        advance(it, 1);
        voxels = terrain_gen(voxels, *id, 0, *it, *it * DISPLACEMENT, *it);
        printL(voxels);
    }

    //
    // int r = rand();
    // sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "terun");
    // while (window.isOpen())
    // {
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }
    //     list <int> :: iterator id = seeds.begin();
    //
    //     if(//arrow pressed)
    //     {
    //         advance(id,1);
    //         voxels = terrain_gen(voxels, *id, 0, segs);
    //     }
    //     else if (//back pressed)
    //     {
    //         advance(id, -1);
    //         voxels = terrain_gen(voxels, *id, 0, segs);
    //     }
    //
    //     window.clear();
    //     window.draw();
    //     window.display();
    // }
    // return 0;
}
