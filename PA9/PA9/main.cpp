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



    int ticker = 0;

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
    text.setPosition(230, 650);
    

    // This is the texture and mapping for the background
    // Background
    sf::Sprite background;

    /*Textures by Level*/
    sf::Texture gameBackgroundTexture;
    sf::Texture gameFancyPanda;
    sf::Texture gamePandaInterior;
    sf::Texture menuBackgroundTexture;
    sf::Texture aboutBackgroundTexture;
    sf::Vector2f backgroundResizeValue;
    sf::Texture empty_texture;
    menuBackgroundTexture.loadFromFile("Textures/menu.png");

    /* Game Textures by Level */
    gameBackgroundTexture.loadFromFile("Textures/intro.jpg");
    gameFancyPanda.loadFromFile("Textures/fancyPanda.jpeg");
    gamePandaInterior.loadFromFile("Textures/pandaInterior.jpg");

    background.setPosition(0, 0);
    aboutBackgroundTexture.loadFromFile("Textures/aboutScreen.png");
    empty_texture.loadFromFile("Textures/empty.png");
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
    std::ifstream fPanda("linesPanda.txt");
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
            /*   
            continue_button.draw(window);*/
                window.draw(rec_shape);
                window.draw(text);
              
                if (ticker >= 9)
                {
                    window.draw(girl.getDrawableObject());
                    window.draw(rec_shape);
                    window.draw(text);
                }
               
                if (continue_button.isBeingPushed(window))
                {
                   
                    ++ticker;
                    std::cout << ticker;
                    text.setString(readFromFile(file));
                    window.draw(text);

                    if (ticker == 6)
                    {
                        /* Transition to the stor vroom vroom */
                        resetBackgroundScale(window, gameFancyPanda, background);
                        text.setString(readFromFile(file));
                        window.draw(text);

                        
                     
                    }
                    if (ticker == 9)
                    {
                        /*---- Zoom Effect ------------------------------------------------*/

                        sf::View view(sf::FloatRect(0.f, 0.f, 1440.f, 810.f));
                        window.setView(view);
                        // Create target view with smaller rectangle size
                        sf::View targetView(sf::FloatRect(100.f, 100.f, 500.f, 500.f));

                        // Set zoom factor and calculate step size
                        float zoomFactor = targetView.getSize().x / view.getSize().x;
                        float stepSize = (zoomFactor - 1.f) / 5.f;

                        // Perform zoom over 1.5 seconds
                        sf::Clock zoomClock;
                        while (zoomClock.getElapsedTime().asSeconds() < 1.5) {
                            // Calculate current zoom level
                            float currentZoom = 1.f + (stepSize * zoomClock.getElapsedTime().asSeconds());

                            // Create new view with current zoom level
                            sf::View zoomView(view.getCenter(), view.getSize() * currentZoom);
                            window.setView(zoomView);

                            // Draw scene
                            window.clear();
                            window.draw(background);
                            window.display();



                        }

                        // Switch back to original view
                        window.setView(view);

                        /*------------------------------------------------------------*/

                        
                        /* Transition to the stor vroom vroom */

                        resetBackgroundScale(window, gamePandaInterior, background);
                        
                        text.setString(readFromFile(file));
                        window.draw(text);
                       
                    }

                    if (ticker == 10)
                    {

                        sf::RectangleShape inputBox(sf::Vector2f(270, 80));
                        inputBox.setPosition(50, 50);
                        inputBox.setOutlineThickness(2);
                        inputBox.setOutlineColor(sf::Color::Black);
                        inputBox.setFillColor(sf::Color::White);

                        sf::Text inputText("Mock Queston what 5+5", font, 20);
                        inputText.setPosition(60, 60);
                        inputText.setFillColor(sf::Color::Black);

                        /* First button */
                        sf::RectangleShape button1(sf::Vector2f(100, 50));
                        button1.setPosition(50, 150);
                        button1.setOutlineThickness(2);
                        button1.setOutlineColor(sf::Color::Black);
                        button1.setFillColor(sf::Color::Green);
                        /* First Button Text  */
                        sf::Text buttonText("A", font, 20);
                        buttonText.setFillColor(sf::Color::White);
                        sf::FloatRect textRect = buttonText.getLocalBounds();
                        buttonText.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
                        buttonText.setPosition(button1.getPosition() + 0.5f * button1.getSize());



                        sf::RectangleShape button2(sf::Vector2f(100, 50));
                        button2.setPosition(50, 250);
                        button2.setOutlineThickness(2);
                        button2.setOutlineColor(sf::Color::Black);
                        button2.setFillColor(sf::Color::Red);

                        sf::Text buttonText2("B", font, 20);
                        buttonText2.setFillColor(sf::Color::White);
                        sf::FloatRect textRect2 = buttonText2.getLocalBounds();
                        buttonText2.setOrigin(textRect2.left + textRect2.width / 2.0f, textRect2.top + textRect2.height / 2.0f);
                        buttonText2.setPosition(button2.getPosition() + 0.5f * button2.getSize());



                        sf::RectangleShape button3(sf::Vector2f(100, 50));
                        button3.setPosition(200, 150);
                        button3.setOutlineThickness(2);
                        button3.setOutlineColor(sf::Color::Black);
                        button3.setFillColor(sf::Color::Red);

                        sf::RectangleShape button4(sf::Vector2f(100, 50));
                        button4.setPosition(200, 250);
                        button4.setOutlineThickness(2);
                        button4.setOutlineColor(sf::Color::Black);
                        button4.setFillColor(sf::Color::Red);

                        while (window.isOpen())
                        {
                            sf::Event event;
                            while (window.pollEvent(event))
                            {
                                if (event.type == sf::Event::Closed)
                                    window.close();

                                if (event.type == sf::Event::TextEntered)
                                {
                                    if (event.text.unicode < 128)
                                    {
                                        inputText.setString(inputText.getString() + static_cast<char>(event.text.unicode));
                                    }
                                }
                            }

                            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                            {
                                sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                                if (button1.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                                {
                                    std::cout << "Correct Answer!" << std::endl;
                                    ticker++;
                                }

                                if (button2.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)) || button3.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)) || button4.getGlobalBounds().contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                                {
                                    std::cout << "Wrong Answer!" << std::endl;
                                }
                            }

                          
                            window.draw(inputBox);
                            window.draw(inputText);
                            window.draw(button1);
                            window.draw(buttonText);
                            window.draw(button2);
                            window.draw(buttonText2);
                            window.draw(button3);
                            window.draw(button4);
                            window.display();
                        }

                    }

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





