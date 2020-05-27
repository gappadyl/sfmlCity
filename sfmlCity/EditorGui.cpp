#include "EditorGui.h"


//Constructor/Destructor
EditorGui::EditorGui()
{

}

EditorGui::~EditorGui()
{

}

//Functions
sf::Vector2f EditorGui::getLocation()const
{
	return sf::Vector2f(0, 0); 
}

void EditorGui::update(sf::Vector2i& mousePos, float& dt)
{
	RobertsButton->update(mousePos); 
	RobertSelector->update(mousePos, dt ); 
}

void EditorGui::render(sf::RenderTarget& target)
{
	this->RobertsButton->render(target);
	this->RobertSelector->render(target); 
}
