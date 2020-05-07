#ifndef SNAKE_H
#define SNAKE_H

#include <vector>

#include "game_object.h"
#include "snake_body_part.h"

enum Direction {
  NONE = 0,
  UP = 1,
  RIGHT = 2,
  DOWN = -1,
  LEFT = -2
};

class Snake : public GameObject {
  public:
    Snake(int x, int y) : GameObject(Point { x, y }) {
      auto head = SnakeBodyPart(x, y);

      this->position = head.position;
      this->body.push_back(head);
    }
    std::vector<SnakeBodyPart> body = std::vector<SnakeBodyPart>();
    bool alive = true;
    int length = 1;
    Direction direction = NONE;
    void Draw(CharacterBatch &character_batch);
    void Update();
    void Turn(Direction direction);
    void Grow();
};

#endif
