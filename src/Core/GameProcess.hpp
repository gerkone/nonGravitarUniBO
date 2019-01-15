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
    sf::Window* GetWindow();
    sf::Time GetElapsed();
    void RestartClock();
  private:
    Window m_window;
    sf::Clock m_clock;  //clock utile per sapere tempo tra ogni refresh dello schermo, eseguire il gioco a velocità costante su ogni hardware
    sf::Time m_elapsed;
    //istances of game objects
  };

}

#endif
