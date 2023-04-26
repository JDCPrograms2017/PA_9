#pragma once

#include "Button.hpp"
#include <SFML/Audio.hpp>
#include <fstream>

class TestCases {

public:

	/*
	* Name: testResourceLoading
	* Description: Ensures that the resources we use in the game can be properly loaded
	* Inputs: None
	* Outputs: Text describing the outcomes of different loading situations.
	* Returns: Void
	*/
	void testResourceLoading() {
		sf::Music music;
		if (!music.openFromFile("music/dating_theme.ogg"))
		{
			throw("The dating_theme.ogg file isn't loading!");
		}
		else {
			std::cout << "Successfully opened dating_theme.ogg\n";
		}

		sf::Music scene1_music;
		if (!scene1_music.openFromFile("music/scene1.ogg"))
		{
			throw("The scene1.ogg file isn't loading!");
		}
		else {
			std::cout << "Successfully opened scene1.ogg\n";
		}

		sf::Music scene2_music;
		if (!scene2_music.openFromFile("music/panda.ogg"))
		{
			throw("The panda.ogg file isn't loading!");
		}
		else {
			std::cout << "Successfully opened panda.ogg\n";
		}

		sf::Font font;
		if (!font.loadFromFile("Font/Aller_It.ttf"))
		{
			throw("The font file couldn't be loaded!");
		}
		else {
			std::cout << "The font file was loaded successfully!\n";
		}
	}

	/*
	* Name: testButtonClick
	* Description: Ensures that we can properly detect if a Button is being pressed.
	* Inputs: None
	* Outputs: Text describing the outcomes of different mouse-to-button location and clicking situations.
	* Returns: Void
	*/
	void testButtonClick() {
		sf::Font font;
		font.loadFromFile("Font/Aller_It.ttf");
		sf::RenderWindow window(sf::VideoMode(1440, 810), "Test Window");
		bool buttonResult = false, positionTest = false;

		Button testButton(sf::Vector2f(500, 100), sf::Vector2f(50, 150), "Close window after clicking button");
		testButton.setFillColor(sf::Color::Red);
		testButton.setButtonTextFont(font);
		testButton.setButtonTextColor(sf::Color::White);

		while (window.isOpen()) {
			sf::Event event;

			window.clear();
			while (window.pollEvent(event)) {
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}
			testButton.draw(window);

			window.display();

			if (testButton.isBeingPushed(window)) {
				buttonResult = true;
				//std::cout << "True!\n";
			}

			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				//std::cout << "Mouse is clicked.\n";
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				sf::Vector2f buttonPos = testButton.getPosition();
				if (mousePos.x >= buttonPos.x && mousePos.x <= (buttonPos.x + testButton.getSize().x) && mousePos.y >= buttonPos.y && mousePos.y <= (buttonPos.y + testButton.getSize().y)) {
					positionTest = true;
				}
			}

		}

		if (buttonResult && positionTest) {
			std::cout << "Button test SUCCEEDED! Button is being pushed.\n buttonResult: " << buttonResult << " PositionTest: " << positionTest << std::endl;
		}
		else {
			std::cout << "Button test FAILED! Button is not correctly detecting being pushed.\n buttonResult: " << buttonResult << " PositionTest: " << positionTest << std::endl;
		}
		
	}

	/*
	* Name: testTextRecomputation
	* Description: Checks if the text is properly centered in the middle of the button after recomputing the center.
	* Inputs: None
	* Outputs: Text describing the outcomes of relocating the text on the screen.
	* Returns: Void
	*/
	void testTextRecomputation() {
		Button testButton(sf::Vector2f(500, 100), sf::Vector2f(50, 150), "Some test text");
		testButton.recomputeTextPosition();

		sf::Text buttonText = testButton.getTextObject();

		sf::Vector2f textPosition = buttonText.getPosition();
		sf::FloatRect buttonBounds = testButton.getLocalBounds();
		sf::Vector2f buttonPosition = testButton.getPosition();

		if (textPosition.x == (buttonPosition.x + (buttonBounds.width / 2)) && textPosition.y == (buttonPosition.y + (buttonBounds.height / 2) - 5)) {
			std::cout << "The text is in the correct position!\n";
		}
		else {
			std::cout << "The text is NOT centered properly!\n";
		}
	}

	/*
	* Name: testOpeningTextFile
	* Description: Ensures that we are properly opening the text file to read.
	* Inputs: None
	* Outputs: Text describing whether or not the file was properly opened. Also calls next test function.
	* Returns: Void
	*/
	void testOpeningTextFile() {
		std::ifstream textStream("lines.txt");
		if (!textStream) {
			std::cout << "Could not open the text file!\n";
		}
		else {
			std::cout << "Text file successfully opened!\n";
			testReadingTextFile(textStream);
		}
	}

	/*
	* Name: testReadingTextFile
	* Description: Ensures that we are properly reading text from the file.
	* Inputs: ifstream reference
	* Outputs: Text describing the outcomes of if we can or cannot read text from our file.
	* Returns: Void
	* Preconditions: The text file must be OPENED!
	*/
	void testReadingTextFile(std::ifstream& textStream) {
		std::string nextString;
		getline(textStream, nextString);
		if (nextString.empty()) {
			std::cout << "Could not read text from the file!\n";
		}
		else {
			std::cout << "Reading text from the file!\n";
		}

		textStream.close();
	}
};