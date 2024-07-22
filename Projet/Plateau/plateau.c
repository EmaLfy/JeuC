#include "fonctions_SDL.h"
#include "lecturefichier.h"
#include "Sprite.h"
#include "../donnees/constante.h"
#include "evenement.h"
#include "monde.h"
#include "fichier.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int affichage_plateau()
{
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;
    SDL_Texture *fond = NULL;
    SDL_Texture *textsprite = NULL;
    SDL_Texture *textsprite2 = NULL;
    SDL_Texture *pavage = NULL;
    SDL_Texture *obj = NULL;
    SDL_Texture *decor = NULL;
    SDL_Texture *grass = NULL;
    SDL_Event evenements;
    SDL_Keycode dernieretouche;
    sprite_t *player = malloc(sizeof(sprite_t));
    monde_t *monde;
    monde = init_monde();
    int numsprite = NONCOLLISION;

    int nbLig, nbCol, nbLigObj, nbColObj;
    char **tabpav;
    char **tabobj;
    int fichier;
    int fichierobj;
    int statut = -1;
    fichier = taille_fichier("terrain.txt", &nbLig, &nbCol);
    fichierobj = taille_fichier("objet.txt", &nbLigObj, &nbColObj);

    // TEST VALIDATION DES FICHIERS -------------------------
    if (fichier == 1 || fichierobj == 1)
    {
        perror("erreur lors de la lecture de fichier");
        return 0;
    }

    if (nbLig != nbLigObj || nbCol != nbColObj)
    {
        perror("La taille des fichiers n'est pas compatible");
        return 0;
    }
    tabpav = lire_fichier("terrain.txt");
    tabobj = lire_fichier("objet.txt");

    if (tabpav == NULL || tabobj == NULL)
    {
        perror("caractère non autorisé");
        return 0;
    }
    if (0 != init(&window, &renderer, HAUTEUR_PAV * nbCol, HAUTEUR_PAV * nbLig))
        goto Quit;
    // Charger les images --------------------------------------------
    fond = loadImage("ressources/fond.bmp", renderer);
    grass = loadImage("ressources/fond.bmp", renderer);
    textsprite = LoadImage_transp("ressources/sprites.bmp", renderer, 0, 255, 255);
    textsprite2 = LoadImage_transp("ressources/sprites2.bmp", renderer, 0, 255, 255);
    obj = LoadImage_transp("ressources/objet.bmp", renderer, 0, 255, 255);
    decor = LoadImage_transp("ressources/decor.bmp", renderer, 0, 255, 255);
    pavage = loadImage("ressources/pavage.bmp", renderer);
    if (NULL == fond || NULL == textsprite || NULL == obj || NULL == decor || NULL == textsprite2 || NULL == grass || NULL == pavage)
        goto Quit;

    // Position initiale des SDL Rect ---------------------------------
    int surfW = HAUTEUR_PAV;
    int surfH = HAUTEUR_PAV;

    SDL_Rect srcs[NBSPRITE];
    {
        for (int i = 0; i < 2; i++) // haut bas
        {
            srcs[i].x = 0;
            srcs[i].y = i * HAUTEUR_PAV;
            srcs[i].w = surfH;
            srcs[i].h = surfH;
        }
        for (int i = 0; i < 2; i++) // gauche droite
        {
            srcs[i + 2].x = HAUTEUR_PAV;
            srcs[i + 2].y = i * HAUTEUR_PAV;
            srcs[i + 2].w = surfH;
            srcs[i + 2].h = surfH;
        }
    }

    SDL_Rect srcp[NBPAV];
    for (int i = 0; i < NBPAV; i++)
    {
        srcp[i].x = (HAUTEUR_PAV * i);
        srcp[i].y = 0;
        srcp[i].w = surfH;
        srcp[i].h = surfH;
    }

    // Positions de destination des SDL Rect ---------------------------
    int spriteX = 0;
    int spriteY = 0;
    SDL_Rect DestR_sprite = newrect(spriteX, spriteY, surfW, surfH);

    // INFORMATION RELATIVE A LA POSITION DU PERSONNAGE SUR LECRAN --------------------
    int posy = 0;
    int posx = 0;
    player = initSprite2(player, posx, posy, spriteX, spriteY);
    // INITIALISATION DE LA LISTE DU MONDE -----------------------------------------------
    int objetmax = 0;
    char objetmin = OBJMINIMUMINTERATION + '0';
    for (int i = 0; i < nbLigObj; i++)
    {
        for (int j = 0; j < nbColObj; j++)
        {
            if (tabobj[i][j] >= '1' && tabobj[i][j] <= '9' && tabobj[i][j] != OBJETAIGNORER && tabobj[i][j] != FINDUJEU)
            {
                char entier = tabobj[i][j];
                int valentier = entier - '0';
                if (!search(monde->objects, valentier)) // objet unique dans l'inventaire
                {
                    if (valentier > objetmax)
                    {
                        objetmax = valentier;
                    }
                    ajouter(monde, valentier);
                }
            }
        }
    }
    // FIN INITIALISATION DEBUT BOUCLE INFINI -----------------------------------------------------
    int positionrect = 0;
    SDL_bool run = SDL_TRUE;
    while (run)
    {

        while (SDL_PollEvent(&evenements))
        {
            switch (evenements.type)
            {

            case SDL_QUIT:
                run = SDL_FALSE;
                break;
            case SDL_KEYDOWN:
                switch (evenements.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    run = SDL_FALSE;
                    break;
                case SDLK_z:
                    positionrect = SPRITEZ;
                    deplacerHB(&posy, &spriteY, -1, nbLig);
                    break;
                case SDLK_s:
                    positionrect = SPRITES;
                    deplacerHB(&posy, &spriteY, 1, nbLig);
                    break;
                case SDLK_q:
                    positionrect = SPRITEQ;
                    deplacerDG(&posx, &spriteX, -1, nbCol);
                    break;
                case SDLK_d:
                    positionrect = SPRITED;
                    deplacerDG(&posx, &spriteX, 1, nbCol);
                    break;
                }
                // INTERACTION AVEC UN OBJET --------------------
                if (tabobj[posy][posx] >= '1' && tabobj[posy][posx] <= '9')
                {
                    char obj = tabobj[posy][posx];
                    int valobj = obj - '0';
                    if (tabobj[posy][posx] == FINDUJEU)
                    {
                        int findujeu = FINDUJEU - '0';
                        RamasserObjet(player, monde, findujeu);
                        statut = 0;
                        goto Quit;
                    }
                    if (search(player->listeInv, valobj - 2) && search(player->listeInv, valobj - 1))
                    {

                        if ((obj == OBJETAIGNORER))
                        {
                            tabobj = modifier_charactere(tabobj, nbLigObj, nbColObj, obj, '0');
                        }
                        if (search(get_objects(monde), valobj))
                        {
                            if (objetmax > OBJMINIMUMINTERATION && valobj >= OBJMINIMUMINTERATION)
                            {
                                tabobj = modifier_charactere(tabobj, nbLigObj, nbColObj, obj, '0');
                                RamasserObjet(player, monde, valobj);
                                objetmin += 1; // empêche la collision des objets non récupérable suivant
                            }
                        }
                    }
                    else if (valobj < OBJMINIMUMINTERATION)
                    {
                        tabobj = modifier_charactere(tabobj, nbLigObj, nbColObj, obj, '0');
                        RamasserObjet(player, monde, valobj);
                    }
                }
                /// COLLISION ---------------------------------------------
                if ((tabpav[posy][posx] >= '1' && tabpav[posy][posx] <= '9') || tabobj[posy][posx] == OBJETAIGNORER || tabobj[posy][posx] >= objetmin)
                {
                    while ((tabpav[posy][posx] >= '1' && tabpav[posy][posx] <= '9') || tabobj[posy][posx] == OBJETAIGNORER || tabobj[posy][posx] >= objetmin)
                    {
                        if (evenements.type == SDL_KEYDOWN)
                        {
                            if (tabobj[posy][posx] == OBJETAIGNORER || tabobj[posy][posx] >= objetmin)
                            {
                                numsprite = COLLISION;
                            }
                            dernieretouche = evenements.key.keysym.sym;
                            if (dernieretouche == SDLK_z)
                            {
                                spriteY += HAUTEUR_PAV;
                                posy += 1;
                            }
                            else if (dernieretouche == SDLK_s)
                            {
                                spriteY -= HAUTEUR_PAV;
                                posy -= 1;
                            }
                            else if (dernieretouche == SDLK_q)
                            {
                                posx += 1;
                                spriteX += HAUTEUR_PAV;
                            }
                            else if (dernieretouche == SDLK_d)
                            {
                                posx -= 1;
                                spriteX -= HAUTEUR_PAV;
                            }
                        }
                    }
                }
                else
                {
                    numsprite = NONCOLLISION;
                }
            }
        }
        SetposX(player, posx);
        SetposY(player, posy);
        SetspriteX(player, spriteX);
        SetspriteY(player, spriteY);
        SDL_RenderClear(renderer);
        DestR_sprite.x = spriteX;
        DestR_sprite.y = spriteY;
        int pavX = 0;
        int pavY = 0;
        SDL_RenderCopy(renderer, fond, NULL, NULL);
        afficherFond(renderer, pavage, srcp, pavX, pavY, nbLig, nbCol, tabpav, NBPAV);
        SDL_RenderCopy(renderer, grass, NULL, NULL);
        afficherFond(renderer, obj, srcp, pavX, pavY, nbLigObj, nbColObj, tabobj, NBPAV);

        if (numsprite == 0)
        {
            SDL_RenderCopy(renderer, textsprite, &srcs[positionrect], &DestR_sprite);
        }
        else if (numsprite == 1)
        {
            SDL_RenderCopy(renderer, textsprite2, &srcs[positionrect], &DestR_sprite);
        }

        SDL_RenderCopy(renderer, decor, NULL, NULL);
        // Affichage des objets  de l'inventaire ---------------------------------------------
        int nbobjet = OBJETAIGNORER - '1';
        for (int i = 1; i < nbobjet + 1; i++)
        {
            if (search(player->listeInv, i))
            {
                SDL_Rect test = newrect(ESPACEENTREOBJET + i * HAUTEUR_PAV, ESPACEENTREOBJET + HAUTEUR_PAV, surfW, surfH);
                SDL_RenderCopy(renderer, obj, &srcp[i], &test);
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(30);
    }
Quit:

    sauvegarde(to_string(getInventaire(player)));
    freeS(player);
    freeM(monde);
    desallouer_tab_2D(tabpav, nbLig);
    desallouer_tab_2D(tabobj, nbLigObj);
    if (NULL != fond)
        SDL_DestroyTexture(fond);
    if (NULL != textsprite)
        SDL_DestroyTexture(textsprite);
    if (NULL != textsprite2)
        SDL_DestroyTexture(textsprite2);
    if (NULL != pavage)
        SDL_DestroyTexture(pavage);
    if (NULL != obj)
        SDL_DestroyTexture(obj);
    if (NULL != grass)
        SDL_DestroyTexture(grass);
    if (NULL != renderer)
        SDL_DestroyRenderer(renderer);
    if (NULL != window)
        SDL_DestroyWindow(window);
    SDL_Quit();
    return statut;
}
