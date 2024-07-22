#ifndef SPRITE_H
#define SPRITE_H

#include "fonctions_SDL.h"
#include "../donnees/constante.h"
#include "liste.h"
#include "monde.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

struct sprite_s
{
    // La position non visible sur le tableau
    int posX;
    int posY;
    // La position visible sur l'écran
    int SpriteX;
    int SpriteY;
    int h;
    int w;
    t_elem *listeInv;
};
typedef struct sprite_s sprite_t;

sprite_t *initSprite2(sprite_t *newsprite, int x, int y, int SpriteX, int SpriteY);

int getposX(sprite_t *sprite);

int getposY(sprite_t *sprite);

int getSpriteX(sprite_t *sprite);

int getSpriteY(sprite_t *sprite);

void SetposX(sprite_t *sprite, int newposx);

void SetposY(sprite_t *sprite, int newposy);

void SetspriteX(sprite_t *sprite, int spritex);

void SetspriteY(sprite_t *sprite, int spritey);

t_elem *getInventaire(sprite_t *sprite);

void RamasserObjet(sprite_t *sprite, monde_t *monde, int objetadd);

void freeS(sprite_t *s);

void printsprite(sprite_t *sprite);

#endif