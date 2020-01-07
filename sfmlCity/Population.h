#pragma once
#include <vector>
#include <iostream>
#include "Person.h"

class Population
{


public:
	//Constructor / Destructor
	Population(const int* level, sf::RenderTarget* window, std::map<std::string, sf::Texture> textures ); 
	Population();
	~Population(); 

	//Functions
	void updatePopulation(float& dt);
	void renderPopulation(); 
	float getHappy(); 
	//Variables
	


private:
	//Variables
	Person* Robert;  
	sf::RenderTarget* target; 
	const int* level; 
	std::map<std::string, sf::Texture> textures; 

	//Functions
	void setUpPlayer(std::map<std::string, sf::Texture> textures); 
};

