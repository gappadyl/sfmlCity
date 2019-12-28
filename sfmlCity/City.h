#pragma once


#include<iostream>
#include "tileMap.h"




class City
{
private:

	//initialization func
	void initWindow(); 
	void initView();
	bool initTileMap(); 
	void drawTileMap(); 

	bool isCameraLegal(sf::Vector2f pos, sf::Vector2f size);
	void pollKeyEvents();
	

	//Variables
	sf::RenderWindow *window; 
	sf::Event sfEvent; 
	sf::View camera;
	sf::Clock dtClock;
	float dt;
	sf::Vector2i mousepos;
	tileMap map; 
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


