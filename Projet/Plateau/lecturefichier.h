#ifndef LECTUREFICHIER_H
#define LECTUREFICHIER_H
#include <SDL2/SDL.h>
#include <stdlib.h>
#include <stdio.h>

char **allouer_tab_2D(int n, int m);

void desallouer_tab_2D(char **tab, int n);

int **allouer_tab_2Di(int n, int m);

void desallouer_tab_2Di(int **tab, int n);

void afficher_tab_2D(char **tab, int n, int m);

char **lire_fichier(const char *nomFichier);

int taille_fichier(const char *nomFichier, int *nbLig, int *nbCol);

char **modifier_charactere(char **tab, int n, int m, char ancien, char nouveau);

void ecrire_fichier(const char *nomFichier, char **tab, int n, int m);

#endif