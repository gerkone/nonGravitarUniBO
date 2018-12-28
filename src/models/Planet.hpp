#ifndef PLANET_H
#define PLANET_H

#inlcude <stdlib.h>
#inlcude <time.h>
#include <list>

const MAX_BUNKERS = 4;
const MAX_REFUELS = 4;
const MAX_SCREENS = 4;

const MAX_X = 100;
const MAX_Y = 100;
const SPACING = 100;

namespace planet {
  class Planet {
  public:
    Planet(){}
    void generate_surface() {}
  private:
    list <Bunker> bunkers;
    list <Fuel> fuels
    list <int> seeds;
  };
}
#endif //PLANET_H
