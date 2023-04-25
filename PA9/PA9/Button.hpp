#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>

class Button : public sf::RectangleShape {

public:
	Button(const sf::Vector2f& newSize = sf::Vector2f(0, 0), 
		   const sf::Vector2f& newPos = sf::Vector2f(0, 0), 
		   const sf::Texture& newButtonTexture = sf::Texture(), 
		std::string insideText = "No text") : sf::RectangleShape(newSize), position(newPos), buttonTexture(newButtonTexture) {

		toggle = false;
);

		dynamic_cast<sf::RectangleShape&>(*this).setTexture(&buttonTexture);


		std::cout << "New button created!\n";
		this->setPosition(position);

		if (insideText != "No text") buttonText.setString(insideText), std::cout << "Set string text!";
		buttonText.setStyle(sf::Text::Bold);
	};

	void toggleButton();
	void setPosition(sf::Vector2f &newPosition);
	void changeButtonTexture(sf::Texture& newTexture);
	void setButtonText(std::string newText) {
		buttonText.setString(newText);
	}
	void setButtonTextFont(sf::Font& fontRef) {
		buttonText.setFont(fontRef);
	}

	void draw(sf::RenderWindow& window, bool debug = false);

	// Centering button text in the middle of the button - CREDIT: Username = Mario https://stackoverflow.com/questions/49346432/how-to-center-a-sftext-in-a-sfrectangleshape
	void recomputeTextPosition() {
		sf::FloatRect textBounds = buttonText.getLocalBounds();
		//std::cout << "Local bounds: " << textBounds.width << ", " << textBounds.height << std::endl;
		sf::FloatRect buttonBounds = this->getLocalBounds();
		sf::Vector2f buttonPosition = this->getPosition();

		buttonText.setOrigin(textBounds.width / 2, textBounds.height / 2);

		buttonText.setPosition(buttonPosition.x + (buttonBounds.width / 2), buttonPosition.y + (buttonBounds.height / 2) - 5); // The -5 is just a little correction to make it look better.
	}

	bool getButtonState();

	bool isBeingPushed(const sf::Window &windowRef);


	sf::RectangleShape& getDrawableShape();
private:
	sf::Vector2f position;
	const sf::Texture buttonTexture;
	sf::Text buttonText;
	bool toggle;

};