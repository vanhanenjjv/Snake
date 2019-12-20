#include "console.h"

#include <iostream>

#include "Windows.h"

namespace console {
  int width() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(
      GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    return csbi.srWindow.Right - csbi.srWindow.Left + 1;
  }

  int height() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(
      GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
  }

  void Clear() {
    COORD topLeft  = { 0, 0 };
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen;
    DWORD written;

    GetConsoleScreenBufferInfo(console, &screen);
    
    FillConsoleOutputCharacterA(
      console, 
      ' ', 
      screen.dwSize.X * screen.dwSize.Y, 
      topLeft, 
      &written);

    FillConsoleOutputAttribute(
      console,
      FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
      screen.dwSize.X * screen.dwSize.Y,
      topLeft,
      &written);
      
    SetConsoleCursorPosition(console, topLeft);
  }

  void SetCursorPosition(short column, short line) {
    COORD coord { column, line };
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    SetConsoleCursorPosition(hConsole, coord);
  }

  void PlaceCharacter(char character) {
    std::cout << character;
  }

  bool IsKeyDown(char key) {
    return (GetKeyState(key) & 0x8000);
  }
};
