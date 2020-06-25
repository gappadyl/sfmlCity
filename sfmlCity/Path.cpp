#include "Path.h"

Path::Path()
{

	next = NULL; 
}

Path::Path(sf::Vector2i data)
{
	this->data = data; 
	next = NULL; 
}

Path::~Path()
{
	delete next; 
}


