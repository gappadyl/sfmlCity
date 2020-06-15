#include "EditorMode.h"

//Constructor/Destructor
EditorMode::EditorMode(sf::RenderWindow* window, Camera* view, Population* population, TileMapLevel* level,
	unsigned int* heightMap, unsigned int* widthMap, unsigned int* tileLength,
	bool* hasFocus, float& dt):Mode(window, view, heightMap, widthMap, tileLength, hasFocus), dt(dt)
{
	//Load gui components
	if (!font.loadFromFile("Fonts/arial.ttf"))
	{
		std::cout << "oops" << std::endl;
	}
	if (!texture.loadFromFile("Textures/background/tileset.png"))
	{
		std::cout << "oops" << std::endl;
	}

	this->population = population; 
	this->tilemap = level; 
	
	//initialize the gui
	initGui(font, &texture); 

	this->window = window; 
	
	tool = add_Mode; 
}

EditorMode::~EditorMode()
{
	
	delete this->textSelect; 
}

void EditorMode::updateControls(float& dt)
{
	//camera movement
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		camera->cameraUpdate(dt, true);
	}

	switch (tool)
	{
		case add_Mode: 
			textSelect->update(worldPos, dt);

			worldPos = sf::Vector2i(worldPos.x / 32, worldPos.y / 32);
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !textSelect->isSelectorActive())
			{
				this->tilemap->addTile(worldPos.x, worldPos.y, 0, textSelect->getTextureSelected(), true, 0);
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
	 case add_Mode:
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
 }