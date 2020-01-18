#include "RegularTile.h"
//Constructors/destructors
RegularTile::RegularTile(float grid_x, float grid_y, float gridSize,
	const sf::Texture texture_sheet,const sf::IntRect rect,
	bool collision, short type):Tile(grid_x, grid_y, gridSize, texture_sheet, rect, collision, type)
{

}
RegularTile::~RegularTile()
{

}

void RegularTile::render(sf::RenderTarget& target)
{
	target.draw(this->tile); 
}

void RegularTile::update(short type)
{

}