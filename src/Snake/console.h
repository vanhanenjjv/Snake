#ifndef CONSOLE_H
#define CONSOLE_H

namespace console {
  int width();
  int height();
  void Clear();
  void SetCursorPosition(short column, short line);
  void PlaceCharacter(char character);
  bool IsKeyDown(char key);
};

#endif
