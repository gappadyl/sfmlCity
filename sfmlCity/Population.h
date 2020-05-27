#pragma once
#include <vector>
#include <iostream>
#include "Person.h"

class Population
{


public:
	//Constructor / Destructor
	Population( sf::RenderTarget* window, std::map<std::string, sf::Texture> textures ); 
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
	 
	std::map<std::string, sf::Texture> textures; 

	//Functions
	void setUpPlayer(std::map<std::string, sf::Texture>& textures); 
};

