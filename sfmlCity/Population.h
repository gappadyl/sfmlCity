#pragma once
#include <vector>
#include <iostream>
#include "Person.h"

class Population
{


public:
	Population(); 
	Population(const int* level, sf::RenderTarget* window); 
	~Population(); 

	//Functions
	void updatePopulation(float& dt);
	void renderPopulation(); 
	float getHappy(); 
	//Variables
	


private:
	//Variables
	Person Robert; 
	//std::vector<Entity> population; 
	//float *happiness; 
	sf::RenderTarget* target; 
	const int* level; 


	//Functions
};

