#include "snake_game.h"

#include <iostream>
#include <thread>

#include "snake.h"
#include "food.h"

SnakeGame::SnakeGame(int width, int height) {
  this->width = width;
  this->height = height;

  this->character_batch = new CharacterBatch(width, height);

  // Start the game from the center
  this->snake = new Snake(width / 2, height / 2);
}

void SnakeGame::DrawBorders() {
  // Draw left and right border
  for (int y = 1; y < this->height; ++y) {
    this->character_batch->Write(0, y, '|');
    this->character_batch->Write(this->width - 1, y, '|');
  }

  // Draw top and bottom border
  for (int x = 0; x < this->width; ++x) {
    this->character_batch->Write(x, 0, '-');
    this->character_batch->Write(x, this->height - 1, '-');
  }
}

void SnakeGame::DrawGame() {
  // Clears the buffer
  this->character_batch->Begin();

  // Writes data to buffer
  this->DrawBorders();
  this->food->Draw(*this->character_batch);
  this->snake->Draw(*this->character_batch);

  // Prints data from buffer to console
  this->character_batch->End();
}

void SnakeGame::UpdateGame() {
  this->snake->Update();
  this->HandleCollision();
}

void SnakeGame::HandleInput() {
  while (this->snake->alive) {
    if (console::IsKeyDown('W'))
      this->snake->Turn(UP);
    if (console::IsKeyDown('A'))
      this->snake->Turn(LEFT);
    if (console::IsKeyDown('D'))
      this->snake->Turn(RIGHT);
    if (console::IsKeyDown('S'))
      this->snake->Turn(DOWN);
  }
}

void SnakeGame::CreateFood() {
  int x, y;
  bool colliding;

  do {
    colliding = false;

    x = this->random.Next(1, this->width - 1);
    y = this->random.Next(1, this->height - 1);

    for (auto body_part : this->snake->body) {
      if (body_part.position.x == x &&
        body_part.position.y == y)
        colliding = true;
    }
  } while (colliding);

  this->food = new Food(x, y);
}

void SnakeGame::HandleCollision() {
  auto &head = this->snake->body[0];

  // Handle the collision with world border
  if (head.position.x < 0)
    head.position.x = this->width - 1;
  else if (head.position.x > this->width - 1)
    head.position.x = 0;
  else if (head.position.y < 0)
    head.position.y = this->height - 1;
  else if (head.position.y > this->height - 1)
    head.position.y = 0;

  // Handle the collision with the snake itself
  for (int i = 1; i < this->snake->length; ++i) {
    if (head.position.x == this->snake->body[i].position.x &&
      head.position.y == this->snake->body[i].position.y)
      this->snake->alive = false;
  }

  // Handle the collision with food
  if (this->snake->position.x == this->food->position.x &&
    this->snake->position.y == this->food->position.y) {
    this->snake->Grow();
    this->CreateFood();
  }
}

void SnakeGame::Start() {
  this->CreateFood();

  // Start thread for handling inputs
  std::thread input(&SnakeGame::HandleInput, this);

  while (this->snake->alive) {
    this->DrawGame();
    this->UpdateGame();

    // Wait for 0.3 seconds for the next update
    _sleep(300);
  }

  // Quick implementation of the score view
  console::Clear();
  std::cout << "Your score: " << this->snake->length << "\n\n";
}
