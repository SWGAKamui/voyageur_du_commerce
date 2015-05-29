#ifndef INPUT_H
#define INPUT_H

#include <SDL.h>

 typedef struct Input{
  int left, right, up, down, enter, erase, pause;
} Input;

void setInput(Input*);
void getInput();

#endif