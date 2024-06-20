#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include"Animation.h"
#include"Inventory.h"
#include"Maze.h"

using namespace sf;

class Item : public Maze
{
public:

    int value;
    int key;
    string name;
    int numofitems=0;
    RectangleShape item;
    Texture texture;
    
    bool visible = true;

    virtual bool isPositionOccupied(int** positions, int count, int row, int col)
    {
        for (int i = 0; i < count; i++)
        {
            if (positions[i][0] == row && positions[i][1] == col)
                return true;
        }
        return false;
    }

    virtual void draw(sf::RenderWindow& window) = 0;
    virtual void updateAnimation(float deltaTime) = 0;
};