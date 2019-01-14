#ifndef GAMEPROCESS_H
#define GAMEPROCESS_H

#include <SFLM/System.hpp>
#include <SFLM/Window.hpp>
#include <SFLM/Graphics.hpp>

namespace game {
  class GameProcess(){
  public:
    GameProcess();
    ~GameProcess();
    void HandleInput();
    void Update();
    void Render();
    Window* GetWindow();
  private:
    Window m_window;
    //istances of game objects
  };

}

#endif
