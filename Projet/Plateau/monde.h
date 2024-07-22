#include <stdlib.h>
#include <stdio.h>
#include "liste.h"

#ifndef MONDE_H
#define MONDE_H

struct monde_s
{
    t_elem *objects; /* L'élément suivant*/
};
typedef struct monde_s monde_t;

/**
 * @brief Initialisation des données du monde (+ initialisation de la liste des objets)
 * @return monde_t*
 */
monde_t *init_monde();

/**
 * @brief Recupere la liste d'objets
 * @return monde_t*
 */
t_elem *get_objects(monde_t *m);

/**
 * @brief Supprime un objet dans le monde
 *
 * @param m le monde
 * @param val la valeur à supprimer
 */
void *suppM(monde_t *m, int val);

/**
 * @brief Libere le monde
 * @return monde_t*
 */
void freeM(monde_t *m);

/**
 * @brief Fonction qui ajoute un objet dans le monde
 * 
 * @param m 
 * @param val 
 */
void ajouter(monde_t *m, int val);

#endif