#include "Gui.h"
//Constructor/Destructor


Gui::~Gui()
{
	
}



Gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text, unsigned int textSize,
	sf::Color IdleColor, sf::Color hoverColor, sf::Color activeColor,
	sf::Color text_idle_color, sf::Color text_hover_color,
	sf::Color text_active_color, sf::Color outline_hover_color,
	sf::Color outline_active_color, sf::Color outline_idle_color, short unsigned id, bool clickable)
{
	//sets colors
	this->idleColor = IdleColor; 
	this->hoverColor = hoverColor; 
	this->activeColor = activeColor; 
	
	this->text_idle_color = text_idle_color; 
	this->text_hover_color = text_hover_color; 
	this->text_active_color = text_active_color; 

	this->outlineIdleColor = outline_idle_color;
	this->outlineHoverColor = outline_hover_color;
	this->outlineActiveColor = outline_active_color; 
	
	

	//creates visble button 
	button = sf::RectangleShape(sf::Vector2f(width, height));
	button.setPosition(x, y);
	button.setFillColor(idleColor);
	button.setOutlineColor(outlineIdleColor);

	//sets font & text
	this->font = font;
	this->text.setString(text);
	this->text.setCharacterSize(textSize);
	this->text.setFont(*this->font);
	this->text.setFillColor(this->text_idle_color);
	this->text.setPosition(button.getPosition().x + button.getGlobalBounds().width / 2.f -
		this->text.getGlobalBounds().width /2.f, button.getPosition().y); 
	

	this->id = id; 
	this->isClickable = clickable; 
	this->buttonState = idle_state; 
}

Gui::Button::~Button()
{

}

std::string Gui::Button::returnText() const
{
	return text.getString();
}

bool Gui::Button::isActive() const
{
	if (this->buttonState == active_state)
	{
		return true;
	}

	return false; 
}

short unsigned Gui::Button::getId() const
{
	return this->id; 
}

void Gui::Button::setText(const std::string newText)
{
	text.setString(newText); 
}

void Gui::Button::setId(const short unsigned Id)
{
	this->id = Id; 
}
bool Gui::Button::isHover()const
{
	if (buttonState == hover_state)
		return true; 

return false; 
}
void Gui::Button::update(const sf::Vector2i& mousePosition)
{//want to check if mouseposition is in button, check if it clicks, 
	buttonState = idle_state; 
	std::cout << buttonState << std::endl;
	
	if (button.getGlobalBounds().contains(static_cast<sf::Vector2f> (mousePosition)) )
	{
		std::cout << "button contains mouse" << std::endl; 
		if (isClickable)
		{
			std::cout << "button is clickable" << std::endl;
			buttonState = hover_state; 

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				std::cout << "clicking " << std::endl; 
				buttonState = active_state; 
			}
		}
	}
	std::cout << buttonState << std::endl; 
	switch (buttonState)
	{
	case idle_state:
		button.setFillColor(idleColor);
		button.setOutlineColor(outlineIdleColor);
		text.setFillColor(text_idle_color);
		break;

	case hover_state:
		button.setFillColor(hoverColor);
		button.setOutlineColor(outlineHoverColor);
		text.setFillColor(text_hover_color);
		break;

	case active_state:
		std::cout << "active" << std::endl;
		button.setFillColor(activeColor);
		button.setOutlineColor(outlineActiveColor);
		text.setFillColor(text_active_color);
		break;

	default:
		this->button.setFillColor(sf::Color::Red);
		this->button.setFillColor(sf::Color::Blue);
		this->button.setOutlineColor(sf::Color::Green);
		break;


	}

}

void Gui::Button::render(sf::RenderTarget& target)
{
	//std::cout << "trying to render" << std::endl;
	target.draw(button); 
	target.draw(text); 
}



Gui::TextureSelection::TextureSelection(float x, float y, float width, float height, float gridSize,
	const sf::Texture* sheet, sf::Font& font, std::string text) :maxKeyTime(1.f), keyTime(0.f)
{
	hideButton = new Gui::Button(x, y, 15.0f, 15.0f, &font, text, 13, sf::Color::Red, sf::Color::Blue, sf::Color::Green,
		sf::Color::Black, sf::Color::Red, sf::Color::Black, sf::Color::Red, sf::Color::Blue, sf::Color::Green, 0, true); 
	hidden = false;//visible
	this->isActive = false; //not Active

	this->gridSize = gridSize; 
	float offset = gridSize; 
	//set selectorBody
	selectorBody.setFillColor(sf::Color::Red); 
	selectorBody.setPosition(x + offset, y); 
	selectorBody.setOutlineThickness(1.0f); 
	selectorBody.setOutlineColor(sf::Color::Red); 
	selectorBody.setSize(sf::Vector2f(width, height)); 

	
	 //set sprite for texture sheet
	textureSheet.setTexture(*sheet); 
	textureSheet.setPosition(x+gridSize, y); 
	
	//check that texturesheet is contained in selectorBody
	if (textureSheet.getGlobalBounds().width > selectorBody.getGlobalBounds().width)
	{
		textureSheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(selectorBody.getGlobalBounds().width), static_cast<int> (textureSheet.getGlobalBounds().height ))); 
	}
	if (textureSheet.getGlobalBounds().height > selectorBody.getGlobalBounds().height)
	{
		textureSheet.setTextureRect(sf::IntRect(0, 0, static_cast<int>(textureSheet.getGlobalBounds().width), static_cast<int>(selectorBody.getGlobalBounds().height))); 
	}

	
	//set up selector
	selector.setSize(sf::Vector2f(gridSize, gridSize) ); 
	selector.setPosition(x + offset, y); 
	selector.setFillColor(sf::Color::Transparent); 
	selector.setOutlineColor(sf::Color::Green); 
	selector.setOutlineThickness(1.f); 

	textureRect.width = static_cast<int>(gridSize); 
	textureRect.height = static_cast<int>(gridSize); 

	
}

Gui::TextureSelection::~TextureSelection()
{
	delete this->hideButton; 
}

const bool& Gui::TextureSelection::isHidden() const 
{//returns true if hidden
	return this->hidden;
}

const bool& Gui::TextureSelection::isSelectorActive() const
{//returns true if active
	return this->isActive; 
}



const sf::IntRect& Gui::TextureSelection::getTextureSelected() 
{//returns the Texture IntRect
	return textureRect; 
}

const bool Gui::TextureSelection::getKeyTime()
{//returns true if enough delta time has happened
	if (keyTime > maxKeyTime)
	{
		keyTime = 0.f; //reset Time
		return true; 
		
	}

	return false;
}

void Gui::TextureSelection::updateKeyTime(const float& dt)
{
	if (keyTime < maxKeyTime)
	{

		this->keyTime += 10.f* dt;
	}
}

void Gui::TextureSelection::update(sf::Vector2i& mousePosition, const float& dt)
{//in work
	updateKeyTime(dt); 
	hideButton->update(mousePosition); 

	if (hideButton->isActive() && getKeyTime())
	{//if The button has been pressed and enough time has passed
		hidden = !hidden; 
		std::cout << "switch hidden" << std::endl; 
	}
	
	isActive = false;

	if (!hidden)
	{//if visible
		
		
		if (selectorBody.getGlobalBounds().contains(static_cast<sf::Vector2f> (mousePosition)) )
		{//if the selectorbody has the
			isActive = true; 
			std::cout << "inside selector" << std::endl; 
			
			//want to put 
				mousPosGrid.x = static_cast<int>(mousePosition.x - selectorBody.getPosition().x) / static_cast<unsigned> (gridSize);
				mousPosGrid.y = static_cast<int>(mousePosition.y - selectorBody.getPosition().y) / static_cast<unsigned> (gridSize);

				selector.setPosition(selectorBody.getPosition().x + mousPosGrid.x *gridSize, 
									  selectorBody.getPosition().y+ (mousPosGrid.y*gridSize ));
			//don't want to divide and get a negative row and column 
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->selectorBody.getPosition().x);
					this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->selectorBody.getPosition().y);
				}
				

		}
		


	}
	
	if (hideButton->isHover() || hideButton->isActive())
	{
		isActive = true;
	}

	//want to check if visible

	//if visible check if mouse in included in the selectorbox->probably want to put in into world cordinates

	//then we want to calculate mousPosGrid -> some math (distance to right of selectorbox)/gridsize -<probabily going to round down because it's casting to int. row-col

	//then want to set the selector position to the mousPosGrid -do some math row column of mousePosGrid, add the position of selector and multiply by gridSize. 




}

void Gui::TextureSelection::render(sf::RenderTarget& target)
{
	hideButton->render(target); 
	if (!hidden)
	{
		
		target.draw(selectorBody); 
		target.draw(textureSheet); 
		target.draw(selector); 
		
	}

}

void Gui::TextureSelection::select()
{


}

Gui::Gui()
{

	
	
	
	

		/*float x, float y, float width, float height, float gridSize,
		const sf::Texture* sheet, sf::Font& font, std::string text) :maxKeyTime(1.f), keyTime(0.f)*/
}
