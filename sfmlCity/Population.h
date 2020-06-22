#pragma once
#include <vector>
#include <math.h>
#include <iostream>
#include "Person.h"
#include "TileMapLevel.h"
class Population
{


public:
	//Constructor / Destructor
	Population( sf::RenderTarget* window, std::map<std::string, sf::Texture> textures, TileMapLevel* level);
	Population();
	~Population(); 

	//Functions
	void updatePopulation(float& dt);
	void renderPopulation(sf::RenderTarget* window);
	float getHappy(); 
	Person* getPlayer()const; 
	//Variables
	


private:
	//Variables
	Person* Robert;  
	sf::RenderTarget* target; 
	TileMapLevel* map; 
	std::map<std::string, sf::Texture> textures; 
	std::vector<Entity*> population; 

	//Functions
	void setUpPlayer(std::map<std::string, sf::Texture>& textures); 
};

