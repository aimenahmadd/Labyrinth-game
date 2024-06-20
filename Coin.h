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
std::mt19937 rng(std::random_device{}());

using namespace sf;

class Coin : public Item
{

public:
    Animation animation;


    Coin() : animation(getTexture(), item, Vector2u(8, 1), 0.1f), Item()
    {
        texture.loadFromFile("pngs/items/coin.png");
        item.setSize(sf::Vector2f(20, 20));
        key = 30;
        name = "Coin";
        value = 100;
    }

    const Texture& getTexture()
    {
        texture.loadFromFile("pngs/items/coin.png");
        return texture;
    }

    void generateCoins(Coin coins[], int& numofcoins, const int** mazeArray, int rows, int columns)
    {
        std::default_random_engine engine(std::time(nullptr)); 
        std::uniform_int_distribution<int> distribution_row(1, rows - 2);
        std::uniform_int_distribution<int> distribution_col(1, columns - 2);

        int count = 0;
        int** occupiedPositions = new int* [numofcoins];
        for (int i = 0; i < numofcoins; ++i)
        {
            occupiedPositions[i] = new int[2];
        }

        while (count < numofcoins)
        {
            int rn = distribution_row(engine);
            int rn1 = distribution_col(engine);

            if (mazeArray[rn][rn1] == 0 && !isPositionOccupied(occupiedPositions, count, rn, rn1))
            {
                coins[count].item.setTexture(&texture);
                coins[count].item.setPosition((rn1 * 25) + 35, (rn * 25) + 180);
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
        item.setSize(sf::Vector2f(45, 45));
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