#include "Button.hpp"

void Button::toggleButton() {
	if (this->toggle) this->toggle = false;
	else this->toggle = true;
}

void Button::setPosition(sf::Vector2f &newPosition) {
	RectangleShape::setPosition(newPosition);
}

void Button::changeButtonTexture(sf::Texture& newTexture) {
	dynamic_cast<sf::RectangleShape&>(*this).setTexture(&newTexture);
}

bool Button::getButtonState() {
	return this->toggle;
}

bool isBeingPushed() {
	return false;
}

sf::RectangleShape& Button::getDrawableShape() {
	return dynamic_cast<sf::RectangleShape&>(*this);
}