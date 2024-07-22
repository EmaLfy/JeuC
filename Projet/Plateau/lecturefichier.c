#include "lecturefichier.h"
#include <SDL2/SDL_image.h>
#include "../donnees/constante.h"
#include <stdlib.h>
#include <stdio.h>

char **allouer_tab_2D(int n, int m)
{
    int i;
    int j;
    char **tab = (char **)malloc(sizeof(char *) * n);
    for (i = 0; i < n; i++)
    {
        tab[i] = (char *)malloc(sizeof(char) * m);
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            tab[i][j] = ' ';
        }
    }
    return tab;
}

int **allouer_tab_2Di(int n, int m)
{
    int i;
    int j;
    int **tab = (int **)malloc(sizeof(int *) * n);
    for (i = 0; i < n; i++)
    {
        tab[i] = (int *)malloc(sizeof(int) * m);
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            tab[i][j] = ' ';
        }
    }
    return tab;
}

void desallouer_tab_2D(char **tab, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        free(tab[i]);
    }
    free(tab);
}

void desallouer_tab_2Di(int **tab, int n)
{
    int i;
    for (i = 0; i < n; i++)
    {
        free(tab[i]);
    }
    free(tab);
}

void afficher_tab_2D(char **tab, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            printf("%c", tab[i][j]);
        }
        printf("\n");
    }
}

int taille_fichier(const char *nomFichier, int *nbLig, int *nbCol)
{
    FILE *fichier = NULL;
    fichier = fopen(nomFichier, "r+");
    if (fichier == NULL)
    {
        perror("Erreur lors de la lecture du fichier");
        return 1;
    }

    fseek(fichier, 0, SEEK_END);
    long tfichier = ftell(fichier);
    if (tfichier == 0)
    {
        perror("LE fichier est vide. \n");
        return 1;
    }
    else
    {
        fseek(fichier, 0, SEEK_SET);
    }

    *nbLig = 0;
    *nbCol = 0;
    char i = 0;
    int col = 0;
    while (i != EOF)
    {
        i = fgetc(fichier);
        if (i != -1 && i != '0' && i != '1' && i != '2' && i != '3' && i != '4' && i != '5' && i != '6' && i != '7' && i != '8' && i != '9' && i != '\n' && i != '\r' && i != ' ')
        {
            perror("Caractère non autorisé");
            return 1;
        }
        if (i == '\n' || i == '\r')
        {
            if (col > 0)
                *nbLig += 1;
            if (*nbCol < col)
            {
                *nbCol = col;
            }
            col = 0;
        }
        else
        {
            col += 1;
        }
    }
    fclose(fichier);
    return 0;
}

char **lire_fichier(const char *nomFichier)
{
    FILE *fichier = fopen(nomFichier, "r");
    int nbLig;
    int nbCol;
    char **tab;

    if (fichier == NULL)
    {
        printf("Erreur lors de la lecture du fichier");
        return NULL;
    }
    taille_fichier(nomFichier, &nbLig, &nbCol);
    tab = allouer_tab_2D(nbLig, nbCol);
    if (tab == NULL)
    {
        fclose(fichier);
        return NULL;
    }

    char i = 0;
    int col = 0, lin = 0;
    while (i != EOF)
    {
        i = fgetc(fichier);
        if (i == '\n' || i == '\r')
        {
            if (col > 0)
                lin += 1;
            col = 0;
        }
        else
        {
            if (i != EOF)
            {
                tab[lin][col] = i;
                col += 1;
            }
        }
    }
    fclose(fichier);
    return tab;
}

char **modifier_charactere(char **tab, int n, int m, char ancien, char nouveau)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (tab[i][j] == ancien)
            {
                tab[i][j] = nouveau;
            }
            else
            {
                tab[i][j] = tab[i][j];
            }
        }
    }

    return tab;
}

void ecrire_fichier(const char *nomFichier, char **tab, int n, int m)
{ // ajouter du controle sur les caractères, des contraintes, afficher l'erreur des fichiers
    FILE *fichier = NULL;
    fichier = fopen(nomFichier, "w");
    if (fichier != NULL)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (tab[i][j] != ' ')
                {
                    fputc(tab[i][j], fichier);
                }
            }
            putc('\n', fichier);
        }
        fclose(fichier);
    }
}
