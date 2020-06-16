#include "EditorMode.h"

//Constructor/Destructor
EditorMode::EditorMode(sf::RenderWindow* window, Camera* view, Population* population, TileMapLevel* level,
	unsigned int* heightMap, unsigned int* widthMap, unsigned int* tileLength,
	bool* hasFocus, float& dt):Mode(window, view, heightMap, widthMap, tileLength, hasFocus), dt(dt)
{
	//Load gui components
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
	
	//initialize the gui
	

	this->window = window; 

	initGui(font, &texture);
	tool = add_Mode; 
}

EditorMode::~EditorMode()
{
	
	delete this->textSelect; 
	delete this->highlighter; 
}

void EditorMode::updateControls(float& dt)
{
	tile_cordinates = sf::Vector2i(worldPos.x / 32, worldPos.y / 32);
	//camera movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		camera->cameraUpdate(dt, true);
	}

	switch (tool)
	{
		case default_Mode:
		//show drop down list
			highlighter->update(this->window); 
			highlighter->outOfBoundsHighlight(tilemap->isCordinateInsideMap(tile_cordinates), sf::Color::Green); 
			std::cout << tilemap->isCordinateInsideMap(tile_cordinates) << std::endl; 
			break; 
		case add_Mode: 
			textSelect->update(worldPos, dt);

			highlighter->update(this->window);
			highlighter->outOfBoundsHighlight(tilemap->isCordinateInsideMap(tile_cordinates), sf::Color::Green);
			//std::cout << "is the cordinate in highlightable" " "+ tilemap->isCordinateInsideMap(tile_cordinates) << std::endl;

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !textSelect->isSelectorActive())
			{
				this->tilemap->addTile(tile_cordinates.x, tile_cordinates.y, 0, textSelect->getTextureSelected(), true, 0);
			}
			break; 

		case delete_Mode:

			break; 

		case move_Mode:

			break; 
	}
}
 void EditorMode::update(float& dt)
{
	
	 locMousePosition = sf::Mouse::getPosition(*window);
	 worldPos = static_cast<sf::Vector2i>((*window).mapPixelToCoords(locMousePosition));

	 updateControls(dt); 
	 

}

 void EditorMode::render(sf::RenderTarget* target)
 {
	 tilemap->render(*target, true); 
	 population->renderPopulation(target);
	 switch (tool)
	 {
	 case default_Mode: 
		 highlighter->render(*target); 
		 break; 
	 case add_Mode:
		 highlighter->render(*target);
		 textSelect->render(*target);
		 break; 

	 case delete_Mode: 
		 break; 
	 case move_Mode:
		 break; 
	 }

	 
	 camera->cameraRender(target);
	 //render button objects and clickable tiles and tile placement cursor 
 }

 void EditorMode::initGui(sf::Font& font, const sf::Texture *textureSheet)
 {
	 this->textSelect = new Gui::TextureSelection(100.f, 100.f, 200.f, 32.f, 32.f, textureSheet, font, "X");
	 this->highlighter = new Gui:: Highlight(this->window, 32, sf::Color::Yellow);
 }