/*
* Collaborators: Simon Meili, Zack Felcyn, Joshua Chadwick, Haley Boileau
* Project Name: PA 9 - Anime Date Simulaton
* Due Date: April 26, 2023
* Professor: Andy O'Fallon
*
* Description: N/A
*/

// NOTE: When compiling and running this program, ensure that the SFML DLLs are in the same directory as the output build!
// Ex. ./PA9/x64/Debug
// 
// Additional Note: SFML only allows compiling and executing in machine type x64, so x86 & arm64 won't compile to my knowledge...

#define _CRT_SECURE_NO_DEPRECATE
#include <SFML/Audio.hpp>
#include <iostream>
#include "Character.h"
#include "Button.hpp"

void resetBackgroundScale(sf::RenderWindow& windowRef, sf::Texture& backgroundTextureRef, sf::Sprite& backgroundRef);
sf::Vector2f& recalculateEntityPosition(Character& characterRef, sf::Window& windowRef);

int main()
{
    sf::RenderWindow window(sf::VideoMode(1440, 810), "Code to My Heart"); // 0.75 scale factor of the menu image size

    // music
    sf::Music music;
    if (!music.openFromFile("music/dating_theme.ogg"))
    {
        throw("Music no load!");
    }


    // Text generation
    sf::Font font;
    if (!font.loadFromFile("Font/Aller_It.ttf"))
    {
        throw("Sadness :(");
    }
    // text generated on screen
    sf::Text text;
    text.setFont(font);
    text.setCharacterSize(30);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Regular);
    text.setString("\"You look lonely, I could fix that...\"");
    text.setPosition(250, 475);


    // This is the texture and mapping for the background
    // Background
    sf::Sprite background;
    sf::Texture gameBackgroundTexture;
    sf::Texture menuBackgroundTexture;
    sf::Texture aboutBackgroundTexture;
    sf::Vector2f backgroundResizeValue;
    menuBackgroundTexture.loadFromFile("Textures/menu.png");
    gameBackgroundTexture.loadFromFile("Textures/funny.jpg");
    aboutBackgroundTexture.loadFromFile("Textures/aboutScreen.png");
    background.setPosition(0, 0);
    resetBackgroundScale(window, menuBackgroundTexture, background);

    // This is the texture and mapping for where the text will go when she speaks
    // text box
    sf::RectangleShape rec_shape;
    rec_shape.setSize(sf::Vector2f(1261, 569));
    sf::Texture text_Texture;
    text_Texture.loadFromFile("Textures/text_box.png");
    rec_shape.setTexture(&text_Texture);
    rec_shape.setPosition(-20, 200);


    // andy's dream girl, added polymorphism
    sf::Texture girl_asset;
    girl_asset.loadFromFile("Textures/andy_girl3.png");
    Character girl(girl_asset, sf::Vector2f(0.5, 0.5), sf::Vector2f(500, -100));


    // menu buttons

    sf::Texture btnTexture;
    btnTexture.loadFromFile("Textures/pink-button.png");
    Button playGameBtn(sf::Vector2f(300, 150), sf::Vector2f(750, 450), btnTexture);
    sf::Text playGameText;
    playGameText.setFont(font);
    playGameText.setCharacterSize(30);
    playGameText.setFillColor(sf::Color::White);
    playGameText.setStyle(sf::Text::Regular);
    playGameText.setString("Play Game");
    playGameText.setPosition(823, 505);
    Button aboutGameBtn(sf::Vector2f(300, 150), sf::Vector2f(750, 525), btnTexture);
    sf::Text aboutGameText;
    aboutGameText.setFont(font);
    aboutGameText.setCharacterSize(30);
    aboutGameText.setFillColor(sf::Color::White);
    aboutGameText.setStyle(sf::Text::Regular);
    aboutGameText.setString("About Game");
    aboutGameText.setPosition(820, 580);
    sf::Texture exitBtnTexture;
    exitBtnTexture.loadFromFile("Textures/exit.png");
    Button exitBtn(sf::Vector2f(200, 100), sf::Vector2f(1250, 700), exitBtnTexture);
    sf::Text exitText;
    exitText.setFont(font);
    exitText.setCharacterSize(30);
    exitText.setFillColor(sf::Color::White);
    exitText.setStyle(sf::Text::Regular);
    exitText.setString("Exit");
    exitText.setPosition(1320, 730);

    // about screen - exit button stays the same, changing position of play game button
    Button newPlayGameBtn(sf::Vector2f(300, 150), sf::Vector2f(580, 600), btnTexture);
    sf::Text newPlayGameText;
    newPlayGameText.setFont(font);
    newPlayGameText.setCharacterSize(30);
    newPlayGameText.setFillColor(sf::Color::White);
    newPlayGameText.setStyle(sf::Text::Regular);
    newPlayGameText.setString("Play Game");
    newPlayGameText.setPosition(653, 655);



    bool isFullscreen = true;
    bool menuMode = true;
    bool aboutMode = false;

    music.play();
    while (window.isOpen()) //NOTE: Rapid flickering after texture resizing or reloading is because the resizing event remains until a new event occurs. Fix this.
    {



        sf::Event event;
        while (window.pollEvent(event))
        {
            window.clear();
            window.draw(background);

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::Resized) {
                // if the window was resized, do something... like reposition our characters
                resetBackgroundScale(window, gameBackgroundTexture, background);
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                if (isFullscreen) window.create(sf::VideoMode(1050, 789), "Code to my Heart");
                if (!isFullscreen) window.create(sf::VideoMode::getFullscreenModes()[0], "Code to my Heart");

                resetBackgroundScale(window, gameBackgroundTexture, background);

                isFullscreen = !isFullscreen; // It'll alternate each time we go back and forth between fullscreen and not fullscreen
            }

            // Display all of the menu features
            if (menuMode) {
                window.draw(playGameBtn.getDrawableShape());

                window.draw(playGameText);
                window.draw(aboutGameBtn.getDrawableShape());
                window.draw(aboutGameText);
                window.draw(exitBtn.getDrawableShape());
                window.draw(exitText);


                if (playGameBtn.isBeingPushed(window)) {
                    resetBackgroundScale(window, gameBackgroundTexture, background);
                    menuMode = false;
                }

                
                if (aboutGameBtn.isBeingPushed(window)) {
                    resetBackgroundScale(window, aboutBackgroundTexture, background);
                    aboutMode = true;
                    menuMode = false;
                }

                if (exitBtn.isBeingPushed(window)) {
                    window.close();
                }
            }
            // about game screen
            else if (aboutMode) {
                window.draw(exitBtn.getDrawableShape());
                window.draw(exitText);
                window.draw(newPlayGameBtn.getDrawableShape());
                window.draw(newPlayGameText);
                if (newPlayGameBtn.isBeingPushed(window)) {
                    resetBackgroundScale(window, gameBackgroundTexture, background);
                    aboutMode = false;
                }

                if (exitBtn.isBeingPushed(window)) {
                    window.close();
                }

            }
            // Run the game
            else {
                window.draw(girl.getDrawableObject());
                window.draw(rec_shape);
                window.draw(text);
            }
        }

        window.display();
    }

    return 0;
}

void resetBackgroundScale(sf::RenderWindow& windowRef, sf::Texture& backgroundTextureRef, sf::Sprite &backgroundRef) {
    sf::Vector2u windowSize = windowRef.getSize(), textureSize = backgroundTextureRef.getSize();

    float scaleX = (float)windowSize.x / textureSize.x;
    float scaleY = (float)windowSize.y / textureSize.y;

    backgroundRef.setTexture(backgroundTextureRef);
    backgroundRef.setScale(scaleX, scaleY);
}

sf::Vector2f& recalculateEntityPosition(Character& characterRef, sf::RenderWindow& windowRef) {
    float posX = characterRef.getPosition().x;
    sf::Vector2f result(0, 0);
    return result;
    //WORK IN PROGRESS
}