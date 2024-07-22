#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#ifndef LISTE_H
#define LISTE_H

typedef struct elem{
    int val; /* La valeur de l'objet*/
    struct elem* suiv; /* L'élément suivant*/
}t_elem;

/**
 * @brief Fonction d'initialisation (vide)
 * 
 * @return t_elem* 
 */
t_elem* init_vide();

/**
 * @brief Fonction d'initialisation avec un élément
 * 
 * @return t_elem* 
 */
t_elem* init_val(int val);



/**
 * @brief Fonction d'ajout, avec une valeur
 * @return t_elem* 
 */
t_elem* add_val(t_elem* e, int val);


/**
 * @brief Fonction rest qui renvoie le reste de la liste
 * @param e Une liste t_elem*
 * @return t_elem* 
 */
t_elem* rest(t_elem* e );

/**
 * @brief Fonction pour savoir si la liste est vide
 * @param e Une liste t_elem*
 * @return boolean
 */
bool empty(t_elem* e);

/**
 * @brief Fonction qui renvoie la longueur de la liste
 * @param e Une liste t_elem*
 * @return entier
 */
int length(t_elem* e);

/**
 * @brief Fonction pour modifier le reste de la liste
 * @param e Une liste t_elem*
 * @param c Une liste t_elem*
 * @return e, avec pour rest c
 */
t_elem* modif_rest(t_elem* e, t_elem* c);

/**
 * @brief Fonction supprimer un élément dans la liste
 * @param e Une liste t_elem*
 * @param val la valeur (int) à supprimer
 * @return e, avec pour rest c
 */
t_elem* supp(t_elem* e, int val);

/**
 * @brief Fonction pour savoir si un élément est présent dans la liste
 * @param e Une liste t_elem*
 * @param val La valeur à chercher
 * @return boolean
 */
bool search(t_elem* e, int val);

/**
 * @brief Fonction qui renvoie la valeur du premier élément de la liste
 * @param e Une liste t_elem*
 * @return Un entier
 */
int get_value(t_elem* e);

/**
 * @brief Fonction qui affiche la liste (pour les tests)
 * @param e Une liste t_elem*
 */
void print(t_elem* e);

/**
 * @brief Retourne une chaine de caracteres des elements de la liste
 * 
 */
char* to_string(t_elem* e);

/**
 * @brief Liberer la liste
 * 
 * @param e 
 */
void freeL(t_elem* e);

#endif
