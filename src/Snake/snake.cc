#include "snake.h"

void Snake::Update() {
  for (int i = this->body.size() - 1; i > 0; --i) {
    this->body[i].position = this->body[i - 1].position;
  }

  auto &head = this->body[0];

  switch (this->direction) {
    case NONE: break;
    case UP: {
      head.position.y -= 1;
      break;
    };
    case RIGHT: {
      head.position.x += 1;
      break;
    };
    case DOWN: {
      head.position.y += 1;
      break;
    };
    case LEFT: {
      head.position.x -= 1;
      break;
    };
  }

  this->position = head.position;
}

void Snake::Draw(CharacterBatch &character_batch) {
  auto body = this->body;
  for (auto body_part : body) {
    body_part.Draw(character_batch);
  }
}

void Snake::Turn(Direction direction) {
  // Prevent turning around if the body is larger than just the head
  if (this->body.size() > 1 && this->direction == (direction * -1))
    return;

  this->direction = direction;
}

void Snake::Grow() {
  auto last_body_part_index = this->body.size() - 1;
  auto last_body_part = this->body[last_body_part_index];

  auto body_part = SnakeBodyPart(
    last_body_part.position.x, 
    last_body_part.position.y);

  this->body.push_back(body_part);

  this->length += 1;
}
