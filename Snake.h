//
// Created by Qara on 2019/10/1.
//

#ifndef SNAKE_SNAKE_H
#define SNAKE_SNAKE_H

#include <list>

#define HEIGHT 20
#define WIDTH 20
#define INIT_LENGTH 4

class Snake {
private:
    std::list<std::pair<int, int>> snake_pos{};
    int direction = -1;
public:
    Snake() {
        for (int mPos = 1; mPos <= INIT_LENGTH; ++mPos) {
            snake_pos.emplace_front(mPos, 1);
        }
        this -> direction = 0;
        for (int mWidth = 1; mWidth < WIDTH; ++mWidth) {
            for (int mHeight = 1; mHeight < HEIGHT; ++mHeight) {
                std::pair<int, int> xy = std::make_pair(mWidth, mHeight);
            }
        }
    }
    std::list<std::pair<int, int>> getPos() const {
        return snake_pos;
    }
    std::pair<int, int> getHeadPos() const {
        return snake_pos.front();
    }
    void left() {
        std::pair<int, int> pair = std::make_pair(snake_pos.front().first - 1, snake_pos.front().second);
        snake_pos.emplace_front(pair);
        snake_pos.pop_back();
        direction = 0;
    }
    void right() {
        std::pair<int, int> pair = std::make_pair(snake_pos.front().first + 1, snake_pos.front().second);
        snake_pos.emplace_front(pair);
        snake_pos.pop_back();
        direction = 1;
    }
    void up() {
        std::pair<int, int> pair = std::make_pair(snake_pos.front().first, snake_pos.front().second - 1);
        snake_pos.emplace_front(pair);
        snake_pos.pop_back();
        direction = 2;
    }
    void down() {
        std::pair<int, int> pair = std::make_pair(snake_pos.front().first, snake_pos.front().second + 1);
        snake_pos.emplace_front(pair);
        snake_pos.pop_back();
        direction = 3;
    }
    int getDirection() const {
        return direction;
    }
    void setDirection(int d) {
        direction = d;
    }
    void eat(std::pair<int, int> food_pos) {
        snake_pos.emplace_back(food_pos);
    }
};

#endif //SNAKE_SNAKE_H
