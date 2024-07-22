#ifndef FONCTIONS_SDL_H
#define FONCTIONS_SDL_H
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

void afficherFond(SDL_Renderer *renderer, SDL_Texture *pavage, SDL_Rect srcp[], int pavX, int pavY, int nbLig, int nbCol, char **tabpav, int nbCases);

SDL_Rect newrect(int x, int y, int w, int h);

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);

int setWindowColor(SDL_Renderer *renderer, SDL_Color color);

SDL_Texture *loadImage(const char *path, SDL_Renderer *renderer);

SDL_Texture *LoadImage_transp(const char *path, SDL_Renderer *renderer, Uint8 r, Uint8 g, Uint8 b);
#endif
