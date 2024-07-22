#include <SDL2/SDL.h>
#include "lecturefichier.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define MAX_SIZE 80

#ifndef FICHIER_H
#define FICHIER_H

/**
 * @brief Fonction qui ecrit dans le fichier sauvegarde.txt les données du joueur
 * 
 * @param chaine 
 */
void sauvegarde(char* chaine);

#endif