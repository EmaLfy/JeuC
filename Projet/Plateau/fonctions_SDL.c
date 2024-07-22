#include "fonctions_SDL.h"
#include <SDL2/SDL_image.h>
#include "../donnees/constante.h"
#include <stdlib.h>
#include <stdio.h>

void afficherFond(SDL_Renderer *renderer, SDL_Texture *pavage, SDL_Rect srcp[], int pavX, int pavY, int nbLig, int nbCol, char **tabpav, int nbCases)
{
    SDL_Rect DestP;

    for (int i = 0; i < nbLig; i++)
    {
        for (int j = 0; j < nbCol; j++)
        {
            DestP.x = pavX;
            DestP.y = pavY;
            DestP.w = HAUTEUR_PAV;
            DestP.h = HAUTEUR_PAV;
            char caseValue = tabpav[i][j];
            if (caseValue >= '0' && caseValue <= ('0' + nbCases - 1))
            {
                int caseIndex = caseValue - '0';
                SDL_RenderCopy(renderer, pavage, &srcp[caseIndex], &DestP);
            }
            pavX += HAUTEUR_PAV;
        }
        pavX = 0;
        pavY += HAUTEUR_PAV;
    }
}

// récupérer coord personnage, voir si cette case contient un objet
// relire la case dans laquelle on avance est une case obstacle ou une case vide même si cette case contient un objet
SDL_Rect newrect(int x, int y, int w, int h)
{
    SDL_Rect new;
    new.x = x;
    new.y = y;
    new.w = w;
    new.h = h;

    return new;
}

// INITIALISATION SDL,

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h)
{
    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        fprintf(stderr, "Erreur SDL_Init : %s", SDL_GetError());
        return -1;
    }
    if (0 != SDL_CreateWindowAndRenderer(w, h, SDL_WINDOW_SHOWN, window, renderer))
    {
        fprintf(stderr, "Erreur SDL_CreateWindowAndRenderer : %s", SDL_GetError());
        return -1;
    }
    return 0;
}

int setWindowColor(SDL_Renderer *renderer, SDL_Color color)
{
    if (SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a) < 0)
        return -1;
    if (SDL_RenderClear(renderer) < 0)
        return -1;
    return 0;
}

SDL_Texture *loadImage(const char *path, SDL_Renderer *renderer)
{
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    tmp = SDL_LoadBMP(path);
    if (NULL == tmp)
    {
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
        return NULL;
    }
    texture = SDL_CreateTextureFromSurface(renderer, tmp);

    if (NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return NULL;
    }

    SDL_FreeSurface(tmp);
    return texture;
}

SDL_Texture *LoadImage_transp(const char *path, SDL_Renderer *renderer, Uint8 r, Uint8 g, Uint8 b)
{
    SDL_Surface *tmp = NULL;
    SDL_Texture *texture = NULL;
    Uint32 keycolor;

    tmp = SDL_LoadBMP(path);
    if (NULL == tmp)
    {
        fprintf(stderr, "Erreur SDL_LoadBMP : %s", SDL_GetError());
        return NULL;
    }

    keycolor = SDL_MapRGB(tmp->format, r, g, b);
    SDL_SetColorKey(tmp, SDL_TRUE, keycolor);
    texture = SDL_CreateTextureFromSurface(renderer, tmp);

    if (NULL == texture)
    {
        fprintf(stderr, "Erreur SDL_CreateTextureFromSurface : %s", SDL_GetError());
        return NULL;
    }
    SDL_FreeSurface(tmp);
    return texture;
}
