#ifndef SNAKE_GAME_H
#define SNAKE_GAME_H

#include <vector>
#include <emscripten.h>
#include <emscripten/bind.h>

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
    SnakeGame(emscripten::val canvas);
    // Bad meme
    void Turn(Direction direction) { this->snake->Turn(direction); }
    void Start();
};

EMSCRIPTEN_BINDINGS(SnakeGame) {
  emscripten::class_<SnakeGame>("SnakeGame")
    .constructor<emscripten::val>()
    .function("Turn", &SnakeGame::Turn)
    .function("Start", &SnakeGame::Start);
  emscripten::enum_<Direction>("Direction")
    .value("Up", UP)
    .value("Down", DOWN)
    .value("Left", LEFT)
    .value("Right", RIGHT);
}

#endif
