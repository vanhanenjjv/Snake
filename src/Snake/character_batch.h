#ifndef CHARACTER_BATCH_H
#define CHARACTER_BATCH_H

#include <vector>

#include "point.h"
#include "console.h"

struct CharacterData {
  int column;
  int line;
  char character;
};

class CharacterBatch {
  private:
    std::vector<CharacterData> buffer = std::vector<CharacterData>();
    int width;
    int height;
  public:
    CharacterBatch(int width, int height);
    void Begin();
    void Write(int x, int y, char character);
    void Write(Point position, char character);
    void End();
};

#endif
