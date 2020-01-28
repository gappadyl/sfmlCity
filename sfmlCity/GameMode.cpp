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
	SFMLCameraEvent();//NOT WORKING
	camera->cameraUpdate(dt, hasFocus); 
	camera->boundsControl(camera->getCamera(), camera->getOldCamera() );

	//GameMode Population Controls
	this->population->updatePopulation(dt); 
	
	if (level)
	{
		level->gridBoarderCollisionCheck(population->getPlayer()); 
	}
}

void GameMode::render(sf::RenderTarget& target)
{
	
	level->render(*window, true); 

	population->renderPopulation();
	//sets window view to camera
	camera->cameraRender(); 
	//displays the window
	
}

void GameMode::SFMLCameraEvent()
{

}

void GameMode::addEvent(sf::Event& sfEvent)const 
{
	
	//this->eventQueue.push_back(sfEvent); 
}

void GameMode::CameraEvents()
{
	
}