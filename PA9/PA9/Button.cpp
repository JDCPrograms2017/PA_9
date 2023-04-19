#include "Button.hpp"

void Button::toggleButton() {
	if (this->toggle) this->toggle = false;
	else this->toggle = true;
}

bool Button::getButtonState() {
	return this->toggle;
}