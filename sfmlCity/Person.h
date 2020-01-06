#pragma once
#include "Entity.h"
class Person: public Entity
{
public:
	//Constructors/destructor
	Person(float x, float y, sf::Texture* texture);
	Person(); 
	~Person(); 
	
	//Functions
	std::string getName();
	sf::Vector2f getLocation(); 
	void setName(std::string name);
	void setLocation(sf::Vector2f location); 

	//inherited from entity
	

private: 
	std::string name; 
	sf::Vector2f location; 
	float movementSpeed = 100.f; 
	//init functions
	void initVariables(); 
	void initComponents(); 
	
};

