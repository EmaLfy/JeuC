#include "fonctions_SDL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Affichage du menu jusqu'à ce que le joueur choisisse si il veut jouer, dans ce cas la fonction renvoie 1, si on clique sur quit elle renvoie 0 et -1 si erreur
 * @return int
 */
int finjeu()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *fond = NULL;
    SDL_Event event;
    int out = -1;

    SDL_Color blanc = {255, 255, 255, 255};
    if (0 != init(&window, &renderer, 1400, 948))
        goto Quit;

    fond = loadImage("ressources/fin.bmp", renderer); // chargement image fond
    if (NULL == fond)
        goto Quit;

    setWindowColor(renderer, blanc);
    SDL_bool run = SDL_TRUE;
    while (run)
    {

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {

            case SDL_QUIT:
                run = SDL_FALSE;
                break;

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    run = SDL_FALSE;
                    break;
                }
            }
            SDL_RenderCopy(renderer, fond, NULL, NULL); // fond
            SDL_RenderPresent(renderer);
        }
    }

Quit:
    if (NULL != fond)
        SDL_DestroyTexture(fond);
    if (NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if (NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return out;
}