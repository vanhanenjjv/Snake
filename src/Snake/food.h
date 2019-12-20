#ifndef FOOD_H
#define FOOD_H

#include "game_object.h"

class Food : public GameObject {
  public:
    Food(int x, int y) : GameObject(Point { x, y }) { }
    void Draw(CharacterBatch &character_batch);
    void Update();
};

#endif
