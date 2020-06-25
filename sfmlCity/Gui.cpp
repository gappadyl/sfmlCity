#include "Gui.h"
//Constructor/Destructor


Gui::~Gui()
{
	
}



Gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string text,  unsigned int textSize,
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
	this->is_clicked = false; 
}
Gui::Button::Button(float x, float y, float width, float height,
	sf::Font* font, std::string true_text,std::string false_text,  unsigned int textSize,
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
	this->true_text = true_text; 
	this->false_text = false_text; 
	this->font = font;
	this->text.setString(false_text);
	this->text.setCharacterSize(textSize);
	this->text.setFont(*this->font);
	this->text.setFillColor(this->text_idle_color);
	this->text.setPosition(button.getPosition().x + button.getGlobalBounds().width / 2.f -
		this->text.getGlobalBounds().width / 2.f, button.getPosition().y);


	this->id = id;
	this->isClickable = clickable;
	this->buttonState = idle_state;
	this->is_clicked = false;
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
std::string Gui::Button::getTrueText() const
{
	return this->true_text; 

}
std::string Gui::Button::getFalseText()const
{
	return this->false_text;
}
bool Gui::Button::clickedStatus()const
{
	return this->is_clicked; 
}

void Gui::Button::moveButton(float x_Dif, float y_Dif)
{
	button.move(sf::Vector2f(x_Dif, y_Dif)); 
	text.move(sf::Vector2f(x_Dif, y_Dif)); 
}

void Gui::Button::setText(const std::string newText)
{
	text.setString(newText); 
	this->text.setPosition(button.getPosition().x + button.getGlobalBounds().width / 2.f -
		this->text.getGlobalBounds().width / 2.f, button.getPosition().y);
}
void Gui::Button::clicked()
{
	is_clicked = !is_clicked; 
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
	const sf::Texture* sheet, sf::Font& font, std::string text, sf::RenderWindow* window):maxKeyTime(1.f), keyTime(0.f)
{
	hideButton = new Gui::Button(x, y, 15.0f, 15.0f, &font,"+",text,   13, sf::Color::Red, sf::Color::Blue, sf::Color::Green,
		sf::Color::Black, sf::Color::Red, sf::Color::Black, sf::Color::Red, sf::Color::Blue, sf::Color::Green, 0, true) ; 

	pinButton = new Gui::Button(x+ 15.0f, y, 15.0f, 15.0f, &font, "o", "i", 13, sf::Color::Yellow, sf::Color::Blue, sf::Color::Green,
		sf::Color::Black, sf::Color::Yellow, sf::Color::Black, sf::Color::Yellow, sf::Color::Blue, sf::Color::Green, 1, true);

	buttonVector.push_back(pinButton); 
	buttonVector.push_back(hideButton); 

	hidden = false;//visible
	move = false; 
	selectorIsVisible = false; 
	is_moving = false; 
	this->isActive = false; //not Active
	this->window = window; 
	this->gridSize = gridSize; 
	float offset = gridSize; 

	//set selectorBody
	selectorBody.setFillColor(sf::Color::Red); 
	selectorBody.setPosition(x + offset, y); 
	selectorBody.setOutlineThickness(1.0f); 
	selectorBody.setOutlineColor(sf::Color::Green); 
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

const bool& Gui::TextureSelection::isMoveable() const
{//returns if moveable
	return this->move; 
}

const bool& Gui::TextureSelection::isSelectorActive() const
{//returns true if active
	return this->isActive; 
}

const bool& Gui::TextureSelection::isMoving() const
{
	return is_moving; 
}


const bool& Gui::TextureSelection::isButtonActive() const
{
	for (Gui::Button* button : buttonVector)
	{
		if (button->isActive() || button->isHover())
		{
			return true; 
		}
	}

	return false; 
}



const sf::IntRect& Gui::TextureSelection::getTextureSelected() 
{//returns the Texture IntRect
	return textureRect; 
}

const bool Gui::TextureSelection::getKeyTime()
{//returns true if enough delta time has happened
	if (keyTime > maxKeyTime)
	{
		keyTime = 0.f; 
		return true; 
		
	}

	return false;
}

//Selector functions


void Gui::TextureSelection::highlightSelector(const bool& move, sf::Color new_color)
{//if selector is moving, change the bodies outline color
	if (move)
	{
		selectorBody.setOutlineColor(new_color); 
	}
	else
	{
		selectorBody.setOutlineColor(sf::Color::Transparent); 
	}
}

void Gui::TextureSelection::moveSelector(float x_Dif, float y_Dif)
{
	pinButton->moveButton(x_Dif, y_Dif);
	hideButton->moveButton(x_Dif, y_Dif);
	selectorBody.move(sf::Vector2f(x_Dif, y_Dif));
	textureSheet.move(sf::Vector2f(x_Dif, y_Dif));
}

void Gui::TextureSelection::selectorSetVisible(bool is_visible)
{
	selectorIsVisible = is_visible; 
}

//update functions
void Gui::TextureSelection::updateKeyTime(const float& dt)
{
	if (keyTime < maxKeyTime)
	{

		this->keyTime += 10.f* dt;
	}
}
void Gui::TextureSelection::updateButtons(sf::Vector2i& mousePosition)
{
	for (Gui::Button* button : buttonVector)
	{
		button->update(mousePosition); 

		if (button->isActive() && getKeyTime())
		{
			button->clicked(); 
			
			if (button->clickedStatus())
			{
				button->setText(button->getTrueText()); 
			}
			else
			{
				button->setText(button->getFalseText());
			}
		}

		switch (button->getId())
		{
		case 0://hidden id
			hidden = button->clickedStatus();
			break; 
		case 1://pin id
			move = button->clickedStatus(); 
			break; 


		}
	}
}

void Gui::TextureSelection::update(sf::Vector2i& mousePosition, const float& dt)
{
	//update keytime
	updateKeyTime(dt); 
	//checks if TextureSelection should be highlighted
	highlightSelector(is_moving, sf::Color::Cyan);

	sf::RectangleShape body_check = selectorBody;//bug causing outline thickness to affect selector box
	body_check.setOutlineThickness(0.0);

	updateButtons(mousePosition);

	isActive = false;

	if (!hidden)
	{//if visible
		
		if (move)
		{//check if moveable
			
			if (body_check.getGlobalBounds().contains(static_cast<sf::Vector2f> (mousePosition)))
			{//checks if player starts moving
				isActive = true; 

				highlightSelector(true, sf::Color::Green);
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					const sf::Vector2i mousePos2 = sf::Mouse::getPosition(); //clicked position

					if (mousePos2 != mousePos)
					{
						sf::Vector2f relativePos1 = window->mapPixelToCoords(mousePos);
						sf::Vector2f relativePos2 = window->mapPixelToCoords(mousePos2);

						moveSelector((relativePos2.x - relativePos1.x), (relativePos2.y - relativePos1.y));

						is_moving = true; 
					}

					highlightSelector(is_moving, sf::Color::Cyan);
				}
				
			}
			else if(is_moving)
			{//checks if being moved

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					const sf::Vector2i mousePos2 = sf::Mouse::getPosition(); //clicked position

					if (mousePos2 != mousePos)
					{
						sf::Vector2f relativePos1 = window->mapPixelToCoords(mousePos);
						sf::Vector2f relativePos2 = window->mapPixelToCoords(mousePos2);
						moveSelector((relativePos2.x - relativePos1.x), (relativePos2.y - relativePos1.y));
						
					}
				}
				else
				{
					is_moving = false; 
				}
			}

		}
		else if (body_check.getGlobalBounds().contains(static_cast<sf::Vector2f> (mousePosition)) )
		{//if not moveable, choose objects
			isActive = true; 
			std::cout << "inside selector" << std::endl; 

				mousPosGrid.x = static_cast<int>(mousePosition.x - selectorBody.getPosition().x) / static_cast<unsigned> (gridSize);
				mousPosGrid.y = static_cast<int>(mousePosition.y - selectorBody.getPosition().y) / static_cast<unsigned> (gridSize);
				std::cout << mousPosGrid.y << std::endl; 
				selector.setPosition(selectorBody.getPosition().x + mousPosGrid.x *gridSize, selectorBody.getPosition().y+ (mousPosGrid.y*gridSize ));
			
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					this->textureRect.left = static_cast<int>(this->selector.getPosition().x - this->selectorBody.getPosition().x);
					this->textureRect.top = static_cast<int>(this->selector.getPosition().y - this->selectorBody.getPosition().y);
				}
			
		}

	}

	mousePos = sf::Mouse::getPosition(); 
}
//render
void Gui::TextureSelection::render(sf::RenderTarget& target)
{
	hideButton->render(target); 
	pinButton->render(target); 

	if (!hidden)
	{
		
		target.draw(selectorBody); 
		target.draw(textureSheet); 
		if (selectorIsVisible)
		{
			target.draw(selector);
		}
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

//Highlight class
Gui::Highlight::Highlight(sf::RenderWindow* window, int tileSize, sf::Color color)
{
	tile_Size = tileSize; 
	if (window != nullptr)
	{
		mpos = sf::Mouse::getPosition(*window);
		int x = round((-window->mapPixelToCoords(mpos) + sf::Vector2f(tile_Size / 2, tile_Size / 2)).x / tile_Size);
		int y = round((-window->mapPixelToCoords(mpos) + sf::Vector2f(tile_Size / 2, tile_Size / 2)).y / tile_Size);
	}
	outlineColor = color; 
	highlight = sf::RectangleShape(); 
	highlight.setOrigin(x * tile_Size, y * tile_Size);
	highlight.setSize(sf::Vector2f(tile_Size, tile_Size));
	highlight.setOutlineColor(color);
	highlight.setOutlineThickness(1);
	highlight.setFillColor(sf::Color::Transparent);
}

Gui::Highlight::~Highlight()
{

}

void Gui::Highlight::render(sf::RenderTarget& target)
{
	if (visible)
	{
		target.draw(highlight);
	}
}
void::Gui::Highlight::outOfBoundsHighlight(const bool inBounds, sf::Color new_color)
{
	highlight.setOutlineColor(outlineColor); 

	if (!inBounds)
	{
		
		highlight.setOutlineColor(new_color);
	}
	

}
void Gui::Highlight::update(sf::RenderWindow* target)
{
	mpos = sf::Mouse::getPosition(*target);
	int x = round((-target->mapPixelToCoords(mpos) + sf::Vector2f(tile_Size / 2, tile_Size / 2)).x / tile_Size);
	int y = round((-target->mapPixelToCoords(mpos) + sf::Vector2f(tile_Size / 2, tile_Size / 2)).y / tile_Size);
	highlight.setOrigin(x * tile_Size, y * tile_Size);
	
}

void Gui::Highlight::setVisibility(bool isVisible)
{
	this->visible = isVisible; 
}
