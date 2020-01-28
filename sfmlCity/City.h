#pragma once

#include<iostream>
#include"GameMode.h"





class City
{
private:
	enum mode {Game=0, Editor=1};
	//initialization func
	void initWindow(); 
	void initView(); 
	void initPopulation(); 
	void initModes(); 
	

	//Variables

	//Sf variables
	sf::RenderWindow *window; 
	sf::Event sfEvent; 
	sf::Clock dtClock;

	//Game Objects
	Camera camera; //camera object
	TileMapLevel* levelMap;
	Population* population; 

	//Resources/ information
	std::map<std::string, sf::Texture> textures; 
	float dt;
	unsigned int heightMap; 
	unsigned int widthMap; 
	unsigned int tileLength; 
	bool bHasFocus = true;
	
	//Modes
	mode currentMode; 
	GameMode *game; 
	
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


