#pragma once

#include "Button.hpp"
#include "Character.h"
#include <vector>

class Scene {

public:
	Scene(sf::RenderWindow &currentWindow) : windowRef(currentWindow) {
		if (!currentWindow.isOpen()) throw("Error: Window not found. Was it closed out?\n");
	};

	void insert(Character& newCharacter) {
		// do an insert into Character array
	}

	void insert(Button& newButton) {

	}

	void changeBackground(sf::Sprite newBackground) { // we want a copy, not a reference to a background sprite
		background = newBackground;
	}

	void display() {

	}

private:
	sf::RenderWindow &windowRef;
	std::vector<Character> sceneCharacters;
	std::vector<Button> sceneButtons;
	sf::Sprite background;

};