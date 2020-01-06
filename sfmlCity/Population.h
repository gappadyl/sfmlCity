#pragma once
#include <vector>
#include <iostream>
#include "Person.h"

class Population
{


public:
	//Constructor / Destructor
	Population(const int* level, sf::RenderTarget* window); 
	Population();
	~Population(); 

	//Functions
	void updatePopulation(float& dt);
	void renderPopulation(); 
	float getHappy(); 
	//Variables
	


private:
	//Variables
	Person Robert; 
	sf::Texture texture; 
	//std::vector<Entity> population; 
	//float *happiness; 
	sf::RenderTarget* target; 
	const int* level; 

	//Functions
	void setUpPlayer(); 
};

