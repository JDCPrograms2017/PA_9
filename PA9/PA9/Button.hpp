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
		dynamic_cast<sf::RectangleShape&>(*this).setTexture(&buttonTexture);
		std::cout << "New button created!\n";
		this->setPosition(position);

		if (insideText != "No text") buttonText.setString(insideText), std::cout << "Set string text!";
		//buttonText.setCharacterSize((int)(newSize.x / 10));
		buttonText.setStyle(sf::Text::Bold);
		recomputeTextPosition();
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

	void draw(sf::RenderWindow& window);

	// Centering button text in the middle of the button - CREDIT: Username = Mario https://stackoverflow.com/questions/49346432/how-to-center-a-sftext-in-a-sfrectangleshape
	void recomputeTextPosition() {
		buttonText.setOrigin(buttonText.getScale().x / 2, buttonText.getScale().y);
		buttonText.setPosition(this->getPosition()); // bases the position of the button text where the button itself is.
		const sf::FloatRect bounds(buttonText.getLocalBounds());
		/*std::cout << "Local bounds of the text:" << std::endl;
		std::cout << "Left: " << bounds.left << std::endl;
		std::cout << "Top: " << bounds.top << std::endl;
		std::cout << "Width: " << bounds.width << std::endl;
		std::cout << "Height: " << bounds.height << std::endl;*/
		const sf::Vector2f box(this->getSize());
		buttonText.setPosition((box.x ), (box.y ));
		//buttonText.setOrigin((bounds.width - box.x) / 2 + bounds.left, (bounds.height - box.y) / 2 + bounds.top);
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