#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "point.h"
#include "character_batch.h"

class GameObject {
  public:
    static constexpr Point size { 40, 40 };
    Point position;
    GameObject(Point position) {
      this->position = position;
    }
    virtual void Update() = 0;
    virtual void Draw(CharacterBatch &character_batch) = 0;
};

#endif
