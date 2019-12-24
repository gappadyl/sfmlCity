#include"tileMap.h"

void tileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();

	states.texture = &this->m_tileset;


	target.draw(this->m_vertices, states);
}

bool tileMap::load(const std::string& tileset, sf::Vector2u tileSize, const int* tiles, unsigned int width, unsigned int height) 
{
		if (!this->m_tileset.loadFromFile(tileset))
		{
			return false;
		}

		this->m_vertices.setPrimitiveType(sf::Quads);
		this->m_vertices.resize(width * height * 4); //indexs of the vertexArray to picture amount


		for (unsigned int w = 0; w < width; w++)//set each vertice position and texture
		{
			for (unsigned int h = 0; h < height; h++)
			{
				int tileNumber = tiles[w + h * width];

				//finding its position in the tileset texture
				int tu = tileNumber % (this->m_tileset.getSize().x / tileSize.x); // tileNumber modulus (texture set pixels / pixels of single tile )
				int tv = tileNumber / (this->m_tileset.getSize().x / tileSize.x);

				//a pointer to the current tile's quad
				sf::Vertex* quad = &this->m_vertices[(w + h * width) * 4];

				quad[0].position = sf::Vector2f(w * tileSize.x, h * tileSize.y);
				quad[1].position = sf::Vector2f((w + 1) * tileSize.x, h * tileSize.y);
				quad[2].position = sf::Vector2f((w + 1) * tileSize.x, (h + 1) * tileSize.y);
				quad[3].position = sf::Vector2f(w * tileSize.x, (h + 1) * tileSize.y);


				quad[0].texCoords = sf::Vector2f(tu * tileSize.x, tv * tileSize.y);
				quad[1].texCoords = sf::Vector2f((tu + 1) * tileSize.x, tv * tileSize.y);
				quad[2].texCoords = sf::Vector2f((tu + 1) * tileSize.x, (tv + 1) * tileSize.y);
				quad[3].texCoords = sf::Vector2f((tu)* tileSize.x, (tv + 1) * tileSize.y);
			}

		}

		return true; 

}
