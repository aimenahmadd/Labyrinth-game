#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include"Animation.h"
#include"Item.h"

using namespace sf;

class Background : public Item
{
public:
    Animation animation;

    Background() : animation(getTexture(), item, Vector2u(19, 1), 0.1f), Item()
    {
        texture.loadFromFile("pngs/mainmenu/Background.png");
        animation = Animation(texture, item, sf::Vector2u(19, 1), 0.1f);
        item.setSize(sf::Vector2f(1900, 1000));
        item.setTexture(&texture);
    }

    const Texture& getTexture()
    {
        texture.loadFromFile("pngs/mainmenu/Background.png");
        return texture;
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