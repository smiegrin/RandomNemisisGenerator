#include "TileGrid.h"

TileGrid::TileGrid(
    const std::string& pathToTiles,
    const sf::Vector2i& tileSize,
    const sf::RectangleShape& outputRect,
    const sf::Color& bgColor
    ) :
  _tileSize(tileSize),
  _outputRect(outputRect),
  _bgColor(bgColor)
{
  _tileset.loadFromFile(pathToTiles);
  _output.create(_outputRect.getSize().x, _outputRect.getSize().y);
  _tileSpace = new int[gridWidth()*gridHeight()];
  for (int i = 0; i < gridWidth()*gridHeight(); i++)
    _tileSpace[i] = 0;
}

void TileGrid::setTile(const int& x, const int& y, const int& newTileValue) {
  if (x >= gridWidth() || y >= gridHeight() || x < 0 || y < 0) return;
  _tileSpace[x + y*gridWidth()] = newTileValue;
  refresh(x, y);
}

void TileGrid::setSize(sf::Vector2f size) {
  int oldwidth = gridWidth();
  int holdheight = gridHeight();
  _outputRect.setSize(size);
  size.x = size.x/_tileSize.x * _tileSize.x;
  size.y = size.y/_tileSize.y * _tileSize.y;
  _output.create(size.x, size.y);
  int* newTilespace = new int[gridWidth()*gridHeight()];

  //add branches later for resize anchor point
  int widthBound = std::min(oldwidth, gridWidth());
  int heightBound = std::min(holdheight, gridHeight());
  for (int j = 0; j < heightBound; j++) {
    for (int i = 0; i < widthBound; i++) {
      _tileSpace[(oldwidth-i) + oldwidth*(holdheight-j)]
        = newTilespace[(gridWidth()-i) + gridWidth()*(gridHeight()-j)];
    }
  }
  refreshAll();
}

int TileGrid::getTile(const int& x, const int& y) const {
  if (x >= gridWidth() || y >= gridHeight() || x < 0 || y < 0) return 0;
  return _tileSpace[x + y*gridWidth()];
}

void TileGrid::refresh(const int& x, const int& y) {
  sf::RectangleShape printhead;
  int tileValue = getTile(x, y);
  int rowSize = _tileset.getSize().x / _tileSize.x;
  printhead.setSize(sf::Vector2f(_tileSize.x, _tileSize.y));
  printhead.setPosition(_tileSize.x*x, _tileSize.y*y);
  printhead.setTexture(&_tileset);
  sf::IntRect textureRect;
  textureRect.left = tileValue % rowSize;
  textureRect.top = tileValue / rowSize;
  textureRect.width = _tileSize.x;
  textureRect.height = _tileSize.y;
  printhead.setTextureRect(textureRect);
  _output.draw(printhead);
  _output.display();
}

void TileGrid::refreshAll() {
  sf::RectangleShape printhead;
  int rowSize = _tileset.getSize().x / _tileSize.x;
  //std::cout << "The row is " << rowSize << " tiles wide in the font sheet." << std::endl;
  printhead.setSize(sf::Vector2f(_tileSize.x, _tileSize.y));
  sf::IntRect textureRect;
  _output.clear(_bgColor);

  for (int j = 0; j < gridHeight(); j++) {
    for (int i = 0; i < gridWidth(); i++) {
      int tileValue = getTile(i, j);
      printhead.setPosition(_tileSize.x*i, _tileSize.y*j);
      printhead.setTexture(&_tileset);
      textureRect.left = (tileValue % rowSize) * _tileSize.x;
      textureRect.top = (tileValue / rowSize) * _tileSize.y;
      textureRect.width = _tileSize.x;
      textureRect.height = _tileSize.y;
      printhead.setTextureRect(textureRect);
      _output.draw(printhead);
    }
  }
  _output.display();
}

void TileGrid::clear(const int& tile) {
  for (int j =0; j < gridHeight(); j++) {
    for (int i = 0; i < gridWidth(); i++) {
      setTile(i, j, tile);
    }
  }
}

void TileGrid::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  sf::RectangleShape tempRect = _outputRect;
//  tempRect.setOutlineThickness(2);
//  tempRect.setOutlineColor(sf::Color::Red);
  sf::Texture tempTexture = _output.getTexture();
  tempRect.setTexture(&tempTexture);
  target.draw(tempRect);
}
