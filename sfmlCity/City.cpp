#include "City.h"
using namespace std;

//inilization func
void City::initWindow()
{
	this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "test Window", sf::Style::Close | sf::Style::Resize);
	std::cout << "x: " << this->window->getSize().x << "y: " << this->window->getSize().y << std::endl; 
}

void City::initView()
{
	this->camera.setCenter(this->window->getSize().x/2.f, this->window->getSize().y/2.f);
	this->camera.setSize(this->window->getSize().x, this->window->getSize().y) ;
	this->camera = correctRatioView(camera, this->window->getSize().x, this->window->getSize().y); 
	this->window->setView(camera); 
}

bool City::initTileMap()
{
	if (!(this->map.load("tileset.png", sf::Vector2u(32, 32), level, 16, 8)))
		throw("failed to find tileset file");
	else
		return 1; 
}

sf::View City::correctRatioView(sf::View view, int windowWidth, int windowHeight)
{
	float windowRatio = windowWidth / (float)windowHeight;
	float viewRatio = view.getSize().x /(float) view.getSize().y; 
	float posX = 0; 
	float posY = 0; 
	float sizeX = 1; 
	float sizeY = 1; 

	bool horizontalLines = true; 

	if (windowRatio < viewRatio) //stretched too much vertically
	{
		horizontalLines = false; 
	}
	

	if (horizontalLines)
	{
		sizeX = viewRatio/ windowRatio; //amount of width window want to view
		
		posX = (1 - sizeX) / 2.f; //distance from left 
	}
	else
	{
		sizeY= (windowRatio / viewRatio); //amount of height window want to view
		
		posY = (1 - sizeY) / 2.f; //distance from top
	}

	view.setViewport(sf::FloatRect(posX, posY, sizeX, sizeY)); 


	return view; 
}


//constructor/destructor
City::City()
{ 
	
	this->initWindow(); //initializes the window
	this->initView(); // initializes camera
	
	try { //loads the tile map textures and positions
		this->initTileMap();
	}
	catch (const char* msg)
	{
		cerr << msg << endl; //can't find the png file
	}
	
	
}

City::~City()
{
	delete this->window; 
}





//Functions

void City::drawTileMap()
{
	this->window->draw(this->map);
}

void City::pollKeyEvents()
{
	const float deltaTime = this->clock.restart().asSeconds();
	bool cameraMove = true;
	//zoom
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageUp) && camera.getSize().x >= 10)
		camera.zoom(1.f - deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::PageDown) && camera.getSize().x <= 1000)
		camera.zoom(1.f + deltaTime);

	 

	if (cameraMove == true)
	{
		//camera controls
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			camera.move(-0.5f + deltaTime, 0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			camera.move(0.5f + deltaTime, 0);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			camera.move(0, -0.5f + deltaTime);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			camera.move(0, 0.5f + deltaTime);

		/*sf::Vector2f mouse = this->window->mapPixelToCoords(this->mousepos); 
		std::cout << "mouse x: " << mouse.x << "mouse.y" << mouse.y << std::endl; */


		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			const sf::Vector2i mousepos = sf::Mouse::getPosition();

			if (this->mousepos != mousepos)
			{
				sf::Vector2f relativePos1 = this->window->mapPixelToCoords(mousepos); // first mouse click
				sf::Vector2f relativePos2 = this->window->mapPixelToCoords(this->mousepos); // mouse drag
				camera.move(relativePos2.x - relativePos1.x, relativePos2.y - relativePos1.y); //move based on difference 
			}
		}

		this->mousepos = sf::Mouse::getPosition();
	}

}



void City::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
		{
			this->window->close(); 
	    }

		if (this->sfEvent.type == sf::Event::MouseWheelMoved)
		{
			if(camera.getSize().x >= 10 && camera.getSize().x <= 1000)
				camera.zoom(1.f - this->sfEvent.mouseWheel.delta * 0.1f);
			 
			if (camera.getSize().x < 10)
				camera.setSize(10, 10);

			if (camera.getSize().y > 1000)
				camera.setSize(1000, 1000);
		}
		
		if (this->sfEvent.type == sf::Event::Resized)
		{
			camera = correctRatioView(camera, sfEvent.size.width, sfEvent.size.height); //gives ratio method the new width and height of resized window
			std::cout << "Window Width:" << sfEvent.size.width << "Window height:" << sfEvent.size.height << std::endl; 
		}
	}
}

void City::update()
{
	this->pollKeyEvents();
	this->updateSFMLEvents(); 
}

void City::render()
{
	//clears the window
	this->window->clear();
	//draws
	this->drawTileMap(); 
	
	
	//displays the window
	this->window->setView(camera);
	this->window->display(); 
}

void City::run()
{
	while (this->window->isOpen())
	{
		this->update(); 
		
		//std::cout << "x: " << camera.getCenter().x << "y: " << camera.getCenter().y << std::endl;
		
		this->render(); 
		
	}
}


