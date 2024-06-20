#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

using namespace sf;

#include"game.h"
#include"Audio.h"
#include"instructions.h"
#include"Background.h"

class Menu : public Instructions, public Audio
{

public:
    Sprite buttonsprite[3];;
    Texture buttontexture;

    Text title, op[3];
    Font font1, options;

    Vector2u TextureSize;  
    Vector2u WindowSize;

    Background background;

    float Xpos[3], Ypos[3], Xsize[3], Ysize[3] , Xmouse, Ymouse;

    Menu()
    {
        font1.loadFromFile("pngs/mainmenu/headingfont.ttf");
        options.loadFromFile("pngs/mainmenu/options.ttf");

        title.setFont(font1);
        title.setFillColor(Color::Color(72, 74, 41));
        title.setOutlineColor(Color::Black);
        title.setString("Backrooms: Labyrinth Ed");
        title.setPosition(200, 220);
        title.setCharacterSize(110);
        title.setOutlineThickness(6);

        //=============================================

        buttontexture.loadFromFile("pngs/mainmenu/white.png");

        int xCord = 1200, yCord = 400;

        for (int i = 0; i < 3; i++)
        {
            op[i].setFont(options);
            op[i].setFillColor(Color::White);
            op[i].setOutlineColor(Color::Black);
            op[i].setPosition(xCord, yCord);
            op[i].setCharacterSize(70);

            buttonsprite[i].setTexture(buttontexture);

            buttonsprite[i].setPosition(xCord, yCord+25);
            buttonsprite[i].setScale(2, 1.2);
            yCord += 220;            
        }

        op[0].setString("  Start Game");
        op[1].setString("  How To Play");
        op[2].setString("  Quit Game");

        display_menu();
    }    

    void display_menu()
    {
        Game g;
        Audiomenu();

        sf::RenderWindow window(sf::VideoMode(1900, 1000), "Backrooms: Labyrinth Ed");

        for (int i = 0; i < 3; i++)
        {
            sf::FloatRect spriteSize = buttonsprite[i].getGlobalBounds();

            Xpos[i] = buttonsprite[i].getPosition().x;
            Ypos[i] = buttonsprite[i].getPosition().y;
            Xsize[i] = spriteSize.width;
            Ysize[i] = spriteSize.height;
        }

        Event event;
        float deltaTime = 0.1f;
        Clock clock;

        while (window.isOpen())
        {
            deltaTime = clock.restart().asSeconds();

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            background.draw(window);
            background.updateAnimation(deltaTime);
            background.item.setTextureRect(background.animation.uvRect);

            window.draw(title);

            for (int i = 0; i < 3; i++)
            {
                window.draw(buttonsprite[i]);
                window.draw(op[i]);
            }

            window.display();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                Xmouse = sf::Mouse::getPosition(window).x;
                Ymouse = sf::Mouse::getPosition(window).y;

                if ((Xmouse >= 1200 && Xmouse <= 1200 + Xsize[0] && Ymouse >= 425 && Ymouse <= 425 + Ysize[0]) == true)
                {
                    selectaudio();

                    g.startgame();

                }

                else if ((Xmouse >= 1200 && Xmouse <= 1200 + Xsize[1] && Ymouse >= 645 && Ymouse <= 645 + Ysize[1]) == true)
                {
                    selectaudio();

                    window.clear(Color::Black);
                    display_instructions();
                }

                if ((Xmouse >= 1200 && Xmouse <= 1200 + Xsize[2] && Ymouse >= 870 && Ymouse <= 870 + Ysize[2]) == true)
                {
                    selectaudio();

                    window.clear(Color::Black);
                    window.close();
                }
            }
        }

    }   
    
};