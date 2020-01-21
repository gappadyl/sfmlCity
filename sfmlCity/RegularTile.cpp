#include "RegularTile.h"
//Constructors/destructors
RegularTile::RegularTile(float grid_x, float grid_y, float gridSize,
	const sf::Texture& texture_sheet,const sf::IntRect& rect,
	bool collision, short type):Tile(grid_x, grid_y, gridSize, texture_sheet, rect, collision, type)
{
	std::cout << grid_x << " " << grid_y << " " << gridSize << std::endl; 
}
RegularTile::~RegularTile()
{

}
//Fuctions
void RegularTile::render(sf::RenderTarget& target)
{
	target.draw(this->tile); 


}

void RegularTile::update(short type)
{

}
//Accesors
std::string RegularTile::getTileAsString()const
{
	std::stringstream word; 
	word << type << " "<<  rect.left << " " << rect.top << " " << collision << " "; 

	return word.str(); 
}

const bool & RegularTile::getCollision()const
{
	return this->collision; 
}