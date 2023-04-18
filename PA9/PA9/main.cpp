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

int main()
{
    sf::RenderWindow window(sf::VideoMode(1050, 789), "Code to my Heart");
    sf::CircleShape shape(20.0f);

    // This Spite stuff could be condensed to a class that inherets from both the Texture and Sprite class possibly
    sf::Texture backgroundTexture;
    sf::Sprite background;
    backgroundTexture.loadFromFile("8-bit-japanese-background.png");
    background.setTexture(backgroundTexture);

    shape.setFillColor(sf::Color::Green);

    window.setFramerateLimit(60); // cap it at 60FPS rn

    bool isFullscreen = true;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                if (isFullscreen) window.create(sf::VideoMode(1050, 789), "Code to my Heart");
                if (!isFullscreen) window.create(sf::VideoMode(800, 800), "Code to my Heart");

                isFullscreen = !isFullscreen; // It'll alternate each time we go back and forth between fullscreen and not fullscreen
            }
        }

        window.clear();
        window.draw(background);
        window.display();
    }

    return 0;
}