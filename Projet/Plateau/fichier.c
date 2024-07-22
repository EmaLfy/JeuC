#include "fichier.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

void sauvegarde(char *chaine)
{
    FILE *fichier = NULL;
    fichier = fopen("score.txt", "a+");
    time_t timestamp = time(NULL);
    struct tm *pTime = localtime(&timestamp);
    fputs("\n----------------------------\n", fichier);
    fprintf(fichier, "Date: %02d/%02d/%04d %02d:%02d:%02d\n",
            pTime->tm_mday, pTime->tm_mon + 1, pTime->tm_year + 1900,
            pTime->tm_hour, pTime->tm_min, pTime->tm_sec);
    fputs("Avancée du joueur:", fichier);
    fputs(chaine, fichier);
    free(chaine);
    fputs("\n----------------------------\n", fichier);
    fclose(fichier);
}