#pragma once
#include "Mode.h"
#include "Population.h"
#include "TileMapLevel.h"
#include "EditorGui.h"
enum tools { default_Mode = 0, add_Mode = 1, delete_Mode = 2, move_Mode = 3 }; 
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
	void updateControls(float& dt);

private:
	//Initializers
	void initGui(sf::Font& font, const sf::Texture* textureSheet);
	 
	float& dt; 
	Population* population; //keeps a reference to population & tilemap
	TileMapLevel* tilemap; 
	tools tool;
	sf::Vector2i locMousePosition; 
	sf::Vector2i worldPos; 
	sf::RenderWindow* window; 
	sf::Font font; 
	sf::Texture texture; 
  EditorGui::TextureSelection* textSelect; 
	
};

