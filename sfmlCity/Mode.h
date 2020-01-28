#pragma once
#include "TileMapLevel.h"
#include "Camera.h"
//MODE BASECLASS, ->[A Mode is a class that handles what is rendered and updated]
class Mode
{
public:
	//Constructor/destructor
	Mode(sf::RenderWindow* window, Camera *view,  unsigned int* heightMap, unsigned int* widthMap, unsigned int* tileLength, bool* hasFocus);
	Mode(); 
	virtual ~Mode();

	//Functions
	virtual void update(float& dt)=0; 
	virtual void render(sf::RenderTarget& target)=0; 

private:

protected:
	//variables
	
	sf::RenderWindow* window; 
	sf::Event sfEvent;
	sf::Clock dtClock;
	Camera *camera; //camera object
	

	//a pointer to the dimensions so it can render the right amount of squares and control camera correctly
	unsigned int* heightMap;
	unsigned int* widthMap;
	unsigned int* tileLength;
	bool *hasFocus; 

};

