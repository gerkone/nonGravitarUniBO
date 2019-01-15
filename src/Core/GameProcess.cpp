#include "GameProcess.hpp"

namespace game {
  GameProcess::GameProcess(): m_window("NOGRAVITAR", sf::Vector2u(800,600)){
  }

  GameProcess::~GameProcess(){}

  void GameProcess::Update(){
    m_window.Update();
  }

  sf::Time GameProcess::GetElapsed()
  {
    return m_elapsed;
  }
  void GameProcess::RestartClock()
  {
    m_elapsed = m_elapsed + m_clock.restart();
  }

  //game object functions
}
