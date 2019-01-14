#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <SFLM/System.hpp>
#include <SFLM/Window.hpp>
//notation: m_member : member of a structure/class
//          l_member : longint
namespace window {
  class WindowManager(){
  public:
    WindowManager();
    WindowManager(const std::string& l_title,const sf::Vector2u& l_size);
    ~WindowManager();
    void BeginDraw();
    void EndDraw();
    void Update();
    bool IsDone();
    bool IsFullscreen();
    sf::Vector2u GetWindowSize();
    void ToggleFullscreen();
    void Draw(sf::Drawable& l_drawable);
  private:
    void Setup(const std::string& l_title, const sf::Vector2u& l_size);
    void Destroy();
    void Create();
    sf::RenderWindow m_window;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isClose;
    bool m_isFullscreen;
  };
}

#endif //WINDOWMANAGER_H
