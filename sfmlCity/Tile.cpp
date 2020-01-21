#include "Tile.h"

//Constructor/Destructor

Tile::Tile(int grid_x, int grid_y, float gridSize, 
	 const sf::Texture&  texture_sheet, const sf::IntRect& text_rect,
	bool collision, short type):collision(collision), type(type), rect(text_rect) //creates the tile
{

	this->tile.setPosition(static_cast<float>(grid_x )* gridSize, static_cast<float>(grid_y)*gridSize); //sets the pixel location of tile
	this->tile.setTexture(texture_sheet);  //sets the texture to pull from 
	this->tile.setTextureRect(text_rect); //sets the place on the sheet to look at
	
	position = tile.getPosition(); //set local position vector
}

Tile::~Tile()
{

}

//Functions
short Tile::getType()const
{
	return this->type; 
}

bool Tile::isCollidable()const
{
	return collision; 
}

const sf::Vector2f& Tile::getPosition()const
{
	return tile.getPosition(); 
}

bool Tile::checkCollision(const sf::FloatRect frect)const
{
	if (tile.getGlobalBounds().intersects(frect))
	{
		return true;
	}
	else return false; 
}

sf::FloatRect Tile::getGlobalBounds()const
{
	return tile.getGlobalBounds(); 
}

