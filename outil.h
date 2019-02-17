#ifndef __OUTIL_H__
#define __OUTIL_H__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <ncurses.h>

#define CARTE 5
#define DEPARTX 14
#define DEPARTY 0
#define SORTIEX 0
#define SORTIEY 29
#define HPMAX 4
#define HP 455
#define POSJOUEUR 456
#define POSX 6
#define POSY 2

int creerCarte(char *);
/*void afficherCarte(int);*/
void ecrireStr(int, char *, size_t);
void ecrireInt(int, int);
void ecrireChar(int, unsigned char);
unsigned char *lireStr(int, size_t);
int lireInt(int);
unsigned char lireChar(int);
void init_couleur();
char *strrev(char *);

#endif