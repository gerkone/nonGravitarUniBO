#ifndef TEXTNODE_HPP
#define TEXTNODE_HPP

#include <SFML/Graphics.hpp>
class TextNode {
public:
  TextNode(const std::string& text, sf::RenderWindow& window);

  void setString(const std::string& text);
  void setPosition(float x, float y);
  void draw();
  void setFont(sf::Font& font);
  sf::Text getText();

private:
  sf::Text mText;
  sf::Font mFont;
  sf::RenderWindow* mWindow;

};
#endif
