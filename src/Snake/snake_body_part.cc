#include "snake_body_part.h"

void SnakeBodyPart::Update() {
}

void SnakeBodyPart::Draw(CharacterBatch &character_batch) {
  character_batch.Write(this->position, 'O');
}
