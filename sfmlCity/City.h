#pragma once

#include<iostream>
#include "tileMap.h"
#include "Camera.h"
#include "Population.h"



class City
{
private:

	//initialization func
	void initWindow(); 
	void initView();
	bool initTileMap(); 
	void drawTileMap();
	void initPopulation(); 
	
	

	//Variables
	sf::RenderWindow *window; 
	sf::Event sfEvent; 
	Camera camera; 
	sf::Clock dtClock;
	tileMap map;
	Population pop; 

	float dt;
	unsigned int heightMap; 
	unsigned int widthMap; 
	unsigned int tileLength; 
	bool bHasFocus = true;

	const int level[256]= 
	{
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 1,
		1, 0, 0, 0, 2, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 2, 0, 1,
		1, 0, 0, 0, 3, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 1,
		1, 0, 0, 0, 3, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 3, 2, 2, 2, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 1,
		1, 0, 0, 0, 2, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0, 2, 0, 1,
		1, 0, 0, 0, 3, 0, 2, 2, 0, 0, 0, 0, 0, 0, 2, 1,
		1, 0, 0, 0, 3, 0, 2, 2, 2, 0, 0, 0, 0, 0, 0, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};

public:
	//constructor/destructor
	City();
	virtual ~City();

	//Functions
	void updateDT();
	void updateSFMLEvents();
	void update();
	void render(); 
	void run(); 
	
	
	
};


