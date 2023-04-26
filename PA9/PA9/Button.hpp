#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

class Button : public sf::RectangleShape {

public:

	// Generic Button Constructor
	// Takes in Vector2f objects for size and position, a Texture object if we want a texture, and some text if we want text on the Button
	Button(const sf::Vector2f& newSize = sf::Vector2f(0, 0),
		const sf::Vector2f& newPos = sf::Vector2f(0, 0),
		const sf::Texture& newButtonTexture = sf::Texture(),
		std::string insideText = "No text") : sf::RectangleShape(newSize), position(newPos), buttonTexture(newButtonTexture) {

		toggle = false;
		dynamic_cast<sf::RectangleShape&>(*this).setTexture(&buttonTexture);
		std::cout << "New button created!\n";
		this->setPosition(position);

		if (insideText != "No text") buttonText.setString(insideText);
		buttonText.setStyle(sf::Text::Bold);
	};

	// Generic Button Constructor
	// Takes in Vector2f objects for size and position and some text if we want text on the Button
	Button(const sf::Vector2f& newSize = sf::Vector2f(0, 0),
		const sf::Vector2f& newPos = sf::Vector2f(0, 0),
		std::string insideText = "No text") : sf::RectangleShape(newSize), position(newPos) {

		toggle = false;
		std::cout << "New button created!\n";
		buttonText.setFillColor(sf::Color::White);
		this->setPosition(position);

		if (insideText != "No text") buttonText.setString(insideText);
		buttonText.setStyle(sf::Text::Bold);
	};

	/*
	* Name: toggleButton
	* Description: Used to alter the boolean value of the Button object
	*/
	void toggleButton();

	/*
	* Name: setPosition
	* Description: Used to alter the position of the Button in the window
	* Inputs: sf::Vector2f reference to an object
	*/
	void setPosition(sf::Vector2f& newPosition);

	/*
	* Name: changeButtonTexture
	* Description: Used to alter the texture of the Button
	* Inputs: sf::Texture reference to a new texture
	*/
	void changeButtonTexture(sf::Texture& newTexture);

	/*
	* Name: setButtonText
	* Description: Used to alter the text that will be displayed within the Button
	* Inputs: std::string copy of new text
	*/
	void setButtonText(std::string newText) {
		buttonText.setString(newText);
	}
	// setters for the button text written by Simon
	void setButtonTextFont(sf::Font& fontRef) {
		buttonText.setFont(fontRef);
	}

	/*
	* Name: setButtonTextSize
	* Description: Used to alter the font size of the text
	* Inputs: int for new font size
	*/
	void setButtonTextSize(int x)
	{
		buttonText.setCharacterSize(x);
	}

	/*
	* Name: setButtonTextColor
	* Description: Used to alter the color of the text within the Button
	* Inputs: sf::Color copy of an sf::Color type
	*/
	void setButtonTextColor(sf::Color color)
	{
		buttonText.setFillColor(color);
	}

	/*
	* Name: setButtonTextPosition
	* Description: Used to alter the position of the Button's text in the window
	* Inputs: const sf::Vector2f reference to an object
	*/
	void setButtonTextPos(const sf::Vector2f& position)
	{
		buttonText.setPosition(position);
	}

	/*
	* Name: setButtonTextOrigin
	* Description: Used to alter the origin of the text inside the Button
	*/
	void setButtonTextOrigin()
	{
		sf::FloatRect textRect = buttonText.getLocalBounds();
		buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
		buttonText.setStyle(sf::Text::Regular);
	}

	/*
	* Name: draw
	* Description: Used to draw both the Button and the text that overlays the Button.
	* Inputs: Reference to the current window and a boolean value to display debug bounding boxes
	*/
	void draw(sf::RenderWindow& window, bool debugMode = false);

	/*
	* Name: recomputeTextPosition
	* Description: Used to alter the position of the text in the window to be centered inside the Button
	* CREDIT: Username = Mario https://stackoverflow.com/questions/49346432/how-to-center-a-sftext-in-a-sfrectangleshape
	*/
	void recomputeTextPosition() {
		sf::FloatRect textBounds = buttonText.getLocalBounds();
		sf::FloatRect buttonBounds = this->getLocalBounds();
		sf::Vector2f buttonPosition = this->getPosition();

		buttonText.setOrigin(textBounds.width / 2, textBounds.height / 2);

		buttonText.setPosition(buttonPosition.x + (buttonBounds.width / 2), buttonPosition.y + (buttonBounds.height / 2) - 5); // The -5 is just a little correction to make it look better.
	}

	/*
	* Name: getButtonState
	* Description: Returns the current state of the Button's boolean value
	* Returns: bool (true or false)
	*/
	bool getButtonState();

	/*
	* Name: isBeingPushed
	* Description: Used to identify whether or not the Button is being "clicked" or "pushed" by the user
	* Inputs: Reference to the current window
	* Returns: bool (true or false)
	*/
	bool isBeingPushed(const sf::Window& windowRef);

	/*
	* Name: getDrawableShape
	* Description: Used to extract a reference to an sf::RectangleShape object which can then be drawn to the window
	* Returns: Reference to an sf::RectangleShape object
	*/
	sf::RectangleShape& getDrawableShape();

	/*
	* Name: getTextObject
	* Description: Used to extract a reference to an sf::Text object which can then be drawn to the window
	* Returns: Reference to an sf::Text object
	*/
	sf::Text& getTextObject() {
		return buttonText;
	}
private:
	sf::Vector2f position;
	const sf::Texture buttonTexture;
	sf::Text buttonText;
	bool toggle;

};