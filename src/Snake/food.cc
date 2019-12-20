#include "food.h"

void Food::Update() {
}

void Food::Draw(CharacterBatch &character_batch) {
  character_batch.Write(this->position, 'X');
}
