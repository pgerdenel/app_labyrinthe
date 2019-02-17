#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "outils_editor.h"
#include "outil.h"
#include "ncurses.h"

#define LARGEUR 30 /* Largeur de la fenêtre */
#define HAUTEUR 15 /* Hauteur de la fenêtre */

int main(int argc, char *argv[])
{
    int fd, i;
    int x, y, bouton;
    if (argc != 2)
    {
        printf("Erreur arg");
        exit(EXIT_FAILURE);
    }

    fd = creerCarte(argv[1]);

    ncurses_initialiser();
    ncurses_souris();
    ncurses_couleurs();
    init_couleur();

    clear();
    refresh();

    afficherCarte(fd);
    refresh();

    while ((i = getch()) != KEY_F(2))
    {
        if (i == KEY_MOUSE)
        {
            if (souris_getpos(&y, &x, &bouton) == OK)
            {
                if (bouton & BUTTON1_CLICKED)
                {
                    if (x > 5 && x < 21 && y > 1 && y < 32)
                    {
                        if (!((x == (DEPARTX - POSX)) && (y == (DEPARTY - POSY))) || ((x == (SORTIEX - POSX)) && (y == (SORTIEY + POSY))))
                        {
                            changeColor(x, y, fd);
                        }
                    }
                }
            }
        }
        refresh();
    }

    ncurses_stopper();

    if (lseek(fd, 0, SEEK_SET) < 0)
    {
        perror("Erreur durant le seek\n");
    }
    i = lireInt(fd);
    if (lseek(fd, 0, SEEK_SET) < 0)
    {
        perror("Erreur durant le seek\n");
    }
    ecrireInt(fd, ++i);
    if (close(fd) == -1)
    {
        perror("Erreur close ");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}