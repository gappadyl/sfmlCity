#include "GameMode.h"
//Constructor/Destructor
GameMode::GameMode(sf::RenderWindow* window, Camera* view, Population* population,  TileMapLevel* level, 
	unsigned int* heightMap, unsigned int* widthMap, unsigned int* tileLength,
	bool* hasFocus):Mode(window, view, heightMap, widthMap, tileLength, hasFocus)
{
	this->population = population; 
	this->level = level; 
}

GameMode::~GameMode()
{
	
}


//Functions
void GameMode::update(float& dt)
{
	//GameMode Camera Controls
	
	camera->cameraUpdate(dt, hasFocus); 
	camera->boundsControl(camera->getCamera(), camera->getOldCamera() );

	//GameMode Population Controls
	 
	
	if (level)
	{
		level->gridBoarderCollisionCheck(population->getPlayer()); 
		 
	}

	this->population->updatePopulation(dt);
}

void GameMode::render(sf::RenderTarget* target)
{
	
	level->render(*target, false); 
	population->renderPopulation(target);
	//sets window view to camera
	camera->cameraRender(target); 
	//displays the window
	
}
