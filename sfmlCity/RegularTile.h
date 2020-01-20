#pragma once
#include "Tile.h"

class RegularTile: public Tile
{

public: 
	//Constructor/Destructor
	RegularTile(float grid_x, float grid_y, float gridSize,
		const sf::Texture& texture_sheet, const sf::IntRect& rect,
		bool collision, short type); 
	~RegularTile(); 
	
	virtual void render(sf::RenderTarget& target); 
	virtual void update(short type); 
	virtual std::string getTileAsString()const; 
	virtual const bool & getCollision() const; 
};

