#ifndef SNAKE_BODY_PART_H
#define SNAKE_BODY_PART_H

#include "game_object.h"

class SnakeBodyPart : public GameObject {
  public:
    SnakeBodyPart(int x, int y) : GameObject(Point { x, y }) { }
    void Update();
    void Draw(CharacterBatch &character_batch);
};

#endif
