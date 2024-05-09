#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <vector>

namespace CLISNAKE
{

    struct SnakeCeil
    {
        int x;
        int y;
        SnakeCeil(int x_, int y_) : x(x_), y(y_){};
    };

    const int UP = 0;
    const int RIGHT = 1;
    const int DOWN = 2;
    const int LEFT = 3;

    class Game
    {
    private:
        int width, height;
        int score = 0;
        int foodX, foodY;
        char snake = 'O';
        char food = '@';
        char empty = ' ';
        char border = '#';
        int snakeDirection = 0;
        std::vector<SnakeCeil> snakeBody;

        bool isSnakeCeil(int x, int y)
        {
            for (int i = 0; i < snakeBody.size(); i++)
            {
                if (snakeBody[i].x == x && snakeBody[i].y == y)
                {
                    return true;
                }
            }
            return false;
        }

        void Draw()
        {
            system("cls");
            for (int i = 0; i < height; i++)
            {
                for (int j = 0; j < width; j++)
                {
                    if (i == 0 || j == 0 || i == height - 1 || j == width - 1)
                    {
                        std::cout << border;
                    }
                    else if (i == foodY && j == foodX)
                    {
                        std::cout << food;
                    }
                    else
                    {
                        if (isSnakeCeil(j, i))
                        {
                            std::cout << snake;
                        }
                        else
                        {
                            std::cout << empty;
                        }
                    }
                }
                std::cout << "\n";
            }
        };

        void Update() {
        };

        void Input()
        {
            if (_kbhit())
            {
                switch (_getch())
                {
                case 'w':
                    snakeDirection = UP;
                    break;
                case 'a':
                    snakeDirection = LEFT;
                    break;
                case 's':
                    snakeDirection = DOWN;
                    break;
                case 'd':
                    snakeDirection = RIGHT;
                    break;
                default:
                    break;
                }
            }
        };

        void Logic()
        {
            switch (snakeDirection)
            {
            case UP:
                snakeBody[0].y--;
                break;
            case RIGHT:
                snakeBody[0].x++;
                break;
            case DOWN:
                snakeBody[0].y++;
                break;
            case LEFT:
                snakeBody[0].x--;
                break;
            default:
                break;
            }

            if (snakeBody[0].x == foodX && snakeBody[0].y == foodY)
            {
                score++;
                foodX = rand() % (width - 4) + 2;
                foodY = rand() % (height - 4) + 2;
            }

            if (snakeBody[0].x <= 0 || snakeBody[0].x >= width || snakeBody[0].y <= 0 || snakeBody[0].y >= height)
            {
                std::cout << "Game Over";
                std::cout << "\nScore: " << score;
                exit(0);
            }
        };

    public:
        Game(int widht_, int height_)
        {
            width = widht_;
            height = height_;
            foodX = rand() % (width - 4) + 2;
            foodY = rand() % (height - 4) + 2;
            snakeBody.push_back(SnakeCeil(width / 2, height / 2));
        }

        void run()
        {
            while (true)
            {
                Draw();
                Update();
                Input();
                Logic();
                Sleep(100);
            }
        };
    };
};