#pragma once
#include "Mode.h"
#include "Population.h"
#include "TileMapLevel.h"
#include "EditorGui.h"

class EditorMode :public Mode
{
public:
	EditorMode(sf::RenderWindow* window, Camera* view, Population* population, TileMapLevel* level,
		unsigned int* heightMap, unsigned int* widthMap, unsigned int* tileLength,
		bool* hasFocus, float& dt);

	~EditorMode(); 
	//Functions
	virtual void update(float& dt); 
	virtual void render(sf::RenderTarget* window); 

	//Initializers
	void initGui(sf::Font& font, const sf::Texture* textureSheet);

	
private:
	float& dt; 
	Population* population; //keeps a reference to population & tilemap
	TileMapLevel* tilemap; 
	
	sf::Vector2i blah; 
	sf::Vector2i worldPos; 
	sf::RenderWindow* window; 
	sf::Font font; 
	sf::Texture texture; 
  Gui::TextureSelection* textSelect; 
	
};

