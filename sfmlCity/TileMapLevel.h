#pragma once
#include "RegularTile.h"
#include <vector>
#include "person.h"
#include <fstream>

class TileMapLevel
{

public:
	//Constructor/Destructor
	TileMapLevel(int width, int height, float gridSize, std::string texture_file);
	TileMapLevel(const std::string file_name); 
	~TileMapLevel(); 

	//Functions
	void load_from_file(const std::string); //Loads all the tiles from a file
	void save_to_file(const std::string); //saves the current tiles to a file

	void gridBoarderCollisionCheck(Entity* entity); //checks if the entity give is colliding with grid

	void update(); 
	void render(sf::RenderTarget& target,const bool showCollision); //renders all of the tiles
	//need to add another render function or too this current render function

	//[EDIT MODE] need to implement or think about states
	void addTile(float cord_x, float cord_y, float cord_z, sf::IntRect rectangle,  bool collision, short type = -1);
	void removeTile(float cord_x , float cord_y); 
	bool isTileEmpty(const int cord_x, const int cord_y, const int cord_z);
	bool isCordinateInsideMap(sf::Vector2i cordinate); 
	//isTileVisible
	//isTileHitBox

private:
	//Functions
	void clear(); //clear map
	void resize(); 
	//Variables

	//map vector variables that holds each renderable sprite
	std::vector< std::vector <std::vector <std::vector <Tile*> > > > map; 

	//tileset and file name for  cordinate instructions. 
	sf::Texture texture_sheet; 
	std::string textureFile; 
	
	int fromX, toX, fromY, toY; //deciding Texture Rect for each square

	//gridSize in float and Int
	float gridSizeF; 
	int gridSizeI; 
	//how many Z values layers
	int layers;
	int currentLayer; 

	//max vertical and horizontal float size of world. max dimensions of tile
	sf::Vector2f maxSizeWorldF; 
	sf::Vector2i maxSizeWorldGrid;

	sf::RectangleShape collisionBox; 

};

