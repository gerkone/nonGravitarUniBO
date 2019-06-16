#include <TextNode.hpp>
#include <iostream>
#include <cassert>

TextNode::TextNode(const std::string& text, sf::RenderWindow& window) : mWindow(&window) {
  mText.setCharacterSize(20);
  mText.setString(text);
  mFont.loadFromFile("Media/Sansation.ttf");
  mText.setFont(mFont);
}

void TextNode::setString(const std::string& text){
  mText.setString(text);
}

void TextNode::draw(){
  mWindow->draw(mText);
}

void TextNode::setPosition(float x, float y){
  mText.setPosition(x, y);
}

void TextNode::setFont(sf::Font& font){
  mText.setFont(font);
}

sf::Text TextNode::getText(){
  return mText;
}
