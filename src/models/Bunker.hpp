#ifndef BUNKER_H
#define BUNKER_H

namespace bunker {
  class Bunker {
  private:
    int location; //segment of terrain on which the bunker is
    int type; //firing mode
    bool alive;
  public:
    Bunker(int location, int type, bool alive) {}
    void fire() {}
    void destroy() {}
  };
}
#endif
