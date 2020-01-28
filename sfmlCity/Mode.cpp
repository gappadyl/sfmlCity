#include "Mode.h"
//Constructor/Destructor
Mode::Mode(sf::RenderWindow* window, Camera* view, unsigned int* heightMap, unsigned int* widthMap, unsigned int* tileLength, bool* hasFocus)
	:window(window), camera(view), heightMap(heightMap), widthMap(widthMap), tileLength(tileLength), hasFocus(hasFocus)
{
	sfEvent = sf::Event(); 
	dtClock = sf::Clock(); 
}
Mode::Mode()
{

	//if no constructor provided
	window = NULL; 
	camera = NULL; 
	heightMap = NULL; 
	widthMap = NULL; 
	tileLength = NULL; 

	hasFocus = false; 

	sfEvent = sf::Event(); 
	dtClock = sf::Clock(); 
	
}

Mode::~Mode()
{

}
//Functions

void Mode::update(float& dt)
{

}

void Mode::render(sf::RenderTarget& target)
{

}
