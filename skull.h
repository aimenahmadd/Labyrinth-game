#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include"Animation.h"
#include"Item.h"
using namespace sf;

class skull : public Item
{
public:
    Animation animation;

    skull() : animation(getTexture(), item, Vector2u(6, 1), 0.1f), Item()
    {
        texture.loadFromFile("pngs/items/skull.png");
        animation = Animation(texture, item, sf::Vector2u(6, 1), 0.1f);
        item.setSize(sf::Vector2f(30, 30));
        item.setTexture(&texture);
    }

    const Texture& getTexture()
    {
        texture.loadFromFile("pngs/items/skull.png");
        return texture;
    }

    void gen(int l, int w)
    {
        item.setTexture(&texture);
        item.setPosition(l, w);
        item.setSize(sf::Vector2f(45, 45));
    }

    void draw(sf::RenderWindow& window) override
    {
        window.draw(item);
    }

    void updateAnimation(float deltaTime) override
    {
        animation.Update(0, deltaTime);
    }
};