#include "City.h"

int main()
{
	
	City city;

	city.run(); 

	return 0;
}



/*
	DYLAN IDEA FOR HOW TO RENDER MAP:

	THE MAP WILL BE A VISUAL REPRESENTIATION OF A 2D ARRAY USING INTEGERS TO REPRESENT DIFFERENT TEXTURES/SPRITES PRESENT IN OUR CITY
	IE:DEFAULT GRASS TILE WILL BE 0, ROADS 1, ETC.

	WE CAN USE THIS ARRAY TO CALLCULATE ONLY WHAT NEEDS TO BE RENDERED DUE TO ZOOMING AND CAMERA MOVEMENT
	OUR NPCS LIKE CARS AND PERHAPS PEOPLE CAN ALSO USE THIS ARRAY TO TRAVERSE THE CITY
	I SUPPOSE WE WILL ALSO HAVE TO CREATE AN ARRAY FOR OUR CITIZENS AS THEY WILL SIMPLY BE OVERLAYED ONTOP OF THE MAP
	AND WILL NOT BE A TILE THEMSELVES

	WE CAN ADD A GUI SOMEWHERE ON THE SCREEN, MAYBE BOTTOM LIKE MINECRAFT TO ALLOW USER TO CREATE/DESTROY ROADS, ADD BUILDINGS, ETC.
	*/
