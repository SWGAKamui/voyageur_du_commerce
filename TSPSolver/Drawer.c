#include <Drawer.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_ttf.h>

static SDL_Rect srcRect, destRect;
Printer* printer;
TTF_Font* font;
SDL_Texture* textureTmp;


void setPrinter(Printer* p){
  printer = p;
}

void setFont(TTF_Font* f){
  font = f;
}

void cleanDrawer(){
  SDL_RenderClear(printer->renderer);
}

void draw(void){
 
  // Remplis le renderer de noir, efface l'écran et l'affiche.
  //SDL_RenderPresent() remplace SDL_Flip de la SDL 1.2
  SDL_SetRenderDrawColor(printer->renderer, 255, 255, 255, 255);
  SDL_RenderPresent(printer->renderer);
 
  // Delai
  SDL_Delay(1);

  cleanDrawer();
}
 
void drawRect(int x, int y, int w, int h, int r, int g, int b){
  SDL_Rect rect = {x, y, w, h};

  SDL_SetRenderDrawColor(printer->renderer, r, g, b, 0);

  SDL_RenderFillRect(printer->renderer, &rect);
}

void drawText(const char* text, int x, int y, int w, int h, int r, int g, int b){
  SDL_Color color = {r, g, b};

  SDL_Surface* gText;
  gText = TTF_RenderText_Blended(font, text, color);
  textureTmp = SDL_CreateTextureFromSurface(printer->renderer, gText);
  

  if (gText == NULL){
    printf("Erreur de texture \n");
  }

  destRect.x = x;
  destRect.y = y;
  destRect.w = w;
  destRect.h = h;

  SDL_RenderCopy(printer->renderer, textureTmp, NULL, &destRect);
  SDL_FreeSurface(gText);
  SDL_DestroyTexture(textureTmp);
}

void drawLines(int x, int y, int x2, int y2, int r, int g, int b){
  drawRect(x, y, (x2-x)/4, 2, r, g, b);
  if (y2<y)
    drawRect(x+(x2-x)/4, y+2, 2, (y2-y)/2, r, g, b);
  else
    drawRect(x+(x2-x)/4, y, 2, (y2-y)/2, r, g, b);
  if (x2<x)
    drawRect(x+(x2-x)/4+2, y + (y2-y)/2, x2-(x+(x2-x)/4), 2, r, g, b);
  else
    drawRect(x+(x2-x)/4, y + (y2-y)/2, x2-(x+(x2-x)/4), 2, r, g, b);
  if (y2<y)
    drawRect(x2, y + (y2-y)/2+2, 2, (y2-y)/2, r, g, b);
  else
    drawRect(x2, y + (y2-y)/2, 2, (y2-y)/2, r, g, b);

}
 
void drawTextWithRectFilled(const char* text, int x, int y, int w, int h, int margin, int rf, int gf, int bf, int rb, int gb, int bb){
  drawRect(x-margin, y-margin, w+2*margin, h+2*margin, rb, gb, bb);
  drawText(text, x, y, w, h, rf, gf, bf);
}
 
void delay(unsigned int frameLimit){
  // Gestion des 60 fps (images/stories/seconde)
  unsigned int ticks = SDL_GetTicks();
 
  if (frameLimit < ticks)
  {
      return;
  }
 
  if (frameLimit > ticks + 16)
  {
      SDL_Delay(16);
  }
 
  else
  {
      SDL_Delay(frameLimit - ticks);
  }
}