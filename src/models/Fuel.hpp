#ifndef FUEL_H
#define FUEL_H

namespace fuel {
  class Fuel {
  private:
    int type;
    int location;
    bool used;
  public:
    Fuel(int type, int location, bool used) {}
    void refuel() {}
  };

}
#endif //PLANET_H
