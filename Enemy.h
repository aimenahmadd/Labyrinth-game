#pragma once
#include<iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include"Audio.h"
#include"Animation.h"

using namespace sf;

class Enemy
{
public:
	RectangleShape skeleton;
	Texture texture; 
	Animation animation;

	int hp = 250;
	int attack = 20;
	int kill = 0;

	bool enemy_attack;
	static int numEnemiesKilled;

	static void incrementEnemiesKilled() {
		numEnemiesKilled++;
	}

	const Texture& getTexture() 
	{
		texture.loadFromFile("pngs/enemy/idleskeleton.png");
		
		return texture;
	}

	Enemy() : animation(getTexture(), skeleton, Vector2u(10, 1), 0.1f)
	{
	
		texture.loadFromFile("pngs/enemy/idleskeleton.png");

		skeleton.setTexture(&texture);
		skeleton.setOrigin(-15, 5);

	}

	void generateEnemy(Enemy enemies[], int& numofenemies, const int** mazeArray, int rows, int columns)
	{
		std::uniform_int_distribution<int> dist_row(1, rows - 2);
		std::uniform_int_distribution<int> dist_col(1, columns - 2);

		int count = 0;
		int** occupiedPositions = new int* [numofenemies];

		for (int i = 0; i < numofenemies; i++)
		{
			occupiedPositions[i] = new int[2];
		}

		while (count < numofenemies)
		{
			int rn = dist_row(rng1);
			int rn1 = dist_col(rng1);

			if (mazeArray[rn][rn1] == 0 && !isPositionOccupied(occupiedPositions, count, rn, rn1))
			{
				enemies[count].skeleton.setSize(Vector2f(45.0f, 40.0f));

				enemies[count].skeleton.setPosition((rn1 * 25) + 20, (rn * 25) + 174);
				occupiedPositions[count][0] = rn;
				occupiedPositions[count][1] = rn1;
				count++;
			}
		}
	}

	bool isPositionOccupied(int** positions, int count, int row, int col)
	{
		for (int i = 0; i < count; i++)
		{
			if (positions[i][0] == row && positions[i][1] == col)
				return true;
		}
		return false;
	}

	void changeTextureLeft()
	{
		texture.loadFromFile("pngs/enemy/attackleft.png");
		skeleton.setTexture(&texture);
		enemy_attack = true;
	}

	void changeTextureRight()
	{
		texture.loadFromFile("pngs/enemy/attackright.png");
		skeleton.setTexture(&texture);
		enemy_attack = true;

	}

	void idleenemy()
	{
		texture.loadFromFile("pngs/enemy/idleskeleton.png");
		skeleton.setTexture(&texture);
	}

	void draw(RenderWindow &window)
	{
		window.draw(skeleton);
	}
	
	void updateAnimation(float deltatime)
	{
		animation.Update(0, deltatime);
	}

};
int Enemy::numEnemiesKilled = 0;
