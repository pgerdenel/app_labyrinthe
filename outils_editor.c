#include "outils_editor.h"

void afficherCarte(int fd)
{
    int x, y;
    unsigned char tmp;
    if (lseek(fd, CARTE, SEEK_SET) < 0)
    {
        perror("Erreur durant le seek\n");
    }
    for (x = 0; x < 15; x++)
    {
        for (y = 0; y < 30; y++)
        {
            tmp = lireChar(fd);
            if ((x == DEPARTX) && (y == DEPARTY))
            {
                if (mvaddch(x + POSX, y + POSY, 'D' | COLOR_PAIR(8)) == ERR)
                {
                    fprintf(stderr, "Erreur mvwaddch");
                    exit(EXIT_FAILURE);
                }
            }
            else if (tmp == 7)
            {
                if (mvaddch(x + POSX, y + POSY, 'S' | COLOR_PAIR(tmp)) == ERR)
                {
                    fprintf(stderr, "Erreur mvwaddch");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                if (mvaddch(x + POSX, y + POSY, ACS_BLOCK | COLOR_PAIR(tmp)) == ERR)
                {
                    fprintf(stderr, "Erreur mvwaddch");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
}

int creerPartie(char *name)
{
    int fd, fd2, tmp;
    char *reverse;
    char nom[64] = "";
    unsigned char *buf = malloc(458 * sizeof(unsigned char));
    reverse = strrev(name);
    if (strncmp(reverse, "nib.emag", 8) == 0)
    {
        if ((fd2 = open(name, O_RDWR, S_IRWXU)) == -1)
        {
            perror("Erreur open: ");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if ((fd = open(name, O_RDWR, S_IRWXU)) == -1)
        {
            perror("Erreur open: ");
            exit(EXIT_FAILURE);
        }
        if (lseek(fd, 0, SEEK_SET) < 0)
        {
            perror("Erreur durant le seek\n");
        }
        tmp = lireInt(fd);
        strncat(nom, name, strlen(name) - 4);
        sprintf(nom, "%s_%d_game.bin",nom, tmp);
        if (lseek(fd, 0, SEEK_SET) < 0)
        {
            perror("Erreur durant le seek\n");
        }
        buf = lireStr(fd, 458);
        if ((fd2 = open(nom, O_CREAT | O_RDWR, S_IRWXU)) == -1)
        {
            perror("Erreur open: ");
            exit(EXIT_FAILURE);
        }
        ecrireStr(fd2, (char *)buf, 458);
    }
    free(buf);
    return fd2;
}

void afficherJeu(int fd)
{
    int x, y;
    unsigned char tmp;
    if (lseek(fd, CARTE, SEEK_SET) < 0)
    {
        perror("Erreur durant le seek\n");
    }
    for (x = 0; x < 15; x++)
    {
        for (y = 0; y < 30; y++)
        {
            tmp = lireChar(fd);
            if (tmp == 7)
            {
                if (mvaddch(x + POSX, y + POSY, 'S' | COLOR_PAIR(tmp)) == ERR)
                {
                    fprintf(stderr, "Erreur mvwaddch");
                    exit(EXIT_FAILURE);
                }
            }
            else if (tmp == 5)
            {

                if (mvaddch(x + POSX, y + POSY, ACS_BLOCK | COLOR_PAIR(3)) == ERR)
                {
                    fprintf(stderr, "Erreur mvwaddch");
                    exit(EXIT_FAILURE);
                }
            }
            else
            {
                if (mvaddch(x + POSX, y + POSY, ACS_BLOCK | COLOR_PAIR(tmp)) == ERR)
                {
                    fprintf(stderr, "Erreur mvwaddch");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }
}

void changeColor(int x, int y, int fd)
{
    unsigned char tmp;
    if (!((x - POSX) == DEPARTX && (y - POSY) == DEPARTY))
    {
        if (lseek(fd, CARTE + (30 * (x - POSX)) + (y - POSY), SEEK_SET) < 0)
        {
            perror("Erreur durant le seek\n");
        }
        tmp = lireChar(fd);
        if (lseek(fd, -1, SEEK_CUR) < 0)
        {
            perror("Erreur durant le seek\n");
        }
        if (tmp == 3 || tmp == 4)
        {
            tmp++;
        }
        else if (tmp == 5)
        {
            tmp = 3;
        }
        else
        {
        }
        ecrireChar(fd, tmp);
        if (mvaddch(x, y, ACS_BLOCK | COLOR_PAIR(tmp)) == ERR)
        {
            fprintf(stderr, "Erreur mvwaddch");
            exit(EXIT_FAILURE);
        }
    }
}

void chargerCouleur(int x, int y, int fd)
{
    unsigned char tmp;
    if (lseek(fd, CARTE + (30 * x) + y, SEEK_SET) < 0)
    {
        perror("Erreur durant le seek\n");
    }
    tmp = lireChar(fd);
    if (mvaddch(x + POSX, y + POSY, ACS_BLOCK | COLOR_PAIR(tmp)) == ERR)
    {
        fprintf(stderr, "Erreur mvwaddch");
        exit(EXIT_FAILURE);
    }
}

int setPosition(int x, int y, int fd, WINDOW *win)
{
    int r = 1;
    unsigned char tmp;
    if (lseek(fd, 5 + (30 * x) + y, SEEK_SET) < 0)
    {
        perror("Erreur durant le seek\n");
    }
    tmp = lireChar(fd);
    if (!(tmp == 4 || tmp == 5))
    {
        if (lseek(fd, 5 + (30 * x) + y, SEEK_SET) < 0)
        {
            perror("Erreur durant le seek\n");
        }
        ecrireChar(fd, 6);
        if (lseek(fd, POSJOUEUR, SEEK_SET) < 0)
        {
            perror("Erreur durant le seek\n");
        }
        ecrireChar(fd, x);
        ecrireChar(fd, y);
        if (mvaddch(x + POSX, y + POSY, ACS_BLOCK | COLOR_PAIR(8)) == ERR)
        {
            fprintf(stderr, "Erreur mvwaddch");
            exit(EXIT_FAILURE);
        }
    }
    else if (tmp == 5)
    {
        r = 0;
        if (mvaddch(x + POSX, y + POSY, ACS_BLOCK | COLOR_PAIR(tmp)) == ERR)
        {
            fprintf(stderr, "Erreur mvwaddch");
            exit(EXIT_FAILURE);
        }
        if (lseek(fd, HP, SEEK_SET) < 0)
        {
            perror("Erreur durant le seek\n");
        }
        tmp = lireChar(fd);
        if (lseek(fd, HP, SEEK_SET) < 0)
        {
            perror("Erreur durant le seek\n");
        }
        ecrireChar(fd, (tmp - 1));
        afficherHp(win, fd);
    }
    else if(tmp == 4){
        r = 0;
    }
    else
    {
    }
    return r;
}

void afficherJoueur(int fd)
{
    int x, y;
    if (lseek(fd, POSJOUEUR, SEEK_SET) < 0)
    {
        perror("Erreur durant le seek\n");
    }
    x = lireChar(fd);
    y = lireChar(fd);
    if (mvaddch(x + POSX, y + POSY, ACS_BLOCK | COLOR_PAIR(8)) == ERR)
    {
        fprintf(stderr, "Erreur mvwaddch");
        exit(EXIT_FAILURE);
    }
}

int gagne(int fd)
{
    int x, y;
    if (lseek(fd, POSJOUEUR, SEEK_SET) < 0)
    {
        perror("Erreur durant le seek\n");
    }
    x = lireChar(fd);
    y = lireChar(fd);
    return (x == SORTIEX && y == SORTIEY);
}

void afficherHp(WINDOW *win, int fd)
{
    unsigned char hp, hpmax;
    if (lseek(fd, HP, SEEK_SET) < 0)
    {
        perror("Erreur durant le seek\n");
    }
    hp = lireChar(fd);
    if (lseek(fd, HPMAX, SEEK_SET) < 0)
    {
        perror("Erreur durant le seek\n");
    }
    hpmax = lireChar(fd);
    if (hp < 10)
    {
        mvwprintw(win, 0, 0, "Vie : 0%d/%d", hp, hpmax);
    }
    else
    {
        mvwprintw(win, 0, 0, "Vie : %d/%d", hp, hpmax);
    }
    wrefresh(win);
}

int perdu(int fd)
{
    int hp;
    if (lseek(fd, HP, SEEK_SET) < 0)
    {
        perror("Erreur durant le seek\n");
    }
    hp = lireChar(fd);
    return hp == 0;
}