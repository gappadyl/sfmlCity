#include "EditorMode.h"

//Constructor/Destructor
EditorMode::EditorMode(sf::RenderWindow* window, Camera* view, Population* population, TileMapLevel* level,
	unsigned int* heightMap, unsigned int* widthMap, unsigned int* tileLength,
	bool* hasFocus, float& dt):Mode(window, view, heightMap, widthMap, tileLength, hasFocus), dt(dt)
{
	
	if (!font.loadFromFile("Fonts/arial.ttf"))
	{
		std::cout << "Failed to load Fonts/arial.ttf" << std::endl;
	}
	if (!texture.loadFromFile("Textures/background/tileset.png"))
	{
		std::cout << "Failed to load Textures/background/tileset.png" << std::endl;
	}

	this->population = population; 
	this->tilemap = level; 
	
	//initialize the gui, need to send it tilelength size, texture file
	initGui(font, &texture); 
	this->window = window; 
	
}

EditorMode::~EditorMode()
{
	
	delete this->textSelect; 
}

 void EditorMode::update(float& dt)
{
	 camera->cameraUpdate(dt, true);
	 
	 blah = sf::Mouse::getPosition(*window);
	 worldPos =static_cast<sf::Vector2i>( (*window).mapPixelToCoords(blah) );
	 textSelect->update(worldPos, dt); 
	 //gui->update(worldPos, dt); 
	 //if click with mouse
	 worldPos = sf::Vector2i(worldPos.x / 32, worldPos.y/ 32); 
	 if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	 {
		 this->tilemap->addTile(worldPos.x, worldPos.y, 0, textSelect->getTextureSelected(), false, 0); 
	 }
	 //editor gui(mouse cordinates) returns true or false

	 //if nothing to click gui check if there is population to click
	 //if no population then see what mode we are in "build" or "delete"

	 //this is going to check for clicks on map and on grid to pick tile and place them. Editing objecT?
	 //need to check if user wants to write to a file for the new tile map. 
	 //population->updatePopulation(dt); 

}

 void EditorMode::render(sf::RenderTarget* target)
 {
	 tilemap->render(*target, true); 
	 population->renderPopulation(target); 
	 textSelect->render(*target); 
	 camera->cameraRender(target);
	 //render button objects and clickable tiles and tile placement cursor 
 }

 void EditorMode::initGui(sf::Font& font, const sf::Texture *textureSheet)
 {
	 this->textSelect = new Gui::TextureSelection(100.f, 100.f, 200.f, 32.f, 32.f, textureSheet, font, "X");
 }