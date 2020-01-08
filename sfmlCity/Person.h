#pragma once
#include "Entity.h"
class Person: public Entity
{
public:
	//Constructors/destructor
	Person(float x, float y, sf::Texture& texture_sheet);
	Person(); 
	~Person(); 
	
	//Functions

	//Accesors
	std::string getName();
	sf::Vector2f getLocation(); 
	//Mutators
	void setName(std::string name);
	void setLocation(sf::Vector2f location); 

	
	

private: 

	//Variables
	std::string name; 
	sf::Vector2f location; 
	float movementSpeed = 100.f; 


	//init functions
	void initVariables(); 
	//void initComponents(sf::Texture& texture_sheet); 
	
};

