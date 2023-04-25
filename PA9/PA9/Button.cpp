#include "Button.hpp"

void Button::toggleButton() {
	if (this->toggle) this->toggle = false;
	else this->toggle = true;
}

void Button::setPosition(sf::Vector2f &newPosition) {
	this->position = newPosition;
	RectangleShape::setPosition(newPosition);
	recomputeTextPosition();
}

void Button::changeButtonTexture(sf::Texture& newTexture) {
	dynamic_cast<sf::RectangleShape&>(*this).setTexture(&newTexture);
}

void Button::draw(sf::RenderWindow& window, bool debug) {
	recomputeTextPosition();

	window.draw(this->getDrawableShape());
	window.draw(buttonText);

	if (debug) {
		// create a rectangle shape to represent the local bounding box
		sf::FloatRect bounds(buttonText.getLocalBounds());
		//std::cout << "Local bounds: " << bounds.width << ", " << bounds.height << std::endl;
		sf::RectangleShape rect(sf::Vector2f(bounds.width, bounds.height));
		rect.setFillColor(sf::Color::Transparent);
		rect.setOutlineColor(sf::Color::Red);
		rect.setOutlineThickness(1.f);
		rect.setPosition(buttonText.getPosition().x + bounds.left, buttonText.getPosition().y + bounds.top);

		sf::FloatRect boundsButton(this->getLocalBounds());
		sf::RectangleShape rectButton(sf::Vector2f(boundsButton.width, boundsButton.height));
		rectButton.setFillColor(sf::Color::Transparent);
		rectButton.setOutlineColor(sf::Color::Red);
		rectButton.setOutlineThickness(1.f);
		rectButton.setPosition(this->getPosition().x + boundsButton.left, this->getPosition().y + boundsButton.top);

		window.draw(rect);
		window.draw(rectButton);
	}
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
		//std::cout << mousePosition.x << ", " << mousePosition.y << " button position: " << this->position.x << ", " << this->position.y << " button size: " << this->getSize().x << ", " << this->getSize().y << std::endl;
	}

	return false;
}

sf::RectangleShape& Button::getDrawableShape() {
	return dynamic_cast<sf::RectangleShape&>(*this);
}