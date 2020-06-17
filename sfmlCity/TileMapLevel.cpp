#include "TileMapLevel.h"
//Constructor/Destructor
TileMapLevel::TileMapLevel(int width, int height, float gridSize, std::string texture_file)//if no loaded file
{
	//tile dimensions
	this->gridSizeF = gridSize; 
	this->gridSizeI = static_cast<int>(gridSize); 
	
	this->textureFile = texture_file; 

	//dimensions of Map
	this->maxSizeWorldGrid.x = width; 
	this->maxSizeWorldGrid.y = height; 

	//max horizontal and vertical float length in pixels
	this->maxSizeWorldF.x = gridSize * static_cast<float>(width); 
	this->maxSizeWorldF.y = gridSize * static_cast<float>(height);

	//sets all to 0
	layers = 1; 
	fromX = 0; 
	toX = 0; 
	fromY = 0; 
	toY = 0; 

	currentLayer = 0; 
	//set map to appropriate size
	resize(); 

	if(!texture_sheet.loadFromFile(textureFile))
		std::cout << "ERROR can't find texture file" << std::endl; 


	collisionBox.setSize(sf::Vector2f(gridSize, gridSize)); 
	collisionBox.setFillColor(sf::Color::Transparent); 
	collisionBox.setOutlineThickness(1.f);
	collisionBox.setOutlineColor(sf::Color::Red); 
}

TileMapLevel::TileMapLevel(const std::string file_name)//load from file
{
	fromX = 0; 
	toX = 0; 
	fromY = 0; 
	toY = 0; 

	currentLayer = 0; //starts on first layer

	load_from_file(file_name); 

	collisionBox.setSize(sf::Vector2f(gridSizeF-1, gridSizeF-1 ) );
	collisionBox.setFillColor(sf::Color::Transparent);
	collisionBox.setOutlineThickness(1.f); 
	collisionBox.setOutlineColor(sf::Color::Red); 
	

}

TileMapLevel::~TileMapLevel()
{
	clear(); //deletes all the tiles
}


//Functions
void TileMapLevel::load_from_file(const std::string file)
{
	std::ifstream file_in; 

	file_in.open(file); 
	
	if (file_in.is_open())
	{
		//map dimension
		sf::Vector2i size; 
		bool collision = false;
		int layers = 0;
		int gridSize; 

		//Rect starting cordinates
		int trX = 0; 
		int trY = 0; 

		//position on map
		int x = 0;
		int y = 0;
		int z = 0;

		short type = 0;

		std::string texture_file = "";

		file_in >> size.x >> size.y >> gridSize >> layers >> texture_file; 
		//reads from a file values [size of map , tile size , z axis, texture file]

		//sets tile size
		gridSizeF = static_cast<float>(gridSize); 
		gridSizeI = gridSize; 

		//amounts of layers set
		this->layers = layers; 

		//pixel width and height of map
		maxSizeWorldF.x = static_cast<float>(gridSize * size.x); 
		maxSizeWorldF.y = static_cast<float>(gridSize * size.y);

		//width and height of map
		maxSizeWorldGrid.x = size.x; 
		maxSizeWorldGrid.y = size.y; 
		
		this->clear(); 
		this->resize(); 

		textureFile = texture_file; 

		if (!texture_sheet.loadFromFile(textureFile))
			std::cout << "[ERROR] can't load file" << std::endl; 

		while (file_in >> x >> y >> z >> type) //while more tiles to add [cordinates]
		{
			if (type == Default)//check type
			{
				file_in >> trX >> trY >> collision; //get texture cordinates and collision
				
				map[x][y][z].push_back(
					new RegularTile(x, y, gridSizeI, texture_sheet, sf::IntRect(trX, trY, gridSizeI, gridSizeI), collision, type)
					); //pushes a Regular Tile onto the Vector at cordinates
				 

			}
			
		}

	}
	else
	{
		std::cout << "couldnt load from filename" << std::endl;
	}

	file_in.close();

}

void TileMapLevel::save_to_file(const std::string file)
{//Saves Tile map to file
	// mapLength mapheight
	//tile dimension
	//layers
	//texture file

	// x y z type
	//textrect x textrect y collision

	std::ofstream file_out; 

	file_out.open(file); 
	

	if (file_out.is_open())
	{
		file_out << maxSizeWorldGrid.x << " " << maxSizeWorldGrid.y << "\n" <<
		 gridSizeI << "\n" << layers << "\n" <<
		 textureFile << std::endl; 

		for (int x = 0; x < map.size(); x++)
		{
			for (int y = 0; y < map[x].size(); y++)
			{
				for (int z = 0; z < map[x][y].size(); z++)
				{
					if (!this->map[x][y][z].empty())
					{
						for (size_t w = 0; w < map[x][y][z].size(); w++)
						{
							file_out << x << " " << y << " " << z << " " << map[x][y][z][w]->getTileAsString(); 
						}
					}
				}
			}
		}
	}

	file_out.close(); 
}

void TileMapLevel::gridBoarderCollisionCheck(Entity* entity) //need to change so that it stays in little box
{
	//World bounds check
	sf::RectangleShape hitBox = entity->getHitBox(); 
	
	if (hitBox.getPosition().x + entity->getHitBoxDimensions().x > maxSizeWorldF.x)
	{
		
		entity->setPosition(sf::Vector2f(maxSizeWorldF.x - entity->getHitBoxDimensions().x, hitBox.getPosition().y));
		entity->stopVelocityX(); 
	}
	else if (hitBox.getPosition().x < 0)
	{
		
		entity->setPosition(sf::Vector2f(0, hitBox.getPosition().y)); 
		entity->stopVelocityX(); 
	}

	if (hitBox.getPosition().y + entity->getHitBoxDimensions().y > maxSizeWorldF.y)
	{
		if (hitBox.getPosition().x < 0)
		{//fixes diagnol movement ignoring bounds
			entity->setPosition(sf::Vector2f(0, maxSizeWorldF.y - entity->getHitBoxDimensions().y));
			entity->stopVelocityX();
			entity->stopVelocityY();
		}
		else if (hitBox.getPosition().x + entity->getHitBoxDimensions().x > maxSizeWorldF.x)
		{
			entity->setPosition(sf::Vector2f(maxSizeWorldF.x - entity->getHitBoxDimensions().x, maxSizeWorldF.y - entity->getHitBoxDimensions().y));
			entity->stopVelocityX();
			entity->stopVelocityY();
		}
		else
		{
			entity->setPosition(sf::Vector2f(hitBox.getPosition().x, maxSizeWorldF.y - entity->getHitBoxDimensions().y));
			entity->stopVelocityY();
		}

	}
	else if (hitBox.getPosition().y < 0)
	{
		
		if (hitBox.getPosition().x < 0)
		{
			entity->setPosition(sf::Vector2f(0, 0));
			entity->stopVelocityX();
			entity->stopVelocityY();
		}
		else if (hitBox.getPosition().x + entity->getHitBoxDimensions().x > maxSizeWorldF.x)
		{
			entity->setPosition(sf::Vector2f(maxSizeWorldF.x - entity->getHitBoxDimensions().x, 0));
			entity->stopVelocityX();
			entity->stopVelocityY();
		}
		else 
		{
			entity->setPosition(sf::Vector2f(hitBox.getPosition().x, 0));
			entity->stopVelocityY();

		}

		
	}

	
} // might have to change

void TileMapLevel::clear()
{//clears map

	if (!map.empty())
	{ 
		for (int x = 0; x < map.size(); x++)
		{
			for (int y = 0; y < map[x].size(); y++)
			{
				for (int z = 0; z < map[x][y].size(); z++)
				{
					for (size_t w = 0; w < map[x][y][z].size(); w++)
					{
						delete map[x][y][z][w];
						map[x][y][z][w] = NULL;
					}
					map[x][y][z].clear();
				}
				map[x][y].clear();
			}

			map[x].clear();
		}
		map.clear();
	}
}

void TileMapLevel::resize()
{//set map to appropriate size
	
	if (maxSizeWorldGrid.x > 0 && maxSizeWorldGrid.y > 0)//map dimensions bigger than 0
	{
		this->map.resize(maxSizeWorldGrid.x, std::vector < std::vector < std::vector <Tile*> > >());

		for (int x = 0; x < maxSizeWorldGrid.x; x++)
		{
			map[x].resize(maxSizeWorldGrid.y, std::vector<std::vector<Tile*> >());

			for (int y = 0; y < maxSizeWorldGrid.y; y++)
			{
				map[x][y].resize(layers, std::vector<Tile*>());
			}
		}
	}
	else
	{
		std::cout << "the size of map is less than 1" << std::endl; 
	}
}

bool TileMapLevel::isTileEmpty(const int cord_x, const int cord_y, const int cord_z)
{
	if (cord_x >= 0 && cord_x <= maxSizeWorldGrid.x //checking if point clicked is in bounds of map
		&& cord_y >= 0 && cord_y <= maxSizeWorldGrid.y 
		&& cord_z >= 0 && cord_z < this->layers)
	{
		return map[cord_x][cord_y][cord_z].empty(); 
	}


	return false; 
		
}
void TileMapLevel::update()
{

}

void TileMapLevel::render(sf::RenderTarget& target, const bool showCollision)//need to edit to handle edit and game differently
{//draw each tile sprite

	for (int x = 0; x < map.size(); x++)
	{
		for (int y = 0; y < map[x].size(); y++)
		{
			for (size_t w = 0; w < map[x][y][0].size(); w++)
			{
				map[x][y][currentLayer][w]->render(target); 
				//check if Tile is Editable Tile type
				if (showCollision)
				{
					if (map[x][y][currentLayer][w]->getCollision()) //render collision box
					{
						collisionBox.setPosition(map[x][y][currentLayer][w]->getPosition()); 
						target.draw(collisionBox); 
					}
				}
				
			}
		}
	}
}
bool TileMapLevel::isCordinateInsideMap(sf::Vector2i cordinate)
{
	if (cordinate.x >= 0 && cordinate.x < maxSizeWorldGrid.x * 32 && (cordinate.y >= 0 && cordinate.y < maxSizeWorldGrid.y* 32))
	{
		return true; 
	}

	return false; 
}

void TileMapLevel::addTile(float cord_x, float cord_y, float cord_z, sf::IntRect rectangle, bool collision, short type)
{//add tiles
	sf::Vector2i cordinateVector = sf::Vector2i(cord_x / 32, cord_y / 32); 
	 
	if (isCordinateInsideMap(sf::Vector2i(cord_x,cord_y)) )
	{//checks if cordinates are within map size
		std::cout << "cord_x " << cord_x << " cord_y " << cord_y <<  std::endl; 

		if (isTileEmpty(cordinateVector.x, cordinateVector.y, cord_z))
		{
			map[cordinateVector.x][cordinateVector.y][cord_z].push_back(new RegularTile(cordinateVector.x, cordinateVector.y, gridSizeI, texture_sheet, rectangle, collision, type));
		}
		else
		{
			map[cordinateVector.x][cordinateVector.y][cord_z].pop_back();
			map[cordinateVector.x][cordinateVector.y][cord_z].push_back(new RegularTile(cordinateVector.x, cordinateVector.y, gridSizeI, texture_sheet, rectangle, collision, type));
		}
	}
		//new RegularTile(x, y, gridSizeI, texture_sheet, sf::IntRect(trX, trY, gridSizeI, gridSizeI), collision, type)
}
void TileMapLevel::removeTile(float cord_x, float cord_y)
{//remove Tile at coridnates

}