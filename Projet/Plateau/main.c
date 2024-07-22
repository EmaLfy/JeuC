#include <SDL2/SDL.h>
#include "menu.h"
#include "plateau.h"
#include "fin.h"
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int etat;
    etat = affichage_menu();
    if (etat == 1)
    {
        etat = affichage_plateau();
        if (etat == 0)
        {
            finjeu();
        }
    }
    

    return EXIT_SUCCESS;
}