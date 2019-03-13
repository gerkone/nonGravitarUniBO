#include <SFML/Graphics.hpp>

#include <list>
#include <iterator>
#include <time.h>

using namespace std;

struct voxel_2d {
  int x;
  int y;
  voxel_2d(int a = 0, int b = 0) {
    x = a;
    y = b;
  }
};

const int SEGMENT_LIMIT = 20; //segmenti massimi che comporranno il terreno
const int SEGMENT_MIN = 10; //segmenti massimi che comporranno il terreno
const int MAX_VIEWS = 5; //schermate massime

const int SCREEN_WIDTH = 440;
const int SCREEN_HEIGHT = 300;

const int VARIANCE = 0.25; //ruvidità di scalo tra displacement tra passaggi successivi
const float DISPLACEMENT = 0.5; // unità di spostamento (segs * displacement) in px rispetto al numero di segmenti
list <voxel_2d> terrain_gen(list <voxel_2d> vx, int seed, int start, int end, int displ, int max)
{
    if((start + 1) = end) { return vx;}
    else
    {
        int mid = (end - start) / 2;
        srand(seed);
        voxel_2d tmp = voxel_2d( (end/max) * SCREEN_WIDTH, floor((double) (rand()%2 - 1) * VARIANCE) );
        displ = VARIANCE * displ; // displacement scalato del fattore variance
        vx.push_front(terrain_gen(tmp, seed, start, mid, displ, max)); // reiterazione sui lati sx e dx del segmento
        vx.push_back(terrain_gen(tmp, seed, mid, end, displ, max));
        return vx;
    }
}

int main()
{
    srand(time(0));
    list <int> seeds;
    for(int c = 0; c < rand()%MAX_VIEWS; c++)
    {
        seeds.push_back(rand());
    }

    int r = rand();
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "terun");
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        list <int> :: iterator id = seeds.begin();

        if(//arrow pressed)
        {
            advance(id,1);
            voxels = terrain_gen(voxels, *id, 0, segs);
        }
        else if (//back pressed)
        {
            advance(id, -1);
            voxels = terrain_gen(voxels, *id, 0, segs);
        }

        window.clear();
        window.draw();
        window.display();
    }
    return 0;
}

subject=Learn Code on Mobile With Dcoder
