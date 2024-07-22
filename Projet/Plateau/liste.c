#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "liste.h"

t_elem *init_vide()
{
    return NULL;
}

t_elem *init_val(int val)
{
    t_elem *e = malloc(sizeof(*e));
    e->val = val;
    e->suiv = NULL;
    return e;
}

t_elem *add_val(t_elem *e, int val)
{
    t_elem *a = init_val(val);
    a->suiv = e;
    return a;
}

t_elem *rest(t_elem *e)
{
    if (empty(e))
    {
        return NULL;
    }
    else
    {
        return e->suiv;
    }
}

bool empty(t_elem *e)
{
    if (e == NULL)
    {
        return true;
    }
    return false;
}

int length(t_elem *e)
{
    if (empty(e))
    {
        return 0;
    }
    else
    {
        return 1 + length(rest(e));
    }
}

t_elem *modif_rest(t_elem *e, t_elem *c)
{
    e->suiv = c;
    return e;
}

t_elem *supp(t_elem *e, int val)
{
    t_elem *n;
    if (empty(e))
    {
        return e;
    }
    if (get_value(e) == val)
    {
        n = e;
        e = rest(e);
        free(n);
        return e;
    }
    if (empty(rest(e)))
    {
        return e;
    }
    else if (empty(rest(rest(e))))
    {
        if (val == get_value(rest(e)))
        {
            t_elem *tmp = e->suiv;
            e = modif_rest(e, init_vide());
            freeL(tmp);
            return e;
        }
        return e;
    }
    else if (val == get_value(e))
    {
        return e = rest(e);
    }
    else if (val == get_value(rest(e)))
    {
        t_elem *tmp = rest(e);
        e = modif_rest(e, rest(rest(e)));
        tmp = modif_rest(tmp, init_vide());
        freeL(tmp);
        return e;
    }
    else
    {
        e = modif_rest(e, supp(rest(e), val));
        return e;
    }
}

bool search(t_elem *e, int val)
{
    if (empty(e))
    {
        return false;
    }
    else if (get_value(e) == val)
    {
        return true;
    }
    else
    {
        return search(rest(e), val);
    }
}

int get_value(t_elem *e)
{
    return e->val;
}

void print(t_elem *e)
{
    if (empty(e))
    {
        printf("est vide");
    }
    else if (empty(rest(e)))
    {
        printf("%d ", get_value(e));
    }
    else
    {
        printf("%d ", get_value(e));
        print(rest(e));
    }
}

void freeL(t_elem *e)
{
    if (!empty(rest(e)))
    {
        t_elem *tmp = rest(e);
        free(e);
        freeL(tmp);
    }
    else
    {
        free(e);
    }
}

char *to_string(t_elem *e)
{
    
    int bufferSize = 100;
    int currentPosition = 0;
    char *buffer = (char *)malloc(bufferSize * sizeof(char));
    if(length(e)==0){

        int written = snprintf(buffer + currentPosition, bufferSize - currentPosition, "--");
        currentPosition += written;
        e = rest(e);
        return buffer;
    }
    while (!empty(e))
    {
        int written = snprintf(buffer + currentPosition, bufferSize - currentPosition, "%d ", get_value(e));
        if (written >= bufferSize - currentPosition)
        {
            bufferSize *= 2;
            buffer = (char *)realloc(buffer, bufferSize * sizeof(char));
        }

        currentPosition += written;
        e = rest(e);
    }

    return buffer;
}
