#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include"game.h"
using namespace sf;


class Animation
{
	float totalTime, switchTime;
	Vector2u imagecount, currentimage;
public:

	RectangleShape dawg;
	Texture texture;

	IntRect uvRect;

	Animation()
	{}

	Animation(Texture texture, RectangleShape dawg, Vector2u imagecount, float switchTime)
	{
		this->texture = texture;
		this->dawg = dawg;
		this->imagecount = imagecount;
		this->switchTime = switchTime;
		totalTime = 0.0f;
		currentimage.x = 0.0f;

		uvRect.width = this->texture.getSize().x / float(imagecount.x);
		uvRect.height = this->texture.getSize().y / float(imagecount.y);
	}

	void settexture(Texture t)
	{
		texture = t;
	}

	void Update(int row, float deltaTime)
	{
		currentimage.y = row;
		totalTime += deltaTime;

		if (totalTime >= switchTime)
		{
			totalTime -= switchTime;
			currentimage.x++;

			if (currentimage.x >= imagecount.x)
				currentimage.x = 0;
		}

		uvRect.left = currentimage.x * uvRect.width;
		uvRect.top = currentimage.y * uvRect.height;
	}

	void playfull(int row, sf::RectangleShape& shape, sf::RenderWindow& window, float deltaTime)
	{
		while (currentimage.x < imagecount.x - 1)
		{
			Update(row, deltaTime);

			shape.setTexture(&texture);
			shape.setTextureRect(uvRect);
			window.draw(shape);
		}
		
	}
};

