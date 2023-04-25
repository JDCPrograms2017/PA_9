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
#include <fstream>
#include <string>

void resetBackgroundScale(sf::RenderWindow& windowRef, sf::Texture& backgroundTextureRef, sf::Sprite& backgroundRef);
sf::Vector2f& recalculateEntityPosition(Character& characterRef, sf::Window& windowRef);
std::string readFromFile(std::ifstream& file);

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
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Regular);
    text.setString("\"One lonely night, you get a match on Tinder and suprisingly, the girl texts first.\"");
    text.setPosition(180, 650);
    

    // This is the texture and mapping for the background
    // Background
    sf::Sprite background;
    sf::Sprite sceneOneBackground;
    sf::Texture sceneOneTexture;
    sf::Texture gameBackgroundTexture;
    sf::Texture menuBackgroundTexture;
    sf::Texture aboutBackgroundTexture;
    sf::Vector2f backgroundResizeValue;
    sf::Texture empty_texture;
    menuBackgroundTexture.loadFromFile("Textures/menu.png");
    gameBackgroundTexture.loadFromFile("Textures/intro.jpg");
    background.setPosition(0, 0);
    aboutBackgroundTexture.loadFromFile("Textures/aboutScreen.png");
    empty_texture.loadFromFile("Textures/empty.png");
    sceneOneTexture.loadFromFile("Textures/cafe.jpg");
    resetBackgroundScale(window, menuBackgroundTexture, background); 

    // This is the texture and mapping for the text box for when she speaks
    sf::RectangleShape rec_shape;
    rec_shape.setSize(sf::Vector2f(1400, 569));
    sf::Texture text_Texture;
    text_Texture.loadFromFile("Textures/ui.png");
    rec_shape.setTexture(&text_Texture);
    rec_shape.setPosition(-20, 350);


    // andy's dream girl, added polymorphism
    sf::Texture girl_asset;
    girl_asset.loadFromFile("Textures/andy_girl3.png");
    Character girl(girl_asset, sf::Vector2f(0.5, 0.5), sf::Vector2f(500, -100));


    // menu buttons
    sf::Texture btnTexture;
    btnTexture.loadFromFile("Textures/pink-button.png");
    Button playGameBtn(sf::Vector2f(300, 150), sf::Vector2f(750, 450), btnTexture, "Play Game");
    playGameBtn.setButtonTextFont(font);
    //Text position: (823, 505)

    Button aboutGameBtn(sf::Vector2f(300, 150), sf::Vector2f(750, 525), btnTexture, "About Game");
    aboutGameBtn.setButtonTextFont(font);
    //Text Postition: (820, 580)

    sf::Texture exitBtnTexture;
    exitBtnTexture.loadFromFile("Textures/exit.png");
    Button exitBtn(sf::Vector2f(200, 100), sf::Vector2f(1250, 700), exitBtnTexture, "Exit");
    exitBtn.setButtonTextFont(font);
    //Text Position: (1320, 730)

    // about screen - exit button stays the same, changing position of play game button
    Button newPlayGameBtn(sf::Vector2f(300, 150), sf::Vector2f(580, 600), btnTexture, "Play Game");
    newPlayGameBtn.setButtonTextFont(font);
    //Text Position: (653, 655)

    // use this to click thru text
    Button continue_button(sf::Vector2f(1400, 569), sf::Vector2f(-20, 350), empty_texture, "");

  


    bool isFullscreen = true;
    bool menuMode = true;
    bool aboutMode = false;

    music.play();
    std::ifstream file("lines.txt");
    int i = 0;
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
                aboutGameBtn.draw(window);
                exitBtn.draw(window);
                playGameBtn.draw(window);
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
            else if (aboutMode) {
                exitBtn.draw(window);
                newPlayGameBtn.draw(window);
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
                //window.draw(girl.getDrawableObject());
                /*    continue_button.draw(window);*/
                if (i >= 8)
                {
                    window.draw(girl.getDrawableObject());
                }
                window.draw(rec_shape);
                window.draw(text);
                if (i == 6)
                {
                    resetBackgroundScale(window, sceneOneTexture, background);

                }


                if (continue_button.isBeingPushed(window))
                {
                    ++i;
                    text.setString(readFromFile(file));

                }

                

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

std::string readFromFile(std::ifstream& file)
{
    std::string temp;
    getline(file,temp);
    return temp;


}