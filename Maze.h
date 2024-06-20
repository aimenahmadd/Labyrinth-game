#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>

using namespace sf;
using namespace std;

class Maze 
{
protected:
    int** arr;
    const int rows = 23;
    const double columns = 73;
    const double cellSize = 25; 
    Texture texture, floor_texture;
    int count = 1;

public:
       
    Maze()
    {
        texture.loadFromFile("pngs/Maze/mazesprite.png");
        floor_texture.loadFromFile("pngs/Maze/ground.png");

        arr = new int* [rows];
        for (int i = 0; i < rows; i++) 
        {
            arr[i] = new int[columns];
        }
    }

    ~Maze() {
        for (int i = 0; i < rows; ++i) {
            delete[] arr[i];
        }
        delete[] arr;
    }

    const int** getArray() const {
        return (const int**)arr;
    }

    int getRows() const {
        return rows;
    }

    int getColumns() const {
        return columns;
    }

    void readFromFile(const string& filename) 
    {
        ifstream file(filename);

        if (!file.is_open()) 
        {
            cout << "Failed to open file." << endl;
            return;
        }

        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < columns; j++)
            {
                char c;

                do {
                    file >> c;
                } while (c != '0' && c != '1'); 

                arr[i][j] = c - '0'; 
            }
        }

        file.close();
    }

    void drawMaze(sf::RenderWindow& window) 
    {
        for (int i = 0; i < rows; i++) 
        {
            for (int j = 0; j < columns; j++)
            {
                if (arr[i][j] == 1)
                {
                    RectangleShape cell(sf::Vector2f(cellSize, cellSize));

                    cell.setPosition((j * cellSize) + 40, (i * cellSize) + 194);
                  
                    cell.setTexture(&texture);
                    window.draw(cell);

                }
              
            }
        
        }

        count++;
    }
};

