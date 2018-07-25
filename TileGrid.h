#pragma once

#include <iostream>
#include <string>

#include <SFML/Graphics.hpp>

class TileGrid : public sf::Drawable {
public:
  TileGrid(
      const std::string&,
      const sf::Vector2i&,
      const sf::RectangleShape&,
      const sf::Color& = sf::Color::Black
  );

  void setTile(const int&, const int&, const int&);
  void setTileSize(const int& width, const int& height)
    { setTileSize(sf::Vector2i(width, height)); }
  void setTileSize(const sf::Vector2i& size)
    { _tileSize = size; }
  void setSize(const float& width, const float& height)
    { setSize(sf::Vector2f(width, height)); }
  void setSize(sf::Vector2f size);
  void setPosition(const float& x, const float& y)
    { setPosition(sf::Vector2f(x, y)); }
  void setPosition(const sf::Vector2f& pos)
    { _outputRect.setPosition(pos); }
  void setBackgroundColor(const sf::Color& color)
    { _bgColor = color; }

  int getTile(const int&, const int&) const;
  int gridWidth() const { return _outputRect.getSize().x/(_tileSize.x); }
  int gridHeight() const { return _outputRect.getSize().y/(_tileSize.y); }
  sf::Vector2f getSize() const { return _outputRect.getSize(); }
  sf::Vector2i getTileSize() const { return _tileSize; }
  sf::Vector2f getPosition() const { return _outputRect.getPosition(); }
  sf::Color getBackgroundColor() const { return _bgColor; }

  void refresh(const int&, const int&);
  void refreshAll();
  void clear(const int& = 0);
  void draw(sf::RenderTarget&, sf::RenderStates = sf::RenderStates::Default) const;
  
private:
  sf::Texture _tileset;
  sf::Vector2i _tileSize;
  sf::RenderTexture _output;
  sf::RectangleShape _outputRect;
  sf::Color _bgColor;
  int* _tileSpace;
};
