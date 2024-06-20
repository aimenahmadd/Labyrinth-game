#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include"Animation.h"
#include"Inventory.h"
#include"Maze.h"
#include"Item.h"

#include <cstdlib> 
#include <ctime>   
#include <random> 

std::mt19937 rng2(std::random_device{}());

using namespace sf;
class Weapon : public Item
{
public:
    Animation animation;

    Weapon() : animation(getTexture(), item, Vector2u(17, 1), 0.1f), Item()
    {
        texture.loadFromFile("pngs/items/dagger.png");
        item.setSize(sf::Vector2f(40, 40));
        key = 50;
        value = 15;
        name = "weapon";
    }

    const Texture& getTexture()
    {
        texture.loadFromFile("pngs/items/dagger.png");
        return texture;
    }

    void generateWeapons(Weapon weapons[], int& numofweapons, const int** mazeArray, int rows, int columns)
    {
        std::uniform_int_distribution<int> dist_roww(1, rows - 2);
        std::uniform_int_distribution<int> dist_coll(1, columns - 2);

        int count = 0;

        int** occupiedPositions = new int* [numofweapons];
        for (int i = 0; i < numofweapons; ++i)
        {
            occupiedPositions[i] = new int[2];
        }

        while (count < numofweapons)
        {
            int rn = dist_roww(rng2);
            int rn1 = dist_coll(rng2);

            if (mazeArray[rn][rn1] == 0 && !isPositionOccupied(occupiedPositions, count, rn, rn1))
            {
                weapons[count].item.setTexture(&texture);
                weapons[count].item.setPosition((rn1 * 25) + 20, (rn * 25) + 170);
                occupiedPositions[count][0] = rn;
                occupiedPositions[count][1] = rn1;
                count++;
            }
        }
    }

    void gen(int l, int w)
    {
        item.setTexture(&texture);
        item.setPosition(l, w);
        item.setSize(sf::Vector2f(50, 50));
    }

    bool isPositionOccupied(int** positions, int count, int row, int col) override
    {
        return Item::isPositionOccupied(positions, count, row, col);
    }

    void draw(sf::RenderWindow& window) override
    {
        if (visible)
            window.draw(item);
    }

    void updateAnimation(float deltaTime) override
    {
        if (visible)
            animation.Update(0, deltaTime);
    }
};