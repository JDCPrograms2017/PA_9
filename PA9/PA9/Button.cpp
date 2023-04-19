#include "Button.hpp"

void Button::toggleButton() {
	if (this->toggle) this->toggle = false;
	else this->toggle = true;
}

bool Button::getButtonState() {
	return this->toggle;
}

sf::RectangleShape& Button::getDrawableShape() {
	return dynamic_cast<sf::RectangleShape&>(*this);
}