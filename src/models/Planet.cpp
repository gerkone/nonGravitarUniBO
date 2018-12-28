#include "Planet.hpp"
#include "Fuel.hpp"
#include "Bunker.hpp"

namespace planet {

  Planet::Planet() {
    srand(time(0));
    for(int i = 0; i < rand()%MAX_BUNKERS; i++) {
      Bunker b = Bunker();  //TODO: inizializzare con valori random
      fuels.push_back(b);
    }
    for(int i = 0; i < rand()%MAX_REFUELS + 1; i++) {
      Fuel f = Fuel();  //TODO: inizializzare con valori random
      fuels.push_back(f);
    }
    for(int i = 0; i < rand()%MAX_SCREENS; i++) {
      seeds.push_back(rand());                    //each screen has its own seed, randomly initialized
    }
  }

  void Planet::generate_surface() {
    list<int>::iterator id;
    int x, y;
    for(id = seeds.begin(); id != seeds.end(); id++) {
      srand(id);
      x = 0;
      y = 0;
      while(x < SCREEN_WIDTH) {
        y = rand()%MAX_Y + SPACING;  //spacing = distance from the top of the screen
        x = rand()%MAX_X + x;  //spacing = distance from the top of the screen
      }
    }
  }
}
