#include "snake_game.h"

#include <iostream>
#include <thread>
#include <math.h>

#include "snake.h"
#include "food.h"

using emscripten::val;


SnakeGame::SnakeGame(val canvas) {
  this->width = canvas["width"].as<int>();
  this->height = canvas["height"].as<int>();

  this->character_batch = new CharacterBatch(canvas);

  std::cout << "width: " << this->width << "\n";
  std::cout << "height: " << this->height << "\n";
}

void SnakeGame::DrawBorders() {
  // Draw left and right border
  for (int y = 1; y < this->height; ++y) {
    this->character_batch->Write(0, y, '|');
    this->character_batch->Write(this->width - 1, y, '|');
  }

  // Draw top and bottom border
  for (int x = 1; x < this->width; ++x) {
    this->character_batch->Write(x, 0, '-');
    this->character_batch->Write(x, this->height - 1, '-');
  }
}

void SnakeGame::DrawGame() {
  // Clears the buffer
  this->character_batch->Begin();

  // Writes data to buffer
  this->food->Draw(*this->character_batch);
  this->snake->Draw(*this->character_batch);

  // Prints data from buffer to console
  this->character_batch->End();
}

void SnakeGame::UpdateGame() {
  this->snake->Update();
  this->HandleCollision();
}

// obsoleted
void SnakeGame::HandleInput() {
  while (this->snake->alive) {
    // if (console::IsKeyDown('W'))
    //   this->snake->Turn(UP);
    // if (console::IsKeyDown('A'))
    //   this->snake->Turn(LEFT);
    // if (console::IsKeyDown('D'))
    //   this->snake->Turn(RIGHT);
    // if (console::IsKeyDown('S'))
    //   this->snake->Turn(DOWN);
  }
}

void SnakeGame::CreateFood() {
  int x, y;
  bool colliding;

  do {
    colliding = false;

    x = this->random.Next(0, 21) * 40;
    y = this->random.Next(0, 21) * 40;

    for (auto body_part : this->snake->body) {
      if (body_part.position.x == x &&
        body_part.position.y == y)
        colliding = true;
    }
  } while (colliding);

  this->food = new Food(x, y);
}

void SnakeGame::HandleCollision() {
  auto head = &this->snake->body[0];

  // Handle the collision with world border
  if (head->position.x < 0)
    head->position.x = this->width - 40;
  else if (head->position.x > this->width - 1)
    head->position.x = 0;
  else if (head->position.y < 0)
    head->position.y = this->height - 40;
  else if (head->position.y > this->height - 1)
    head->position.y = 0;

  // Handle the collision with the snake itself
  for (int i = 1; i < this->snake->length; ++i) {
    if (head->position.x == this->snake->body[i].position.x &&
      head->position.y == this->snake->body[i].position.y)
      this->snake->alive = false;
  }

  // Handle the collision with food
  if (head->position.x == this->food->position.x &&
    head->position.y == this->food->position.y) {
    this->snake->Grow();
    this->CreateFood();
  }
}

void SnakeGame::Start() {
  // Start the game from the center
  this->snake = new Snake((this->width / 2) - GameObject::size.x / 2, this->height / 2 - GameObject::size.y / 2);

  this->CreateFood();

  while (this->snake->alive) {
    this->DrawGame();
    this->UpdateGame();
    
    emscripten_sleep(
      // just a quick meme to make the game more interesting to play
      std::max(
        200 - this->snake->length * 10,
        50));
  }

  EM_ASM({
    // some good old fashioned calls to consumer from library
    window.game.Start();
    alert('Your score: ' + $0);
  }, this->snake->length);
}
