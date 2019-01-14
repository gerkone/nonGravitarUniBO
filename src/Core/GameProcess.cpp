#include "GameProcess.hpp"

namespace game {
  GameProcess::GameProcess(): m_window("NOGRAVITAR", sf::Vector2u(800,600)){
  }

  GameProcess::~GameProcess(){}

  void GameProcess::Update(){
    m_window.Update();
  }

  //game object functions
}
