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
#include "TestCases.h"
#include <fstream>
#include <string>

void resetBackgroundScale(sf::RenderWindow& windowRef, sf::Texture& backgroundTextureRef, sf::Sprite& backgroundRef);
sf::Vector2f& recalculateEntityPosition(Character& characterRef, sf::Window& windowRef);
std::string readFromFile(std::ifstream& file);

int main()
{
    TestCases tester;
    tester.testResourceLoading();
    tester.testButtonClick();
    tester.testTextRecomputation();
    tester.testOpeningTextFile(); // this test function will call the subsequent file-related test function...

    sf::RenderWindow window(sf::VideoMode(1440, 810), "Code to My Heart"); // 0.75 scale factor of the menu image size


    int gameWon = 0;
    // music, done by Simon
    sf::Music music;
    music.openFromFile("music/dating_theme.ogg");

    sf::Music scene1_music;
    scene1_music.openFromFile("music/scene1.ogg");

    sf::Music scene2_music;
    scene2_music.openFromFile("music/panda.ogg");

    // Text generation, done by Simon
    sf::Font font;
    font.loadFromFile("Font/Aller_It.ttf");
 
    // text generated on screen, done by Simon
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
    sf::Vector2f backgroundResizeValue;
    sf::Texture empty_texture;
    sf::Texture gameBackgroundTexture;

    // Haley designed these
    sf::Sprite aboutBackground;
    sf::Sprite menuBackground;
    sf::Sprite cafeLose;
    sf::Sprite pandaLose;
    sf::Texture menuBackgroundTexture;
    sf::Texture aboutBackgroundTexture;
    sf::Texture cafeLoseBackground;
    sf::Texture pandaLoseBackground;

    
    
    menuBackgroundTexture.loadFromFile("Textures/menu.png");
    gameBackgroundTexture.loadFromFile("Textures/intro.jpg");
    background.setPosition(0, 0);
    aboutBackgroundTexture.loadFromFile("Textures/aboutScreen.png");
    empty_texture.loadFromFile("Textures/empty.png");
    sceneOneTexture.loadFromFile("Textures/cafe.jpg");
    cafeLoseBackground.loadFromFile("Textures/cafeLose.png");
    pandaLoseBackground.loadFromFile("Textures/pandaLose.png");
    resetBackgroundScale(window, menuBackgroundTexture, background); 



    /* Panda Scene by Zack */
    sf::Texture gamePandaExterior;
    gamePandaExterior.loadFromFile("Textures/fancyPanda.jpeg");


    sf::Texture gamePandaInterior;
    gamePandaInterior.loadFromFile("Textures/pandaInterior.jpg");


    sf::Texture cars;
    cars.loadFromFile("Textures/cars_bedroom.jpeg");

    // This is the texture and mapping for the text box for when she speaks, done by Simon
    sf::RectangleShape rec_shape;
    rec_shape.setSize(sf::Vector2f(1400, 569));
    sf::Texture text_Texture;
    text_Texture.loadFromFile("Textures/ui.png");
    rec_shape.setTexture(&text_Texture);
    rec_shape.setPosition(-20, 350);


    // Creating assets for Clarissa, done by Simon
    sf::Texture girl_asset;
    girl_asset.loadFromFile("Textures/andy_girl3.png");
    sf::Texture girl2_asset;
    girl2_asset.loadFromFile("Textures/menu_imh.png");

    Character girl(girl_asset, sf::Vector2f(0.5, 0.5), sf::Vector2f(500, -100));

    Character girl2(girl2_asset, sf::Vector2f(0.5, 0.5), sf::Vector2f(100, -50));





    // Haley implemented the menu buttons
    sf::Texture btnTexture;
    btnTexture.loadFromFile("Textures/pink-button.png");
    Button playGameBtn(sf::Vector2f(300, 150), sf::Vector2f(750, 450), btnTexture, "Play Game");
    playGameBtn.setButtonTextFont(font);

    Button aboutGameBtn(sf::Vector2f(300, 150), sf::Vector2f(750, 525), btnTexture, "About Game");
    aboutGameBtn.setButtonTextFont(font);

    sf::Texture exitBtnTexture;
    exitBtnTexture.loadFromFile("Textures/exit.png");
    Button exitBtn(sf::Vector2f(200, 100), sf::Vector2f(1250, 700), exitBtnTexture, "Exit");
    exitBtn.setButtonTextFont(font);

    // Haley designed and implemented the about screen - exit button stays the same, changing position of play game button
    Button newPlayGameBtn(sf::Vector2f(300, 150), sf::Vector2f(580, 600), btnTexture, "Play Game");
    newPlayGameBtn.setButtonTextFont(font);
    // Haley wrote the summary of the game
    sf::Text aboutText;
    aboutText.setFont(font);
    aboutText.setCharacterSize(30);
    aboutText.setFillColor(sf::Color::White);
    aboutText.setStyle(sf::Text::Regular);
    aboutText.setString("\"Code to My Heart\" is an exciting dating simulator that puts your \ncomputer science knowledge to the test. In this game, you take \non the role of a protagonist who's trying to win the heart of the \nlove interest, Clara, by answering challenging questions related \nto programming, computer science, and technology. As you progress \nthrough the game, you'll face increasingly difficult questions that \nwill test your knowledge and skills.");
    aboutText.setPosition(260, 250);


    // use this to click thru text
    Button continue_button(sf::Vector2f(1400, 569), sf::Vector2f(-20, 350), empty_texture, "");


    // input question, improved my Simon and Josh originally was created by Zack
    sf::RectangleShape inputBox(sf::Vector2f(300, 80));
    inputBox.setPosition(50, 50);
    inputBox.setOutlineThickness(2);
    inputBox.setOutlineColor(sf::Color::Black);
    inputBox.setFillColor(sf::Color::White);

    sf::Text inputText("What is a struct?", font, 20);
    inputText.setPosition(60, 60);
    inputText.setFillColor(sf::Color::Black);

    /* Originally done in my Panda Level on my Branch utilzied the 4 buttons crrated, Josh and Simon modified to use Joshs button class */


    /* First button */
    Button button1(sf::Vector2f(500, 100), sf::Vector2f(50, 150), sf::Texture(), "A data type that groups several related variables in one place");
    button1.setOutlineThickness(2);
    button1.setOutlineColor(sf::Color::Black);
    button1.setFillColor(sf::Color::Blue);
    button1.setButtonTextSize(17);
    button1.setButtonTextFont(font);
    button1.setButtonTextOrigin();
    button1.setButtonTextPos(sf::Vector2f(300, 200));


    Button button2(sf::Vector2f(500, 100), sf::Vector2f(50, 250), sf::Texture(), "A dynamic data structure that holds multiple functions ");
    button2.setOutlineThickness(2);
    button2.setOutlineColor(sf::Color::Black);
    button2.setFillColor(sf::Color::Blue);
    button2.setButtonTextSize(17);
    button2.setButtonTextFont(font);
    button2.setButtonTextOrigin();
    button2.setButtonTextPos(sf::Vector2f(300, 300));

    Button button3(sf::Vector2f(500, 100), sf::Vector2f(50, 350), sf::Texture(), "A dynamic data structure that holds multiple functions ");
    button3.setOutlineThickness(2);
    button3.setOutlineColor(sf::Color::Black);
    button3.setFillColor(sf::Color::Blue);
    button3.setButtonTextSize(17);
    button3.setButtonTextFont(font);
    button3.setButtonTextOrigin();
    button3.setButtonTextPos(sf::Vector2f(300, 400));

    Button button4(sf::Vector2f(500, 100), sf::Vector2f(50, 450), sf::Texture(), "A dynamic data structure that holds multiple functions ");
    button4.setOutlineThickness(2);
    button4.setOutlineColor(sf::Color::Black);
    button4.setFillColor(sf::Color::Blue);
    button4.setButtonTextSize(17);
    button4.setButtonTextFont(font);
    button4.setButtonTextOrigin();
    button4.setButtonTextPos(sf::Vector2f(300, 500));

    bool isFullscreen = true;
    bool menuMode = true;
    bool aboutMode = false;

    music.play();

    /* Simon wrote first scene, Zack wrote latter */
    std::ifstream file("lines.txt");

    int i = 0, failsafe = 0, win_condition = 0;
    bool Current_State = true;
    while (window.isOpen())
    {

        sf::Event event;
 
        while (window.pollEvent(event))
        {
            window.clear();
            window.draw(background);

            if (event.type == sf::Event::Closed)
                window.close();

            // Haley implemented the exit button
            if (exitBtn.isBeingPushed(window)) {
                window.close();
            }

            // Display all of the menu features - Haley implemented this
            if (menuMode) {
                aboutGameBtn.draw(window);
                exitBtn.draw(window);
                playGameBtn.draw(window);
                window.draw(girl2);

                // someone else did this - Haley debugged it
                if (event.type == sf::Event::Resized) {
                    isFullscreen = !isFullscreen; // It'll alternate each time we go back and forth between fullscreen and not fullscreen
                    if (isFullscreen) window.create(sf::VideoMode(1050, 789), "Code to my Heart");
                    if (!isFullscreen) window.create(sf::VideoMode::getFullscreenModes()[0], "Code to my Heart");

                    resetBackgroundScale(window, menuBackgroundTexture, menuBackground);
                }

                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                    if (isFullscreen) window.create(sf::VideoMode(1050, 789), "Code to my Heart");
                    if (!isFullscreen) window.create(sf::VideoMode::getFullscreenModes()[0], "Code to my Heart");

                    resetBackgroundScale(window, menuBackgroundTexture, menuBackground);

                    isFullscreen = !isFullscreen; // It'll alternate each time we go back and forth between fullscreen and not fullscreen
                }

               
                if (playGameBtn.isBeingPushed(window)) {
                    resetBackgroundScale(window, gameBackgroundTexture, background);
                    music.pause();
                    menuMode = false;
                }

                // Haley implemented moving to the about screen
                if (aboutGameBtn.isBeingPushed(window)) {
                    resetBackgroundScale(window, aboutBackgroundTexture, background);
                    aboutMode = true;
                    menuMode = false;
                }
            }
            else if (aboutMode) {
                
                // someone else did this
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                    if (isFullscreen) window.create(sf::VideoMode(1050, 789), "Code to my Heart");
                    if (!isFullscreen) window.create(sf::VideoMode::getFullscreenModes()[0], "Code to my Heart");
                    resetBackgroundScale(window, aboutBackgroundTexture, aboutBackground);
                    isFullscreen = !isFullscreen; // It'll alternate each time we go back and forth between fullscreen and not fullscreen
                }

                // Haley implemented the about screen features
                exitBtn.draw(window);
                newPlayGameBtn.draw(window);
                window.draw(aboutText);

                if (newPlayGameBtn.isBeingPushed(window)) {
                    resetBackgroundScale(window, gameBackgroundTexture, background);
                    aboutMode = false;
                }
            }
            
            // Run the game, beggining of Simon's code
            else {
                if (i ==  6) { resetBackgroundScale(window, sceneOneTexture, background); }
           
                if (i == 8)
                {
                    scene1_music.play();
                }
                if (i >= 8)
                {
                    window.draw(girl.getDrawableObject());
                    
                }

                window.draw(rec_shape);
                window.draw(text);
                exitBtn.draw(window);
                if (i == 6) { 
                    resetBackgroundScale(window, sceneOneTexture, background);
                    if (event.type == sf::Event::Resized) {
                        resetBackgroundScale(window, sceneOneTexture, background);
                    }


                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
                        if (isFullscreen) window.create(sf::VideoMode(1050, 789), "Code to my Heart");
                        if (!isFullscreen) window.create(sf::VideoMode::getFullscreenModes()[0], "Code to my Heart");

                        resetBackgroundScale(window, sceneOneTexture, background);

                        isFullscreen = !isFullscreen; // It'll alternate each time we go back and forth between fullscreen and not fullscreen
                    }
                    exitBtn.draw(window);

                }

                if (i < 29 && continue_button.isBeingPushed(window)  )
                {
                    ++i;
                    text.setString(readFromFile(file));

                }
                
                /* Zack: Originally Created on my Branch, coded the question prompt code   */
                /* The mouse pos code and the drawing of the buttons                      */

                if (i == 29 && failsafe == 0)
                {
                    window.draw(inputBox);
                    window.draw(inputText);
                    button1.draw(window);
                    button2.draw(window);
                    button3.draw(window);
                    button4.draw(window);

                    girl.set_the_Position(sf::Vector2f(800, -100));

                    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
                    {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

                        if (button1.isBeingPushed(window))
                        {
                            text.setString("Good job! If you failed this one I would be concerned...");
                            ++i;
                            ++failsafe;
                            girl.set_interest(win_condition++);
                        }

                        if (button2.isBeingPushed(window) || button3.isBeingPushed(window) || button4.isBeingPushed(window))
                        {
                            std::cout << "Wrong Answer!" << std::endl;
                            text.setString("How did you get it wrong??? Maybe you're not as good as I thought...");
                            ++failsafe;
                            ++i;
                        }
                      
                    }
                }
                if (i == 30 && continue_button.isBeingPushed(window)) { i++; }

                if (i == 31 && failsafe == 1)
                {
                    text.setString("If you can't answer this one, you're an idiot!");
                    inputText.setString("What is a private member of a class?");
                    button1.setButtonText("A variable or function that cannot be accessed \nfrom the outside of a class");
                    button2.setButtonText("Idk");
                    button3.setButtonText("A member that can only be accessed using a friend function");
                    button4.setButtonText("A member of a class that is protected");
                    window.draw(inputBox);
                    window.draw(inputText);
                    button1.draw(window);
                    button2.draw(window);
                    button3.draw(window);
                    button4.draw(window);

                    if (button1.isBeingPushed(window))
                    {
                        text.setString("Nice! People who are smart are hot ;)");
                        ++i;
                        ++failsafe;
                        win_condition++;
                        girl.set_interest(win_condition++);
                    
                    }
                    
                    if (button2.isBeingPushed(window) || button3.isBeingPushed(window) || button4.isBeingPushed(window))
                    {
                        std::cout << "Wrong Answer!" << std::endl;
                        text.setString("Wrong! You're getting uglier the more you get things wrong...");
                        ++i;
                        ++failsafe;
                    }

                    
                }

                if (i == 32 && continue_button.isBeingPushed(window)) { i++; }

                if (i == 33 && failsafe == 2)
                {
                    text.setString("Let's make things a little more challenging!");
                    inputText.setString("Give the big O notation \nfor bubble sort!");
                    button1.setButtonText("O(n^2)");
                    button2.setButtonText("O(n)");
                    button3.setButtonText("O(logn)");
                    button4.setButtonText("O(logn * n");
                    window.draw(inputBox);
                    window.draw(inputText);
                    button1.draw(window);
                    button2.draw(window);
                    button3.draw(window);
                    button4.draw(window);


                    if (button1.isBeingPushed(window))
                    {
                        text.setString("Your good at this hehe");
                        ++i;
                        ++failsafe;
                        girl.set_interest(win_condition++);
                    }

                    if (button2.isBeingPushed(window) || button3.isBeingPushed(window) || button4.isBeingPushed(window))
                    {
                        std::cout << "Wrong Answer!" << std::endl;
                        text.setString("Basic knowledge, do you actually know how to code?");
                        ++i;
                        ++failsafe;
                    }

                }
                if (i == 34 && continue_button.isBeingPushed(window)) { i++; }

                if (i == 35 && failsafe == 3)
                {
                    text.setString("One more and we're done!");
                    inputText.setString("What's your favorite coding language?");
                    button1.setButtonText("Python");
                    button2.setButtonText("C");
                    button3.setButtonText("C++");
                    button4.setButtonText("Java");
                    window.draw(inputBox);
                    window.draw(inputText);
                    button1.draw(window);
                    button2.draw(window);
                    button3.draw(window);
                    button4.draw(window);


                    if (button1.isBeingPushed(window))
                    {
                        text.setString("Ew, too basic for my tastes...");
                        ++i;
                        ++failsafe;
                    }

                    if (button2.isBeingPushed(window) || button3.isBeingPushed(window))
                    {

                        text.setString("No way! I love anything related to C!");
                        ++i;
                        ++failsafe;
                        girl.set_interest(win_condition++);

                    }

                    if (button4.isBeingPushed(window))
                    {
                        text.setString("You like java??? Ewwwww......");
                        ++i;
                        ++failsafe;
                    }
                }
                
                if (i >= 36 && i < 45 && (girl.get_interest() >= 3) && continue_button.isBeingPushed(window))
                {
                    scene1_music.stop();
                    ++i;
                    text.setString(readFromFile(file));
                }
                
                if (i == 36 && (girl.get_interest() < 3) && continue_button.isBeingPushed(window))
                {
                    text.setString("As I thought, you're an idiot!. Have a nice life!");
                    // Haley designed and implemented the cafe losing screen
                    resetBackgroundScale(window, cafeLoseBackground, background);
                }
                // end of Simon's code as it is the end of scene
                /* Zack: Panda Level, I worked on this originally on my branch and looked little different, Simon and I differed on how our games progressed */
                /* Cause mine progressed in a way that conflicted with Simons, I decided to code and abrige my Panda level                                  */
               
                if (i == 45)
                {
                    resetBackgroundScale(window, gamePandaExterior, background);

                /* Zack really proud of this Zooming effect that pans into the panda store think its cool                                               */

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

                    resetBackgroundScale(window, gamePandaInterior, background);
                   
                    ++i;
                    std::cout << i;

                    text.setString(readFromFile(file));
                   
                }
                
                if (i == 46)
                {
                    scene2_music.play();
                }
                if ( i >= 46 && i < 50 && continue_button.isBeingPushed(window))
                {
                    
                    ++i;
                    std::cout << i;
                    text.setString(readFromFile(file));
                }

               
                if (i >= 50 && i < 51 )
                {
                   
                    text.setString("Can you holy c my temple!");
                    inputText.setString("What is equivalent of main in Holy c?");
                    button1.setButtonText("holy()");
                    button2.setButtonText("praise_the_lord()");
                    button3.setButtonText("start()");
                    button4.setButtonText("andrewOFallon()");
                    window.draw(inputBox);
                    window.draw(inputText);
                    button1.draw(window);
                    button2.draw(window);
                    button3.draw(window);
                    button4.draw(window);


                    if (button1.isBeingPushed(window))
                    {
                        text.setString("Really... that would be too easy, you're going to be frying in that orange chicken bowl");
                        ++i;
                        ++failsafe;
                        gameWon = 3;
                    }

                    if (button2.isBeingPushed(window))
                    {

                        text.setString("Hello New Boyfriend, I wanna take you home and pull from your repository ");
                        ++i;
                        ++failsafe;
                        gameWon = 1;

                    }


                    if (button3.isBeingPushed(window))
                    {

                        text.setString("Ewww, you're not starting my main program, knife knife ");
                        ++i;
                        ++failsafe;
                        gameWon = 3;

                    }

                    if (button4.isBeingPushed(window))
                    {
                        text.setString("Ah yes the best comp sci proffesor");
                        ++i;
                        gameWon = 1;
                    }
                }

                /* Zack: Wish this was better but last night came up with easy system to change the window based on who wins */

                if (gameWon == 1)
                {
                    resetBackgroundScale(window, cars, background);
                    std::cout << "Damm ya won";
                }
                
                if (gameWon == 3)
                {
                   
                   
                    resetBackgroundScale(window, pandaLoseBackground, background);

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