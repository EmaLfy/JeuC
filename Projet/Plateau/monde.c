#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#include "monde.h"
#include "liste.h"

monde_t *init_monde()
{
    monde_t *w = malloc(sizeof(monde_t));
    t_elem *ob = init_vide();
    w->objects = ob;
    return w;
}

t_elem *get_objects(monde_t *m)
{
    return m->objects;
}

void ajouter(monde_t *m, int val)
{
    m->objects = add_val(m->objects, val);
}

void *suppM(monde_t *m, int val)
{
    m->objects = supp(m->objects, val);
    return m;
}

void freeM(monde_t *m)
{
    freeL(get_objects(m));
    free(m);
}