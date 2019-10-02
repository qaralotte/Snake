#include <iostream>
#include <ctime>
#include <conio.h>
#include <random>
#include <chrono>

#include "Snake.h"

std::string world[WIDTH][HEIGHT]{};

void delay(unsigned long);
std::pair<int, int> randomFood(const std::list<std::pair<int, int>>&);
void updateWorld(const std::list<std::pair<int, int>>& snake_pos, const std::pair<int, int>& food_pos) {
#if defined(__linux__)
    system("clear");
#elif defined(_WIN32)
    system("cls");
#endif
    for (int mWidth = 1; mWidth < WIDTH; ++mWidth) {
        for (int mHeight = 1; mHeight < HEIGHT; ++mHeight) {
            world[mWidth][mHeight] = "  ";
        }
    }
    bool top = false;
    for (auto sp : snake_pos) {
        world[sp.first][sp.second] = top ? "¡ó" : "¡ô";
        top = true;
    }
    world[food_pos.first][food_pos.second] = "¡ï";
    for (int mHeight = 0; mHeight < HEIGHT + 1; ++mHeight) {
        for (int mWidth = 0; mWidth < WIDTH + 1; ++mWidth) {
            if (mHeight == 0) {
                if (mWidth == 0) {
                    std::cout << "¨X";
                } else if (mWidth == WIDTH) {
                    std::cout << "¨[";
                } else {
                    std::cout << "¨T¨T";
                }
            } else if (mHeight >= 1 && mHeight <= HEIGHT - 1) {
                if (mWidth == 0 || mWidth == WIDTH) {
                    std::cout << "¨U";
                } else {
                    std::cout << world[mWidth][mHeight];
                }
            } else if (mHeight == HEIGHT) {
                if (mWidth == 0) {
                    std::cout << "¨^";
                } else if (mWidth == WIDTH) {
                    std::cout << "¨a";
                } else {
                    std::cout << "¨T¨T";
                }
            }
        }
        std::cout << std::endl;
    }
}
int main() {
    Snake s;
    s.setDirection(1);
    auto food_pos = randomFood(s.getPos());
    while (true) {
        switch (s.getDirection()) {
            case 0: {
                s.left();
            }
                break;
            case 1: {
                s.right();
            }
                break;
            case 2: {
                s.up();
            }
                break;
            case 3: {
                s.down();
            }
                break;
        }
        if (s.getHeadPos() == food_pos) {
            food_pos = randomFood(s.getPos());
            s.eat(food_pos);
        }
        int input{};
        if (_kbhit()) {
            input = _getch();
        }
        (input == 'a' && s.getDirection() != 1) ? s.setDirection(0) :
        (input == 'd' && s.getDirection() != 0) ? s.setDirection(1) :
        (input == 'w' && s.getDirection() != 3) ? s.setDirection(2) :
        (input == 's' && s.getDirection() != 2) ? s.setDirection(3) : s.setDirection(s.getDirection());
        bool isEatSelf = true;
        for (auto mPos : s.getPos()) {
            if (mPos == s.getHeadPos()) {
                isEatSelf = !isEatSelf;
            }
            if (((mPos.first == HEIGHT || mPos.second == WIDTH) || (mPos.first == 0 || mPos.second == 0)) || isEatSelf) {
                return 0;
            }
        }
        updateWorld(s.getPos(), food_pos);
        delay(200);
    }
}
void delay(unsigned long ms) {
    clock_t now = clock();
    while(clock() - now < ms);
}

std::pair<int, int> randomFood(const std::list<std::pair<int, int>>& snake_pos) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 mt(seed);
    std::uniform_int_distribution<int> distx(1, WIDTH - 1);
    std::uniform_int_distribution<int> disty(1, HEIGHT - 1);
    while (true) {
        std::pair<int, int> food_pos = std::make_pair(distx(mt), disty(mt));
        bool last{};
        for (auto mPos : snake_pos) {
            if (mPos != food_pos) {
                last = true;
            }
        }
        if (last) {
            return food_pos;
        }
    }
}