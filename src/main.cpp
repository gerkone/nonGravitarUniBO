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

const int VARIANCE = 30; //spostamento in pixel massimo tra gli estremi dei segmenti

list <voxel_2d> terrain_gen(list <voxel_2d> vx, int seed, int start, int end)
{
    if((start + 1) = end) { return vx;}
    else
    {
        int mid = (end - start) / 2;
        list <voxel_2d> :: iterator id = vx.begin();
        advance(id, mid);
        srand(seed);
        id.y = id.y + floor((double) (rand()%2 - 1) * VARIANCE);
        terrain_gen(vx, seed, start, mid);
        terrain_gen(vx, seed, mid + 1, end);
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
    for(int c = 0; c < SEGMENT_MIN + rand()%SEGMENT_LIMIT; c++)
    {
        voxels.push_back(new voxel_2d((c + 1) * SCREEN_WIDTH/segs), 150);  //setta i segmenti allineati, uno dopo l'altro
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
