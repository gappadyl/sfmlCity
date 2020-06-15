#include "City.h"

using namespace std;

//inilization func
void City::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "City Simulation", sf::Style::Close | sf::Style::Resize);
	
}

void City::initView()
{
	this->widthMap = 16;
	this->heightMap = 16;
	this->tileLength = 32; 
	
	camera = Camera(this->window, widthMap, heightMap, tileLength); //initialize camera object
	camera.ratioUpdate(window->getSize().x, window->getSize().y); 
	
}

void City::initPopulation()
{
	//initializing texture
	sf::Texture temp;
	temp.loadFromFile("Textures/Player/DinoSprites - vita.png");
	this->textures["PLAYER_IDLE"] = temp;

	this->population = new Population( this->window, textures); 

	 
}

void City::initModes()
{
	currentMode = Game; 
	game = new GameMode(window, &camera, population, levelMap, &heightMap, &widthMap, &tileLength, &bHasFocus); //creates a new GameMode
	editor = new EditorMode(window, &camera, population, levelMap, &heightMap, &widthMap, &tileLength, &bHasFocus, dt); //creates a new Editor Object
}

void City::cleanUp()
{
	std::cout << widthMap << std::endl; 
	delete this->population;
	delete this->window;
	delete this->levelMap;
	delete this->game;
	delete this->editor; 
}
//Constructors/Destructors
City::City()
{

	this->initWindow(); //initializes the window
	this->initView(); // initializes camera
	this->levelMap = new TileMapLevel("test_load.txt"); 
	initPopulation(); 

	initModes(); 
}

City::~City()
{
	cleanUp();
}

//Functions

void City::updateDT()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void City::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close();
		}

		if (this->sfEvent.type == sf::Event::GainedFocus)
		{
			this->bHasFocus = true;
		}

		if (this->sfEvent.type == sf::Event::LostFocus)
		{
				this->bHasFocus = false;
		}

		if (this->sfEvent.type == sf::Event::KeyReleased && sfEvent.key.code == sf::Keyboard::LShift)//change game mode
		{
			if (currentMode == Game)
			{
				currentMode = Editor;
			}
			else if (currentMode == Editor)
			{
				currentMode = Game;
			}
		}

		camera.SFMLCameraEvents(sfEvent, bHasFocus, currentMode); 
		 
		//Maybe we could have a event queue on the game mode object and send it there if it's a Camera move object??
	}
}

void City::update()
{
	
	this->updateSFMLEvents(); 

	
	if (currentMode == Game)
	{
		game->update(dt); 
	}
	else if (currentMode == Editor)
	{//need to change to updating a editor object
		editor->update(dt); 
		
	}
	
	//std::cout << currentMode << std::endl; 
	

}

void City::render()
{
	//clears the window
	this->window->clear();
 
	if (currentMode == Game)
	{
		game->render(window); 
	}
	else if (currentMode == Editor)
	{
		editor->render(window); 
	}



	this->window->display(); 
}

void City::run()
{
	while (this->window->isOpen())
	{//switch statment for different modes
		this->updateDT();
		this->update(); 
		this->render(); 
		//std::cout << dt << std::endl; 
	}
}


