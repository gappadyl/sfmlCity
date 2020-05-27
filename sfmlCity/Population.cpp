#include "Population.h"


//Constructors/Destructors
Population::Population( sf::RenderTarget* window, std::map<std::string, sf::Texture> textures)
{
	
	this->target = window; 
	this->textures = textures; 
	
	setUpPlayer(this->textures);
}

Population::Population()
{
	std::cout << "setting Robert to null" << std::endl; 
	Robert = NULL; 
	
	target = NULL; 
}

Population::~Population()
{
	//std::cout << Robert << std::endl; 
	delete this->Robert; 
	
	 
}

//initializer Functions
void Population::setUpPlayer(std::map<std::string, sf::Texture>& textures)
{
	std::cout << "player set up" << std::endl; 
		this->Robert = new Person(50.f, 50.f, textures["PLAYER_IDLE"] ); 

		std::cout << Robert << std::endl; 
}

//Functions
void Population::updatePopulation(float& dt)
{
	this->Robert->update(dt); 

}

void Population::renderPopulation(sf::RenderTarget* window)
{
	try { 
		this->Robert->render(window);
		}
		catch (const char* msg)
		{
		std::cerr << msg << std::endl;
		}
}
//Accesors
float Population::getHappy()
{
	return 0.f; 
}

Person* Population::getPlayer()const
{
	if (Robert)
	{
		return Robert;
	}
}