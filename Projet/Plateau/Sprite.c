#include "Sprite.h"
#include "liste.h"
#include "monde.h"

sprite_t *initSprite2(sprite_t *newsprite, int x, int y, int SpriteX, int SpriteY)
{
    newsprite->posX = x;
    newsprite->posY = y;
    newsprite->SpriteX = x + HAUTEUR_PAV;
    newsprite->SpriteY = y + HAUTEUR_PAV;
    newsprite->h = HAUTEUR_PAV;
    newsprite->w = HAUTEUR_PAV;
    t_elem *listInv = init_vide();
    newsprite->listeInv = listInv;
    // texture
    return newsprite;
}

int getposX(sprite_t *sprite)
{
    return sprite->posX;
}

int getposY(sprite_t *sprite)
{
    return sprite->posY;
}

int getSpriteX(sprite_t *sprite)
{
    return sprite->SpriteX;
}

int getSpriteY(sprite_t *sprite)
{
    return sprite->SpriteY;
}

t_elem *getInventaire(sprite_t *sprite)
{
    return sprite->listeInv;
}

void SetposX(sprite_t *sprite, int newposx)
{
    sprite->posX = newposx;
}

void SetposY(sprite_t *sprite, int newposy)
{
    sprite->posY = newposy;
}

void SetspriteX(sprite_t *sprite, int spritex)
{
    sprite->SpriteX = spritex;
}

void SetspriteY(sprite_t *sprite, int spritey)
{
    sprite->SpriteY = spritey;
}

void RamasserObjet(sprite_t *sprite, monde_t *monde, int objetadd)
{
    sprite->listeInv = add_val(getInventaire(sprite), objetadd);
    suppM(monde, objetadd);
}

void freeS(sprite_t *s)
{
    freeL(s->listeInv);
    free(s);
}

void printsprite(sprite_t *sprite)
{
    if (sprite == NULL)
    {
        printf("Le joueur n'est pas initialisé");
    }
    else
    {
        printf("(x : %d ; y : %d) | (SpriteX : %d ; SpriteY : %d)  \n liste joueur : ", sprite->posX, sprite->posY, sprite->SpriteX, sprite->SpriteY);
        print(sprite->listeInv);
        printf("\n");
    }
}