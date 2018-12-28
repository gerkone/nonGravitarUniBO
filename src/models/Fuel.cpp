#include "Fuel.hpp"

namespace fuel {
  Fuel::Fuel(int location = 0, int type = 0, bool used = false) {
    this.location = location;
    this.type = type;
    this.alive = alive;
  }
  void Fuel::refuel() {
    if(!used)
      used = true;
  }
}
