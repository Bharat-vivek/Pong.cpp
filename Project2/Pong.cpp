#include "Bat.h"
#include "Ball.h"
#include <sstream>

#include <SFML/Graphics.hpp>

int main()
{
    // Create a video mode object
    VideoMode vm(1366, 768);

    // Create and open a window for the game
    RenderWindow window(vm, "Pong",Style::Fullscreen);
    // Create a bat at the bottom center of the screen
    Bat bat(1366 / 2, 768 - 20);

    // Create a ball
    Ball ball(1366 / 2, 0);
    // Create a Text object called HUD
    Text hud;

    // Load the font from the folder.
    Font font;
    font.loadFromFile("font/DS-DIGI.TTF");

    // Set the font to our retro-style
    hud.setFont(font);

    // Make it nice and big
    hud.setCharacterSize(70);

    // Choose a color
    hud.setFillColor(Color::White);
    // set string
    hud.setString("Score:0   Lives:3");

    hud.setPosition(20, 20);
    int score = 0;
    int lives = 3;

    // Here is our clock for timing everything
    Clock clock;

    while (window.isOpen())
    {
       
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                // Quit the game when the window is closed
                window.close();
        }

        // Handle the player quitting
        if (Keyboard::isKeyPressed(Keyboard::Escape))
        {
            window.close();
        }

        // Handle the pressing and releasing of the arrow keys
        if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            if(bat.getPosition().left<0)
            {
                bat.stopLeft();
            }else{
                bat.moveLeft();
            }
        }
        else
        {
            bat.stopLeft();
        }

        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            if(bat.getPosition().left+bat.getPosition().width>1370)
            {
                bat.stopRight();
            }else{
                bat.moveRight();
            }
            
        }
        else
        {
            bat.stopRight();
        }

        Time dt = clock.restart();
        // bat update
        bat.update(dt);
        // ball update
        ball.update(dt);
        

        // Update the HUD text
        std::stringstream ss;
        ss << "Score: " << score << "  Lives: " << lives;
        hud.setString(ss.str());
        
        // Handle ball hitting the bottom
        if (ball.getPosition().top > window.getSize().y)
        {
            // Reverse the ball direction
            ball.reboundBottom();

            // Remove a life
            lives--;

            // Check for zero lives
            if (lives < 1)
            {
                // reset the score
                score = 0;
                // reset the lives
                lives = 3;
            }
        }

        // Handle ball hitting top
        if (ball.getPosition().top < 0)
        {
            ball.reboundBatOrTop();

            // Add a point to the players score
            score++;
        }

        // Handle ball hitting sides
        if (ball.getPosition().left < 0 ||
            ball.getPosition().left + 
            ball.getPosition().width > window.getSize().x)
        {
            ball.reboundSides();
        }

        // When the ball hit the bat?
        if (ball.getPosition().intersects(bat.getPosition()))
        {
            score++;
            ball.reboundBatOrTop();
        }
       
        window.clear();
        //draw all the requirment.
        window.draw(hud);
        window.draw(bat.getShape());
        window.draw(ball.getShape());
        window.display();
    }

    return 0;
}
// g++ Bat.cpp Ball.cpp Pong.cpp  -lsfml-graphics -lsfml-window -lsfml-system
