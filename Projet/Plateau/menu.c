#include "fonctions_SDL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * @brief Affichage du menu jusqu'à ce que le joueur choisisse si il veut jouer, dans ce cas la fonction renvoie 1, si on clique sur quit elle renvoie 0 et -1 si erreur
 * @return int
 */
int affichage_menu()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *fond = NULL;
    SDL_Texture *logo = NULL;
    SDL_Texture *play = NULL;
    SDL_Texture *quit = NULL;
    SDL_Event event;
    int out = -1;

    Uint8 rm = 255;
    Uint8 gm = 255;
    Uint8 bm = 255;

    SDL_Color blanc = {255, 255, 255, 255};
    if (0 != init(&window, &renderer, 1400, 948))
        goto Quit;

    fond = loadImage("ressources/menu.bmp", renderer); // chargement image fond
    if (NULL == fond)
        goto Quit;

    logo = LoadImage_transp("ressources/logo2.bmp", renderer, rm, gm, bm); // chargement image transp logo
    play = LoadImage_transp("ressources/play.bmp", renderer, rm, gm, bm);  // chargement image transp bouton play
    quit = LoadImage_transp("ressources/quit2.bmp", renderer, rm, gm, bm); // chargement image transp bouton play

    SDL_Rect srcs;

    setWindowColor(renderer, blanc);
    SDL_bool run = SDL_TRUE;
    while (run)
    {

        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                out = 0;
                run = SDL_FALSE;
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.y > 271 && event.button.y <= 271 + 289 && event.button.x > 800 && event.button.x <= 800 + 425)
                {
                    play = LoadImage_transp("ressources/play2.bmp", renderer, rm, gm, bm);
                    SDL_Delay(40);
                    run = SDL_FALSE;
                    out = 1;
                }
                if (event.button.y > 500 && event.button.y <= 500 + 214 // si clic sur boutton
                    && event.button.x > 835 && event.button.x <= 835 + 350)
                {
                    quit = LoadImage_transp("ressources/quit.bmp", renderer, rm, gm, bm);
                    SDL_Delay(40);
                    run = SDL_FALSE;
                    out = 0;
                    break;
                }
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.y > 271 && event.button.y <= 271 + 289 && event.button.x > 800 && event.button.x <= 800 + 425)
                {
                    play = LoadImage_transp("ressources/play2.bmp", renderer, rm, gm, bm);
                }
                if (event.button.y > 500 && event.button.y <= 500 + 214 && event.button.x > 835 && event.button.x <= 835 + 350)
                {
                    quit = LoadImage_transp("ressources/quit.bmp", renderer, rm, gm, bm);
                }

            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    out = 0;
                    run = SDL_FALSE;
                    break;
                }
            }
        }
        SDL_RenderCopy(renderer, fond, NULL, NULL); // fond
        // SDL_Rect srcs;
        srcs.x = 0;
        srcs.y = 237;
        srcs.w = 700;
        srcs.h = 474;
        SDL_RenderCopy(renderer, logo, NULL, &srcs);
        srcs.x = 800;
        srcs.y = 271;
        srcs.w = 425;
        srcs.h = 289;
        SDL_RenderCopy(renderer, play, NULL, &srcs);
        srcs.x = 835;
        srcs.y = 500;
        srcs.w = 350;
        srcs.h = 214;
        SDL_RenderCopy(renderer, quit, NULL, &srcs);

        SDL_RenderPresent(renderer);
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
