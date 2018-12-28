#include "Bunker.hpp"

namespace bunker {
  Bunker::Bunker(int location = 0, int type = 0, bool alive = true) {
    this.location = location;
    this.type = type;
    this.alive = alive;
  }
  void Bunker::destroy() {
    alive = false;
  }
  void Bunker::fire() {
    
  }
}
