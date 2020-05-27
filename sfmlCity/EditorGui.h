#pragma once
#include "tile.h"
#include "Gui.h"


/*texture object for tilemap
	vector holding tiles "map selection"
	integer objects to hold dimensions
	probably able to calculate amount of tiles, file pixel length/width
	probably a save to file method
	maybe a tilemap object?
	from to (x, y)
	local position on screen
	global position in world
	camera position [need to calculate local positon in respect to camera position)*/


class EditorGui:public Gui
{
public:
	//Constructor/Destructor
	EditorGui(); //add constructor for width, height, texture, ect
	~EditorGui(); 


	//Functions
	virtual sf::Vector2f getLocation()const; 
	virtual void update(sf::Vector2i& mousePos, float& dt); 
	virtual void render(sf::RenderTarget& target);
};

