#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>

#include"Animation.h"
#include"Inventory.h"

#include"Coin.h"
#include"Potion.h"
#include"Weapons.h"

#include"Enemy.h"

using namespace std;
using namespace sf;


class Player
{
public:
    RectangleShape knight;
    Texture texture;
    bool up, down, right, left, attack, block;
    bool idrk, idle, leftidle = false;
    bool attacking = false , blocking=false, useSword;

    Potion potion;
    int xtexture;
    int count = 1;
    int posX, posY;

    Weapon weapon;

    Animation animation;
    inventory<Item>* val;

    int cc = 0, pc = 0, wc = 0, score = 0;

    const Texture& getTexture()
    {
        texture.loadFromFile("pngs/Entity/idleplayer.png");
        return texture;
    }
    
    Player(inventory<Item>* inv) : val(inv) {}


    Player() : animation(getTexture(), knight, Vector2u(8, 1), 0.1f)
    {
        val = new inventory<Item>();

        posX = 2;
        posY = 23;

        knight.setSize(Vector2f(40, 40));
        knight.setOrigin(-15, 10);

        knight.setPosition(posX * 25 + 20, posY * 25 + 140);

        if (!texture.loadFromFile("pngs/Entity/idleplayer.png"))
        {
            return;
        }

        knight.setTexture(&texture);
        up = down = left = right = idrk = false;
        idle = leftidle = true;
        attacking = false;
        blocking = false;

    }

    void processevent(sf::Keyboard::Key key, bool checkPressed)
    {
        if (checkPressed == true)
        {
            if (key == sf::Keyboard::W)
                up = true;

            if (key == sf::Keyboard::S)
                down = true;

            if (key == sf::Keyboard::D)
            {
                leftidle = false;
                right = true;
                idrk = false;
            }

            if (key == sf::Keyboard::A)
            {
                leftidle = true;
                left = true;
                idrk = true;
            }

            if (key == sf::Keyboard::E)
            {
                attacking = true; 
                attack = true;
            }

            if (key == sf::Keyboard::O) 
            {
                useSword = true;
            }

            if (key == sf::Keyboard::P)
            {
                if (val->search(potion.key) > 0)
                {
                    score += 50; 
                    val->removenum(potion.key); 
                }
            }
        }

        if (checkPressed == false)
        {
            up = down = left = right = attack = block = useSword= false;
        }
    }

    void xleftmovement()
    {
        texture.loadFromFile("pngs/Entity/walkingplayerL.png");
        xtexture = 0;
        xtexture = ((int)knight.getPosition().x / 15) % 8;
        xtexture *= 83;
        knight.setTextureRect(sf::IntRect(xtexture, 0, 83, 96));
    }

    void yleftmovement()
    {
        texture.loadFromFile("pngs/Entity/walkingplayerL.png");
        xtexture = 0;
        xtexture = ((int)knight.getPosition().y / 15) % 8;
        xtexture *= 83;
        knight.setTextureRect(sf::IntRect(xtexture, 0, 83, 96));
    }

    void xrightmovement()
    {
        texture.loadFromFile("pngs/Entity/walkingplayerR.png");
        xtexture = 0;
        xtexture = ((int)knight.getPosition().x / 15) % 8;
        xtexture *= 83;
        knight.setTextureRect(sf::IntRect(xtexture, 0, 83, 96));
    }

    void yrightmovement()
    {
        texture.loadFromFile("pngs/Entity/walkingplayerR.png");
        xtexture = 0;
        xtexture = ((int)knight.getPosition().y / 15) % 8;
        xtexture *= 83;
        knight.setTextureRect(sf::IntRect(xtexture, 0, 83, 96));
    }

    void update(const int** mazeArray, int mazeRows, int mazeColumns)
    {

        float tempX = knight.getPosition().x;

        if (ceil(tempX) - tempX < 0.5) {
            posX = floor(knight.getPosition().x) / 25;
        }

        float tempY = knight.getPosition().y;

        if (ceil(tempY) - tempY < 0.5) {
            posY = floor(knight.getPosition().y) / 25 - 7;
        }

        if (up || down || left || right || attack || block)
        {
            idle = false;

            if (up)
            {
                if (idrk == false)
                    yrightmovement();
                else
                    yleftmovement();

                if (mazeArray[posY - 1][posX] != 1)
                {
                    knight.move(0, -1);
                }
            }

            else if (down)
            {
                if (idrk == false)
                    yrightmovement();
                else
                    yleftmovement();

                if (mazeArray[posY + 1][posX] != 1)
                {
                    knight.move(0, 1);
                }

            }

            else if (left) // A
            {
                xleftmovement();
                leftidle = true;
                if (mazeArray[posY][posX - 1] != 1)
                {
                    knight.move(-1, 0);
                }
            }

            else if (right) // D
            {
                xrightmovement();
                leftidle = false;

                if (mazeArray[posY][posX + 1] != 1)
                {
                    knight.move(1, 0);
                }
            }

            else if (attack)
            {
                if (leftidle)
                    texture.loadFromFile("pngs/Entity/al.png");
                else
                    texture.loadFromFile("pngs/Entity/ar.png");

                knight.setTexture(&texture);
                attacking = true;
            }

            else if (block)
            {
                attacking = false;
                blocking = true;
            }
               
        }


        else
        {
            if (!leftidle)
                texture.loadFromFile("pngs/Entity/idleplayer.png");
            else
                texture.loadFromFile("pngs/Entity/idleleft.png");

            attacking = false;
            blocking = false;

            idle = true;
        }

    }

    void checkCoinCollision(Coin coins[], int numCoins)
    {
        for (int i = 0; i < numCoins; i++)
        {
            if (knight.getGlobalBounds().intersects(coins[i].item.getGlobalBounds()) && coins[i].visible)
            {
                cc++;
                val->insert(&coins[i]);
                score += coins[i].value;

                coins[i].visible = false;

            }
        }
    }

    void checkPotionCollision(Potion potion[], int numpy)
    {
        for (int i = 0; i < numpy; i++)
        {
            if (knight.getGlobalBounds().intersects(potion[i].item.getGlobalBounds()) && potion[i].visible)
            {
                val->insert(&potion[i]);
                score += potion[i].value;

                potion[i].visible = false;

                pc++;

            }
        }
    }

    void checkWeaponCollision(Weapon weapon[], int numwep)
    {
        for (int i = 0; i < numwep; i++)
        {
            if (knight.getGlobalBounds().intersects(weapon[i].item.getGlobalBounds()) && weapon[i].visible)
            {
                val->insert(&weapon[i]);
                score += weapon[i].value;

                weapon[i].visible = false;

                wc++;
            }
        }
    }

    void checkEnemyCollision(Enemy enemies[], int numEnemy, Player& p, RenderWindow& window, float dt, float& enemyCollisionTimer, Clock& collisionClock)
    {
        for (int i = 0; i < numEnemy; i++)
        {
            if (knight.getGlobalBounds().intersects(enemies[i].skeleton.getGlobalBounds()))
            {
                sf::Vector2f playerPos = knight.getPosition();
                sf::Vector2f enemyPos = enemies[i].skeleton.getPosition();

                float dx = enemyPos.x - playerPos.x;
                float dy = enemyPos.y - playerPos.y;


                if (std::abs(dx) > std::abs(dy))
                {
                    if (dx > 0)
                    {
                        enemies[i].changeTextureLeft();

                        if (p.attacking)
                        {

                            if (enemies[i].hp <= 0) 
                            {
                                enemies[i].skeleton.setPosition(-1000, -1000);
                                Enemy::incrementEnemiesKilled();

                            }

                            else
                            {
                                enemies[i].hp -= 50;
                            }

                           

                            p.blocking = false;

                        }
                       
                        else if (!p.blocking && enemies[i].enemy_attack && !useSword)
                        {
                            enemies[i].animation.playfull(0, enemies[i].skeleton, window, dt);
                            p.score -= enemies[i].attack;
                            enemyCollisionTimer = 0;
                            collisionClock.restart();

                            if (p.attacking)
                            {

                                if (enemies[i].hp <= 0)
                                {
                                    enemies[i].skeleton.setPosition(-1000, -1000);
                                    Enemy::incrementEnemiesKilled();

                                }

                                else
                                {
                                    enemies[i].hp -= 50;
                                }

                                p.blocking = false;

                            }
                        }
                        else if (useSword && val->search(weapon.key) > 0) 
                        {
                            enemies[i].skeleton.setPosition(-1000, -1000); 
                            enemies[i].hp = 0; 
                            useSword = false; 
                            val->removenum(weapon.key); 
                            Enemy::incrementEnemiesKilled();

                        }

                        else
                        {
                            p.attacking = false;
                            p.blocking = true;
                            continue;
                        }
                    }

                    else
                    {
                        enemies[i].changeTextureRight();

                        if (p.attacking)
                        {

                            if (enemies[i].hp <= 0)
                            {
                                enemies[i].skeleton.setPosition(-1000, -1000);
                                Enemy::incrementEnemiesKilled();
                            }

                            else
                            {
                                enemies[i].hp -= 50;
                            }
                            p.blocking = false;

                        }

                        else if (!p.blocking && enemies[i].enemy_attack && !useSword)
                        {
                            enemies[i].animation.playfull(0, enemies[i].skeleton, window, dt);
                            p.score -= enemies[i].attack;
                            enemyCollisionTimer = 0;
                            collisionClock.restart();

                            if (p.attacking)
                            {
                                if (enemies[i].hp <= 0)
                                {
                                    enemies[i].skeleton.setPosition(-1000, -1000);
                                    Enemy::incrementEnemiesKilled();

                                }

                                else
                                {
                                    enemies[i].hp -= 50;
                                }

                                p.blocking = false;

                            }
                        }
                        else if (useSword && val->search(weapon.key) > 0)
                        {
                            enemies[i].skeleton.setPosition(-1000, -1000);
                            enemies[i].hp = 0;
                            useSword = false;
                            val->removenum(weapon.key);
                            Enemy::incrementEnemiesKilled();

                        }
                        else
                        {
                            p.attacking = false;
                            p.blocking = true;
                            continue;
                        }
                    }
                }
                else
                {
                    enemies[i].idleenemy();
                    p.attacking = false;
                    p.blocking = false;
                }
            }
        }
    }

    void drawplayer(sf::RenderWindow& window)
    {
        window.draw(knight);
    }

    void playeranimationupdate(float deltatime)
    {
        if (idle)
            animation.Update(0, deltatime);
    }

};