#pragma once


#include<iostream>
#include "tileMap.h"




class City
{
private:

	//initialization func
	void initWindow(); 
	bool initTileMap(); 
	void drawTileMap(); 
	

	//Variables
	sf::RenderWindow *window; 
	sf::Event sfEvent; 
	tileMap map; 

	 const int level[128]= 
	 {
		 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 2, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 3, 3, 3, 3,
		0, 1, 0, 0, 2, 0, 3, 3, 3, 0, 1, 1, 1, 0, 0, 0,
		0, 1, 1, 0, 3, 3, 3, 0, 0, 0, 1, 1, 1, 2, 0, 0,
		0, 0, 1, 0, 3, 0, 2, 2, 0, 0, 1, 1, 1, 1, 2, 0,
		2, 0, 1, 0, 3, 0, 2, 2, 2, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 1, 0, 3, 2, 2, 2, 0, 0, 0, 0, 1, 1, 1, 1,
	 };

public:
	//constructor/destructor
	City();
	virtual ~City();

	//Functions
	void updateSFMLEvents();
	void update();
	void render(); 
	void run(); 
	
	
};


