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

std::mt19937 rng1(std::random_device{}());

using namespace sf;
class Potion : public Item
{
public:
    Animation animation;

    Potion() : animation(getTexture(), item, Vector2u(12, 1), 0.1f), Item()
    {
        texture.loadFromFile("pngs/items/potion.png");
        key = 10;
        name = "potion";
        value = 5;
    }   

    const Texture& getTexture()
    {
        texture.loadFromFile("pngs/items/potion.png");
        return texture;
    }

    void generatePotions(Potion potions[], int& numofpotions, const int** mazeArray, int rows, int columns)
    {
        std::uniform_int_distribution<int> dist_row(1, rows - 2);
        std::uniform_int_distribution<int> dist_col(1, columns - 2);

        int count = 0;
        int** occupiedPositions = new int* [numofpotions];
        for (int i = 0; i < numofpotions; ++i)
        {
            occupiedPositions[i] = new int[2];
        }

        while (count < numofpotions)
        {
            int rn = dist_row(rng1);
            int rn1 = dist_col(rng1);

            if (mazeArray[rn][rn1] == 0  && !isPositionOccupied(occupiedPositions, count, rn, rn1))
            {
                potions[count].item.setSize(sf::Vector2f(55, 30));
                potions[count].item.setTexture(&texture);
                potions[count].item.setPosition((rn1 * 25) + 20, (rn * 25) + 170);
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
        item.setSize(sf::Vector2f(85, 45));
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