#pragma once
#include <iostream>
#include <string>
#include <windows.h>
#include <vector>
#include <conio.h>

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

        void End()
        {
            std::cout << "\nGame Over";
            std::cout << "\nScore: " << score;
            exit(0);
        }

        void Logic()
        {
            switch (snakeDirection)
            {
            case UP:
                snakeBody.emplace(snakeBody.begin(), SnakeCeil(snakeBody[0].x, snakeBody[0].y - 1));
                snakeBody.pop_back();
                break;
            case RIGHT:
                snakeBody.emplace(snakeBody.begin(), SnakeCeil(snakeBody[0].x + 1, snakeBody[0].y));
                snakeBody.pop_back();
                break;
            case DOWN:
                snakeBody.emplace(snakeBody.begin(), SnakeCeil(snakeBody[0].x, snakeBody[0].y + 1));
                snakeBody.pop_back();
                break;
            case LEFT:
                snakeBody.emplace(snakeBody.begin(), SnakeCeil(snakeBody[0].x - 1, snakeBody[0].y));
                snakeBody.pop_back();
                break;
            default:
                break;
            }

            if (snakeBody[0].x == foodX && snakeBody[0].y == foodY)
            {
                score++;
                foodX = rand() % (width - 4) + 2;
                foodY = rand() % (height - 4) + 2;
                snakeBody.push_back(SnakeCeil(snakeBody[snakeBody.size() - 1].x, snakeBody[snakeBody.size() - 1].y));
            }
            if (snakeBody[0].x <= 0 || snakeBody[0].x >= width - 1 || snakeBody[0].y <= 0 || snakeBody[0].y >= height - 1)
            {
                End();
            }

            for (int i = 2; i < snakeBody.size(); i++)
            {
                if (snakeBody[0].x == snakeBody[i].x && snakeBody[0].y == snakeBody[i].y)
                {
                    End();
                }
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
                Input();
                Logic();
                Sleep(150);
            }
        };
    };
};