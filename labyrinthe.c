#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "outils_editor.h"
#include "outil.h"
#include "ncurses.h"

int main(int argc, char *argv[])
{
    int fd, i, x, y;
    WINDOW *winhp, *wininfo;
    char buf[80];
    char* tmp = buf;
    if (argc != 2)
    {
        printf("Erreur arg");
        exit(EXIT_FAILURE);
    }
    fd = creerPartie(argv[1]);
    ncurses_initialiser();
    ncurses_souris();
    ncurses_couleurs();
    init_couleur();

    clear();
    refresh();
    wininfo = newwin(3, 80, 2, 2);
    scrollok(wininfo, TRUE);
    winhp = newwin(5, 30, 8, 45);
    mvwprintw(winhp, 1, 2, "Mur decouvert");
    mvwprintw(winhp, 2, 2, "Mur visible");
    mvwprintw(winhp, 3, 2, "Valeureux guerrier");
    mvwprintw(winhp, 4, 2, "Sortie");
    if (mvaddch(9, 45, ACS_BLOCK | COLOR_PAIR(5)) == ERR)
    {
        fprintf(stderr, "Erreur mvwaddch");
        exit(EXIT_FAILURE);
    }
    if (mvaddch(10, 45, ACS_BLOCK | COLOR_PAIR(4)) == ERR)
    {
        fprintf(stderr, "Erreur mvwaddch");
        exit(EXIT_FAILURE);
    }
    if (mvaddch(11, 45, ACS_BLOCK | COLOR_PAIR(8)) == ERR)
    {
        fprintf(stderr, "Erreur mvwaddch");
        exit(EXIT_FAILURE);
    }
    if (mvaddch(12, 45, 'S' | COLOR_PAIR(7)) == ERR)
    {
        fprintf(stderr, "Erreur mvwaddch");
        exit(EXIT_FAILURE);
    }
    wbkgd(winhp, COLOR_PAIR(9));

    afficherJeu(fd);
    afficherHp(winhp, fd);
    afficherJoueur(fd);
    refresh();
    wrefresh(winhp);

    if (lseek(fd, POSJOUEUR, SEEK_SET) < 0)
    {
        perror("Erreur durant le seek\n");
    }
    x = lireChar(fd);
    y = lireChar(fd);

    while ((!gagne(fd) & !perdu(fd)) && ((i = getch()) != KEY_F(2)))
    {
        if (lseek(fd, POSJOUEUR, SEEK_SET) < 0)
        {
            perror("Erreur durant le seek\n");
        }
        x = lireChar(fd);
        y = lireChar(fd);
        if (i == KEY_LEFT)
        {
            if (y - 1 >= 0)
            {
                if (setPosition(x, y - 1, fd, winhp))
                {
                    tmp = "Vous etes alle a gauche : pas de mur";
                    chargerCouleur(x, y, fd);
                    y--;
                }
                else
                {
                    tmp = "Vous etes alle a gauche : mur";
                }
            }
        }
        else if (i == KEY_RIGHT)
        {
            if (y + 1 <= 29)
            {
                if (setPosition(x, y + 1, fd, winhp))
                {
                    tmp = "Vous etes alle a droite : pas de mur";
                    chargerCouleur(x, y, fd);
                    y++;
                }
                else
                {
                    tmp = "Vous etes alle a droite : mur";
                }
            }
        }
        else if (i == KEY_UP)
        {
            if (x - 1 >= 0)
            {
                if (setPosition(x - 1, y, fd, winhp))
                {
                    tmp = "Vous etes alle en haut : pas de mur";
                    chargerCouleur(x, y, fd);
                    x--;
                }
                else
                {
                    tmp = "Vous etes alle en haut : mur";
                }
            }
        }
        else if (KEY_DOWN)
        {
            if (x + 1 <= 14)
            {
                if (setPosition(x + 1, y, fd, winhp))
                {
                    tmp = "Vous etes alle en bas : pas de mur";
                    chargerCouleur(x, y, fd);
                    x++;
                }
                else
                {
                    tmp = "Vous etes alle en bas : mur";
                }
            }
        }
        else
        {
        }
        scroll(wininfo);
        mvwprintw(wininfo, 2, 0,tmp);
        wrefresh(wininfo);
        refresh();
    }
    if (gagne(fd))
    {
        tmp = "GAGNE!!!                            ";
    }
    if (perdu(fd))
    {
        tmp = "PERDU!!!                            ";
    }
    mvwprintw(wininfo, 2, 0, tmp);
    wrefresh(wininfo);
    refresh();
    sleep(5);
    ncurses_stopper();
    return EXIT_SUCCESS;
}