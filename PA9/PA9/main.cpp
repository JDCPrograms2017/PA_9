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
    menuBackgroundTexture.loadFromFile("8-bit-japanese-background.png");
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

    

    sf::Texture btnTexture;
    btnTexture.loadFromFile("Textures/testButton.png");
    Button playGameBtn(sf::Vector2f(50, 250), sf::Vector2f(20, 800), btnTexture);

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
                window.draw(playGameBtn.getDrawableShape());

                

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