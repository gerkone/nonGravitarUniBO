#include "WindowManager.hpp"

namespace window {
  WindowManager::WindowManager(){ Setup("NOGRAVITAR", sf::Vector2u(640,480)); }

  WindowManager::WindowManager(const std::string& l_title, const sf::Vector2u& l_size)
  {
    Setup(l_title,l_size);
  }

  WindowManager::~WindowManager()
  {
    Destroy();
  }

  void WindowManager::Setup(const std::string l_title,const sf::Vector2u& l_size)
  {
    m_windowTitle = l_title;
    m_windowSize = l_size;
    m_isFullscreen = false;
    m_isClose = false;
    Create();
  }

  void Window::Create()
  {
    auto style = (m_isFullscreen ? sf::Style::Fullscreen : sf::Style::Default);
    m_window.create({ m_windowSize.x, m_windowSize.y, 32 }, m_windowTitle, style);
    m_window.setFramerateLimit(FPS_CAP);
  }

  void Window::Destroy()
  {
    m_window.close();
  }

  void Window::Update(){
    sf::Event event;
    while(m_window.pollEvent(event)){
      if(event.type == sf::Event::Closed){
        m_isClose = true;
      } //else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F11)
      // {
      //   ToggleFullscreen();
      // }
    }
  }

  void Window::ToggleFullscreen()
  {
    m_isFullscreen = !m_isFullscreen;
    Destroy();
    Create();
  }

  void Window::Draw(sf::Drawable&l_drawable)
  {
    m_window.draw(l_drawable);
  }

  void Window::BeginDraw()
  {
    m_window.clear(); //default nero
  }

  void Window::EndDraw()
  {
    m_window.display();
  }

  bool Window::IsDone()
  {
    return m_isClose;
  }

  bool Window::IsFullscreen()
  {
    return m_isFullscreen;
  }

  sf::Vector2u Window::GetWindowSize()
  {
    return m_windowSize;
  }

}
