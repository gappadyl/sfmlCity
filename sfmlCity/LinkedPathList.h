#pragma once
#include "path.h"

class LinkedPathList
{
public:
	//Constructor/Destructor
	LinkedPathList(); 
	LinkedPathList(sf::Vector2i initialNode); 
	~LinkedPathList();

	//Functions
	void add(sf::Vector2i data); 
	void remove(int index); 
	void remove(); 
	void reverse(); 
	int size(); 
	void printPath(); 
	//variables
	Path* head; 

};

