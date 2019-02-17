#ifndef __OUTILS_EDITOR_H__
#define __OUTILS_EDITOR_H__

#include <string.h>
#include "outil.h"

void afficherCarte(int);
int creerPartie(char*);
void afficherJeu(int);
void changeColor(int, int, int);
void chargerCouleur(int,int,int);
int setPosition(int,int,int,WINDOW*);
void afficherJoueur(int);
int gagne(int);
int perdu(int);
void afficherHp(WINDOW*,int);

#endif