#include "Button.hpp"

void Button::toggleButton() {
	if (this->toggle) this->toggle = false;
	else this->toggle = true;
}

void Button::setPosition(sf::Vector2f &newPosition) {
	this->position = newPosition;
	RectangleShape::setPosition(newPosition);
}

void Button::changeButtonTexture(sf::Texture& newTexture) {
	dynamic_cast<sf::RectangleShape&>(*this).setTexture(&newTexture);
}

bool Button::getButtonState() {
	return this->toggle;
}

bool Button::isBeingPushed(const sf::Window &windowRef) {
	sf::Vector2i mousePosition = sf::Mouse::getPosition(windowRef); // Gets the position of the mouse relative to the window, not the whole screen.
	bool mouseClicked = sf::Mouse::isButtonPressed(sf::Mouse::Left); // Sees if we are clicking with the left mouse button.

	if (mouseClicked && mousePosition.x >= this->position.x && mousePosition.x <= (this->position.x + this->getSize().x) && mousePosition.y >= this->position.y && mousePosition.y <= (this->position.y + this->getSize().y)) {
		return true;
	}
	else {
		std::cout << mousePosition.x << ", " << mousePosition.y << " button position: " << this->position.x << ", " << this->position.y << " button size: " << this->getSize().x << ", " << this->getSize().y << std::endl;
	}

	return false;
}

sf::RectangleShape& Button::getDrawableShape() {
	return dynamic_cast<sf::RectangleShape&>(*this);
}