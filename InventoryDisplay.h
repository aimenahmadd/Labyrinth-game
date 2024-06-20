#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream> 

#include"skull.h"
#include"Animation.h"
#include"Coin.h"
#include"Potion.h"
#include"Weapons.h"
#include"Item.h"

#include"Player.h"

using namespace sf;
using namespace std;

class inventorydisplay
{
protected:

    RectangleShape box;
    Texture texture, texture1;

    int length, width;

    Coin coin;
    Potion potion;
    Weapon weapon;
    skull skull;
    Text countext, total_score, rules;
    Font font;


public:

    inventorydisplay()
    {
        texture.loadFromFile("pngs/id/small.png");
        texture1.loadFromFile("pngs/id/inventorydisplaymain.png");

        font.loadFromFile("pngs/mainmenu/options.ttf");
        rules.setFont(font);

        countext.setCharacterSize(35);

        countext.setFont(font); 
        countext.setFillColor(sf::Color::White); 

        total_score.setCharacterSize(35);

        total_score.setFont(font);
        total_score.setFillColor(sf::Color::White);
    }

    void total_score_display(RenderWindow& window, Player& p)
    {
        total_score.setCharacterSize(60);
        total_score.setPosition(50, 70);

        std::stringstream ss;
        ss << "SCORE: " << p.score; 
        total_score.setString(ss.str());
        window.draw(total_score);
    }

    void main_display(RenderWindow& window)
    {
        box.setTexture(&texture1);
        box.setPosition(800, 800);
        box.setSize(sf::Vector2f(500, 200));

        window.draw(box);
    }

    void small_display(int l, int w, RenderWindow& window, float dt, Player& p)
    {
        length = l, width = w;

        box.setTexture(&texture);
        box.setPosition(l, w);
        box.setSize(sf::Vector2f(150, 100));

        window.draw(box);

        if (l == 510)
        {
            if (w == 810)
            {
                coin.gen(555, 840);
                coin.draw(window);
                coin.updateAnimation(dt);
                coin.item.setTextureRect(coin.animation.uvRect);

                countext.setPosition(590, 855);

                int nc = p.val->search(coin.key); 
                std::stringstream ss;
                ss << "X" << nc;
                countext.setString(ss.str());
                window.draw(countext);

            }

            else if (w == 905)
            {
                weapon.gen(555, 930);
                weapon.draw(window);
                weapon.updateAnimation(dt);
                weapon.item.setTextureRect(weapon.animation.uvRect);

                countext.setPosition(590, 950);

                int nw = p.val->search(weapon.key);
                std::stringstream ss;
                ss << "X" << nw;
                countext.setString(ss.str());
                window.draw(countext);
            }
        }

        else if (l == 655)
        {
            if (w == 810)
            {                
                potion.gen(680, 840);
                potion.draw(window);
                potion.updateAnimation(dt);
                potion.item.setTextureRect(potion.animation.uvRect);

                countext.setPosition(740, 855);

                int np = p.val->search(potion.key);
                std::stringstream ss;
                ss << "X" << np;
                countext.setString(ss.str());
                window.draw(countext);
            }

            else if (w == 905)
            {
                skull.gen(700, 930);
                skull.draw(window);
                skull.updateAnimation(dt);
                skull.item.setTextureRect(skull.animation.uvRect);


                countext.setPosition(740, 950);
                std::stringstream ss;
                ss << "X" << Enemy::numEnemiesKilled;
                countext.setString(ss.str());
                window.draw(countext);
            }
        }
    }    

    void rulesdisplay(RenderWindow& window)
    {
        rules.setFillColor(Color::White);
        rules.setOutlineColor(Color::Black);
        rules.setPosition(870, 830);
        rules.setCharacterSize(35);
        rules.setString("  W\nA S D controls for movement\nE : attack  Q : Defend.\nP for potion  O : Weapon ");
        window.draw(rules);

    }
    

};

