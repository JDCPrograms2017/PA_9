/*
* Collaborators: Simon Meili, Zack Felcyn, Joshua Chadwick, Haley Boileau
* Project Name: PA 9 - Anime Date Simulator
* Due Date: April 26, 2023
* Professor: Andy O'Fallon
* 
* Description: N/A
*/

// NOTE: When compiling and running this program, ensure that the SFML DLLs are in the same directory as the output build!
// Ex. ./PA9/x64/Debug
// 
// Additional Note: SFML only allows compiling and executing in machine type x64, so x86 & arm64 won't compile to my knowledge...

#include <SFML/Graphics.hpp>
#include "Button.hpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(735, 413), "wooha");

    // This is the texture and mapping for the background
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(735, 413));
    sf::Texture gameBackgroundTexture;
    sf::Texture menuBackgroundTexture;
    menuBackgroundTexture.loadFromFile("Textures/menu.png");
    gameBackgroundTexture.loadFromFile("Textures/funny.jpg");
    background.setTexture(&menuBackgroundTexture);

    // This is the texture and mapping for where the text will go when she speaks
    sf::RectangleShape rec_shape;
    rec_shape.setSize(sf::Vector2f(735, 413));
    sf::Texture text_Texture;
    text_Texture.loadFromFile("Textures/text_box.png");
    rec_shape.setTexture(&text_Texture);
    rec_shape.setPosition(0, 100);

    window.setFramerateLimit(60); // cap it at 60FPS rn

    
    // this is the texture for the button
    sf::Texture menuButtons;
    menuButtons.loadFromFile("Textures/pink-button.png");
    Button newSessionBtn(sf::Vector2f(200, 80), sf::Vector2f(1, 1), menuButtons);
    Button resumeSessionBtn(sf::Vector2f(200, 80), sf::Vector2f(1, 1), menuButtons);
    Button aboutGameBtn(sf::Vector2f(200, 80), sf::Vector2f(1, 1), menuButtons);

    sf::Texture exitButton;
    exitButton.loadFromFile("Textures/exit.png");
    Button exitBtn(sf::Vector2f(100, 30), sf::Vector2f(1, 1), exitButton);



    bool isFullscreen = true;
    bool menuMode = true;

    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            window.clear();
            window.draw(background);
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                if (isFullscreen) window.create(sf::VideoMode(1050, 789), "Code to my Heart");
                if (!isFullscreen) window.create(sf::VideoMode(800, 800), "Code to my Heart");

                isFullscreen = !isFullscreen; // It'll alternate each time we go back and forth between fullscreen and not fullscreen
            }

            // Display all of the menu features
            if (menuMode) {
                window.draw(newSessionBtn.getDrawableShape());
                window.draw(resumeSessionBtn.getDrawableShape());
                window.draw(aboutGameBtn.getDrawableShape());
                window.draw(exitBtn.getDrawableShape());

                

            }
            // Run the game
            else {
                window.draw(rec_shape);
            }
        }

      
        window.display();
    }

    return 0;
}