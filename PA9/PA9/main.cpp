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
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>



int main()
{
    sf::RenderWindow window(sf::VideoMode(1102, 646), "wooha");

    // music
    sf::Music music;
    if (!music.openFromFile("music/dating_theme.ogg"))
    {
        throw("Music no load!");
    }
    music.play();
   

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
    sf::RectangleShape background;
    background.setSize(sf::Vector2f(1102, 646));
    sf::Texture Maintexture;
    Maintexture.loadFromFile("Textures/funny.jpg");
    background.setTexture(&Maintexture);

    // This is the texture and mapping for where the text will go when she speaks
    // text box
    sf::RectangleShape rec_shape;
    rec_shape.setSize(sf::Vector2f(1261, 569));
    sf::Texture text_Texture;
    text_Texture.loadFromFile("Textures/text_box.png");
    rec_shape.setTexture(&text_Texture);
    rec_shape.setPosition(-20, 200);

    // andy's dream girl
    sf::RectangleShape andy_girl;
    andy_girl.setSize(sf::Vector2f(506, 758));
    sf::Texture girl_asset;
    girl_asset.loadFromFile("Textures/andy_girl3.png");
    girl_asset.setSmooth(true);
    andy_girl.setTexture(&girl_asset);
    andy_girl.setPosition(575, -50);
  
    

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
        window.draw(andy_girl);
        window.draw(rec_shape);
        window.draw(text);
        window.display();
    }

    return 0;
}