
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

#ifndef MENU_H
#define MENU_H

/**
 * @brief Affichage du menu jusqu'à ce que le joueur choisisse si il veut jouer, dans ce cas la fonction renvoie 1, si on clique sur quit elle renvoie 0 et -1 si erreur
 * @return int 
 */
int affichage_menu();

#endif