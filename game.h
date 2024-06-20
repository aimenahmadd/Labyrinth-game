#pragma once
#include <SFML/Graphics.hpp>
#include <time.h>
#include <SFML/System.hpp>
#include <iostream>

using namespace sf;

#include"Player.h"
#include"Enemy.h"
#include"Animation.h"
#include"Menu.h"
#include"Maze.h"
#include"Coin.h"
#include"Potion.h"
#include"Weapons.h"
#include"Item.h"
#include"Inventory.h"
#include"InventoryDisplay.h"
#include"Audio.h"


class Game :public Audio
{
public:
    Sprite background;
    Texture bg_texture;

    Vector2u TextureSize;
    Vector2u WindowSize;

    //==========================

    Player p1;
    Enemy enemy[6];
    Maze maze;

    Coin coinGenerator, coins[15];
    Potion potion, potionz[3];
    Event event;
    Weapon dagger, daggers[4];

    inventorydisplay boxes[5], score;

    Clock enemyCollisionClock;
    float enemyCollisionTimer;

    bool summon = true;

    int numCoins = 15, numPotions = 3, numWeapons = 4, numEnemy = 6;

    float Xpos[3], Ypos[3], Xsize[3], Ysize[3], Xmouse, Ymouse;

    //===========================

    Game()
    {
        bg_texture.loadFromFile("pngs/background1.jpg");
        background.setTexture(bg_texture);
    }

    void startgame()
    {
        gametheme();

        sf::RenderWindow window(sf::VideoMode(1900, 1000), "Game");

        if (!bg_texture.loadFromFile("pngs/background1.jpg"))
            return;

        background.setTexture(bg_texture);

        maze.readFromFile("pngs/Maze/maze1.txt");

        //========================

        dagger.generateWeapons(daggers, numWeapons, maze.getArray(), maze.getRows(), maze.getColumns());

        coinGenerator.generateCoins(coins, numCoins, maze.getArray(), maze.getRows(), maze.getColumns());

        potion.generatePotions(potionz, numPotions, maze.getArray(), maze.getRows(), maze.getColumns());

        enemy->generateEnemy(enemy, numEnemy, maze.getArray(), maze.getRows(), maze.getColumns());

        //=========================

        float deltaTime = 0.0f;
        Clock clock;

        while (window.isOpen() && !isGameOver())
        {
            deltaTime = clock.restart().asSeconds();

            enemyCollisionTimer = enemyCollisionClock.getElapsedTime().asSeconds();

            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();

                if (event.type == sf::Event::KeyPressed)
                    p1.processevent(event.key.code, true);

                if (event.type == sf::Event::KeyReleased)
                    p1.processevent(event.key.code, false);
            }

            TextureSize = bg_texture.getSize();
            WindowSize = window.getSize();
            float ScaleX = (float)WindowSize.x / TextureSize.x;
            float ScaleY = (float)WindowSize.y / TextureSize.y;
            background.setScale(ScaleX, ScaleY);

            window.draw(background);

            maze.drawMaze(window);

            //=========================

            p1.update(maze.getArray(), maze.getRows(), maze.getColumns());

            p1.drawplayer(window);
            p1.playeranimationupdate(deltaTime);
            p1.knight.setTextureRect(p1.animation.uvRect);

            if (enemyCollisionTimer > 1) {
                p1.checkEnemyCollision(enemy, numEnemy, p1, window, deltaTime, enemyCollisionTimer, enemyCollisionClock);
            }
            //=========================

            for (int i = 0; i < numCoins; i++)
            {
                if (i < numPotions && potionz[i].visible)
                {
                    potionz[i].draw(window);
                    potionz[i].updateAnimation(deltaTime);
                    potionz[i].item.setTextureRect(potionz[i].animation.uvRect);
                }

                if (i < numEnemy)
                {
                    enemy[i].draw(window);
                    enemy[i].updateAnimation(deltaTime);
                    enemy[i].skeleton.setTextureRect(enemy[i].animation.uvRect);
                }

                if (i < numWeapons && daggers[i].visible)
                {
                    daggers[i].draw(window);
                    daggers[i].updateAnimation(deltaTime);
                    daggers[i].item.setTextureRect(daggers[i].animation.uvRect);
                }

                if (coins[i].visible)
                {
                    coins[i].draw(window);
                    coins[i].updateAnimation(deltaTime);
                    coins[i].item.setTextureRect(coins[i].animation.uvRect);
                }

            }

            //=========================

            score.total_score_display(window, p1);
            boxes[0].main_display(window);
            boxes[1].small_display(510, 810, window, deltaTime, p1);
            boxes[2].small_display(655, 810, window, deltaTime, p1);
            boxes[3].small_display(510, 905, window, deltaTime, p1);
            boxes[4].small_display(655, 905, window, deltaTime, p1);
            boxes[0].rulesdisplay(window);

            //=========================

            p1.checkCoinCollision(coins, numCoins);
            p1.checkPotionCollision(potionz, numPotions);
            p1.checkWeaponCollision(daggers, numWeapons);

            //=========================

            window.display();
        }

        p1.val->display1();
        p1.val->destroyTree(p1.val->root);

    }
   
    ~Game() 
    {
        if (p1.val) 
        {
            p1.val->destroyTree(p1.val->root); 
        }
    }


    bool isGameOver() {
        if (p1.score < 0) 
        {
            return true;
        }
        return false;
    }

};