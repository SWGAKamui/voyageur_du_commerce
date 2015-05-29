#ifndef DRAWER_H
#define DRAWER_H

#include <SDL.h>
#include <SDL_ttf.h>

typedef struct Printer
{
  SDL_Window *window;
  SDL_Renderer *renderer;
} Printer;

void setPrinter(Printer*);
void setFont(TTF_Font*);
void draw(void);
void cleanDrawer();
void drawRect(int x, int y, int w, int h, int r, int g, int b);
void drawText(const char* text, int x, int w, int h, int y, int r, int g, int b);
void drawTextWithRectFilled(const char* text, int x, int y, int w, int h, int margin, int rf, int bf, int gf, int rb, int bb, int gb);
void delay(unsigned int frameLimit);
void drawLines(int x, int y, int dx, int dy, int r, int g, int b);

#endif