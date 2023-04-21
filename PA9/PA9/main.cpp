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

sf::Vector2f& resetBackgroundScale(sf::RenderWindow& windowRef, sf::Texture& backgroundTextureRef);
sf::Vector2f& recalculateEntityPosition(Character& characterRef, sf::Window& windowRef);

int main()
{
    sf::RenderWindow window(sf::VideoMode(1050, 789), "Code to My Heart");

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
    sf::Vector2f backgroundResizeValue;
    menuBackgroundTexture.loadFromFile("8-bit-japanese-background.png");
    gameBackgroundTexture.loadFromFile("Textures/funny.jpg");
    background.setTexture(menuBackgroundTexture);
    backgroundResizeValue = resetBackgroundScale(window, menuBackgroundTexture);
    background.setScale(backgroundResizeValue);

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
   

    //andy_girl.setSize(sf::Vector2f(506, 758));
    //girl_asset.loadFromFile("Textures/andy_girl3.png");
    //girl_asset.setSmooth(true);
    //andy_girl.setTexture(&girl_asset);
    //andy_girl.setPosition(575, -50);



    sf::Texture btnTexture;
    btnTexture.loadFromFile("Textures/text_box.png");
    Button playGameBtn(sf::Vector2f(500, 100), sf::Vector2f(100, 100), btnTexture);

    bool isFullscreen = true;
    bool menuMode = true;

    music.play();
    while (window.isOpen())
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
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                if (isFullscreen) window.create(sf::VideoMode(1050, 789), "Code to my Heart");
                if (!isFullscreen) window.create(sf::VideoMode::getFullscreenModes()[0], "Code to my Heart");

                backgroundResizeValue = resetBackgroundScale(window, gameBackgroundTexture);
                background.setScale(backgroundResizeValue);

                isFullscreen = !isFullscreen; // It'll alternate each time we go back and forth between fullscreen and not fullscreen
            }

            // Display all of the menu features
            if (menuMode) {
                window.draw(playGameBtn.getDrawableShape());
                if (playGameBtn.isBeingPushed(window)) {
                    background.setTexture(gameBackgroundTexture);
                    backgroundResizeValue = resetBackgroundScale(window, gameBackgroundTexture);
                    background.setScale(backgroundResizeValue);

                    menuMode = false;
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

sf::Vector2f& resetBackgroundScale(sf::RenderWindow& windowRef, sf::Texture& backgroundTextureRef) {
    sf::Vector2u windowSize = windowRef.getSize(), textureSize = backgroundTextureRef.getSize();

    float scaleX = (float)(windowSize.x / textureSize.x);
    float scaleY = (float)(windowSize.y / textureSize.y);

    sf::Vector2f result(scaleX, scaleY);

    return result;
}

sf::Vector2f& recalculateEntityPosition(Character& characterRef, sf::Window& windowRef) {
    float posX = characterRef.getPosition().x;
    sf::Vector2f result(0, 0);
    return result;
    //WORK IN PROGRESS
}