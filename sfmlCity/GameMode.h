#pragma once
#include "Mode.h"
#include "tileMap.h"
#include "Population.h"
#include <queue>

//GAMEMODE CLASS->[handles the rendering and updating during gamemode]
class GameMode : public Mode
{

public:
	GameMode(sf::RenderWindow* window, Camera* view, Population* population, TileMapLevel* level, 
		unsigned int* heightMap, unsigned int* widthMap, unsigned int* tileLength, bool* hasFocus);
	~GameMode(); 
	
	virtual void update(float& dt); 
	virtual void render(sf::RenderTarget* target); 
	


private:

	//Variables
	//std::vector<sf::Event> eventQueue; 
	Population* population; 
	TileMapLevel* level; 
};

