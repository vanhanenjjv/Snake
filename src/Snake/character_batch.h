#ifndef CHARACTER_BATCH_H
#define CHARACTER_BATCH_H

#include <vector>
#include <string>
#include <emscripten/val.h>

#include "point.h"
// #include "console.h"

struct CharacterData {
  int column;
  int line;
  char character;
};

class CharacterBatch {
  private:
    emscripten::val canvas;
    emscripten::val context;
    std::vector<CharacterData> buffer = std::vector<CharacterData>();
    int width;
    int height;
  public:
    CharacterBatch(emscripten::val canvas) :
      canvas(canvas),
      context(canvas.call<emscripten::val>("getContext", std::string("2d"))) {
      this->width = canvas["width"].as<int>();
      this->height = canvas["height"].as<int>();
      this->context.set("fillStyle", std::string("green"));
    }
    void Begin();
    void Write(int x, int y, char character);
    void Write(Point position, char character);
    void End();
};

#endif
