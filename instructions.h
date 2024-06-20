#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
using namespace sf;
#include"game.h"
#include"Audio.h"


class Instructions
{
public:
    Texture bg_texture; 
    Sprite background;
    Texture menutexture;

    Text titlee, text;
    Font instfont;

    Vector2u TextureSize;
    Vector2u WindowSize;

    Instructions()
    {
        instfont.loadFromFile("pngs/mainmenu/options.ttf");
        
        bg_texture.loadFromFile("pngs/instructions_bg.png");
        background.setTexture(bg_texture);

        titlee.setFont(instfont);
        titlee.setFillColor(Color::White);
        titlee.setOutlineColor(Color::Black);
        titlee.setString("Instructions");
        titlee.setPosition(100, 100);
        titlee.setCharacterSize(100);
        titlee.setOutlineThickness(5);

        text.setFont(instfont);
        text.setFillColor(Color::White);
        text.setOutlineColor(Color::Black);
        text.setPosition(170, 350);
        text.setCharacterSize(75);
        text.setOutlineThickness(5);
        text.setString("Explore the Labyrinth and collect items that will help you\nalong your journey. \n  W\nA S D controls for movement\n\nE to attack\nQfor defending.\n Press P for potion\nPress O To instantly kill enemy if you have a weapon in inventory");
    }

    void display_instructions()
    {       
        sf::RenderWindow window(sf::VideoMode(1900, 1000), "Instructions");

        while (window.isOpen())
        {
            Event e;

            while (window.pollEvent(e)) 
            {
                if (e.type == Event::Closed)
                    window.close();
            }

            TextureSize = bg_texture.getSize();
            WindowSize = window.getSize();
            float ScaleX = (float)WindowSize.x / TextureSize.x;
            float ScaleY = (float)WindowSize.y / TextureSize.y;
            background.setScale(ScaleX, ScaleY);

            window.draw(background);
            //window.clear(Color::Black);
            window.draw(titlee);
            window.draw(text);
            window.display();

            if (e.type == Event::KeyPressed)
            {
                window.close();
            }
        }

    }
};