#pragma once
#include <iostream>
#include <sstream>

#include"SFML/window.hpp"
#include"SFML/System.hpp"
#include"SFML/Graphics.hpp"
#include"SFML/Audio.hpp"
#include"SFML/Network.hpp"


enum TileTypes{Default = 0};


class Tile //base class for other tiles
{
	
public:
//Constructor/Destructor
	Tile(int grid_x, int grid_y, float gridSize, const sf::Texture& texture_sheet,const sf::IntRect& rect, bool collision, short type );
	virtual ~Tile();

//Functions
	virtual void render(sf::RenderTarget& target)=0; 
	virtual void update(short type)=0;
//Accesors
	virtual short getType()const; 
	virtual bool isCollidable()const; 
	virtual const sf::Vector2f& getPosition()const; 
	virtual sf::FloatRect getGlobalBounds()const; 
	virtual bool checkCollision(const sf::FloatRect frect)const; 
	virtual std::string getTileAsString()const =0; 
	virtual const bool & getCollision() const = 0; 
	
//Variables


protected:
	//Variables
	bool collision; 
	sf::Sprite tile; 
	short type; 
	sf::Texture texture; 
	sf::IntRect rect; 
	sf::Vector2f position; 



};

