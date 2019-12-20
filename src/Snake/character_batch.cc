#include "character_batch.h"

#include <iostream>

#include "console.h"

CharacterBatch::CharacterBatch(int width, int height) {
  this->width = width;
  this->height = height;
}

void CharacterBatch::Begin() {
  console::Clear();
  this->buffer.clear();
}

void CharacterBatch::Write(int x, int y, char character) {
  x += (console::width() / 2) - (this->width / 2);
  y += (console::height() / 2) - (this->height / 2);

  this->buffer.push_back(CharacterData { x, y, character });
}

void CharacterBatch::Write(Point position, char character) {
  this->Write(position.x, position.y, character);
}

void CharacterBatch::End() {
  for (auto character_data : this->buffer) {
    console::SetCursorPosition(character_data.column, character_data.line);
    console::PlaceCharacter(character_data.character);
  }

  // Place the cursor to the top left corner
  console::SetCursorPosition(0, 0);
}
