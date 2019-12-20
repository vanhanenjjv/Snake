#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <vector>

#include "random.h"
#include "character_batch.h"
#include "food.h"
#include "snake.h"

class SnakeGame {
  private:
    Random random = Random();
    CharacterBatch *character_batch;
    Snake *snake;
    Food *food;
    int width;
    int height;
    void DrawBorders();
    void CreateFood();
    void HandleCollision();
    void HandleInput();
    void UpdateGame();
    void DrawGame();

  public:
    SnakeGame(int width, int height);
    void Start();
};

#endif
