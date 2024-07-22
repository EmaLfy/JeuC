#include <stdlib.h>
#include <stdio.h>
#include "../donnees/constante.h"

// fd : facteur de direction
void deplacerHB(int *posY, int *spriteY, int fd, int nbLig)
{
    if (*posY == 0)
    {
        if (fd > 0)
        {
            *posY += fd;
            *spriteY += HAUTEUR_PAV;
        }
    }
    else if (*posY == nbLig - 1)
    {
        if (fd < 0)
        {
            int newfd;
            newfd = abs(fd);
            *posY -= newfd;
            *spriteY -= HAUTEUR_PAV;
        }
    }
    else if (*posY > 0 && *posY < nbLig - 1)
    {
        if (fd < 0)
        {
            int newfd;
            newfd = abs(fd);
            *posY -= newfd;
            *spriteY -= HAUTEUR_PAV;
        }
        else
        {
            *posY += fd;
            *spriteY += HAUTEUR_PAV;
        }
    }
}

void deplacerDG(int *posX, int *spriteX, int fd, int nbCol)
{
    if (*posX == 0)
    {
        if (fd > 0)
        {
            *posX += fd;
            *spriteX += (HAUTEUR_PAV * fd);
        }
    }
    else if (*posX == nbCol - 1)
    {
        if (fd < 0)
        {
            int newfd;
            newfd = abs(fd);
            *posX -= newfd;
            *spriteX -= HAUTEUR_PAV;
        }
    }
    else if (*posX > 0 && *posX < nbCol - 1)
    {
        if (fd < 0)
        {
            int newfd;
            newfd = abs(fd);
            *posX -= newfd;
            *spriteX -= HAUTEUR_PAV;
        }
        else if (fd > 0)
        {
            *posX += fd;
            *spriteX += (HAUTEUR_PAV * fd);
        }
    }
}
