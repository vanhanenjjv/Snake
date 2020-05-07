#include "character_batch.h"

#include <iostream>
#include <string>

#include "game_object.h"

// #include "console.h"

using std::string;
using emscripten::val;


// ooh yeah bad codinks
string characterToColor(char character) {
  switch (character) {
    case 'O':
      return "green";
    case 'X':
      return "red";
    default:
      return "pink";
  }
}

void CharacterBatch::Begin() {
  this->context.call<void>("clearRect", 0, 0, this->width, this->height);
  this->buffer.clear();
}

void CharacterBatch::Write(int x, int y, char character) {
  this->buffer.push_back(CharacterData { x, y, character });
}

void CharacterBatch::Write(Point position, char character) {
  this->Write(position.x, position.y, character);
}

void CharacterBatch::End() {
  for (auto character_data : this->buffer) {
    auto size = GameObject::size;

    this->context.set("fillStyle", characterToColor(character_data.character));
    this->context.call<void>("fillRect", character_data.column, character_data.line, size.x, size.y);
  }
}
