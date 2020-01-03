#pragma once
#include <vector>
#include <iostream>
#include "Entity.h"

class Population
{


public:
	Population(); 
	Population(int* level, sf::RenderTarget& window); 
	~Population(); 

	//Functions
	void updatePopulation(float* dt);
	void renderPopulation(); 
	float* getHappy(); 
	//Variables
	


private:
	//Variables
	std::vector<Entity> population; 
	float *happiness; 


	//Functions
};

