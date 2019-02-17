#include "outil.h"

void init_couleur()
{
    init_pair(3, COLOR_WHITE, COLOR_WHITE);
    init_pair(4, COLOR_BLUE, COLOR_BLUE);
    init_pair(5, COLOR_RED, COLOR_RED);
    init_pair(6, COLOR_CYAN, COLOR_CYAN);
    init_pair(7, COLOR_WHITE, COLOR_YELLOW);
    init_pair(8, COLOR_GREEN, COLOR_GREEN);
    init_pair(9, COLOR_WHITE, COLOR_BLACK);
}

int creerCarte(char *nom)
{
    int fd, i;
    char buf[454];
    if ((fd = open(nom, O_CREAT | O_EXCL, S_IRWXU)) == -1)
    {
        if (errno == EEXIST && (fd = open(nom, O_RDWR, S_IRWXU)) == -1)
        {
            perror("Erreur open: ");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        if (close(fd) == -1)
        {
            perror("Erreur close ");
            exit(EXIT_FAILURE);
        }
        if ((fd = open(nom, O_RDWR, S_IRWXU)) == -1)
        {
            perror("Erreur open: ");
            exit(EXIT_FAILURE);
        }
        ecrireInt(fd, 0);
        buf[0] = 10;
        for (i = 1; i <= 450; ++i)
        {
            if (i == DEPARTX * 30 + DEPARTY + 1)
            {
                buf[i] = 6;
            }
            else if (i == SORTIEX * 30 + SORTIEY + 1)
            {
                buf[i] = 7;
            }
            else
            {
                buf[i] = 3;
            }
        }
        buf[451] = 10;
        buf[452] = DEPARTX;
        buf[453] = DEPARTY;
        ecrireStr(fd, buf, 454);
    }
    return fd;
}

void ecrireStr(int fd, char *str, size_t t)
{
    if (write(fd, str, t) != t)
    {
        perror("Erreur write: ");
        exit(EXIT_FAILURE);
    }
}

void ecrireInt(int fd, int n)
{
    if (write(fd, &n, sizeof(int)) != sizeof(int))
    {
        perror("Erreur write: ");
        exit(EXIT_FAILURE);
    }
}

void ecrireChar(int fd, unsigned char c)
{
    if (write(fd, &c, sizeof(unsigned char)) != sizeof(unsigned char))
    {
        perror("Erreur write: ");
        exit(EXIT_FAILURE);
    }
}

unsigned char *lireStr(int fd, size_t t)
{
    unsigned char *buf = malloc(t * sizeof(unsigned char));
    buf = malloc(sizeof(char) * t);
    if (read(fd, buf, t) == -1)
    {
        perror("Erreur read ");
        exit(EXIT_FAILURE);
    }
    return buf;
}

int lireInt(int fd)
{
    int n;
    if (read(fd, &n, sizeof(n)) == -1)
    {
        perror("Erreur read ");
        exit(EXIT_FAILURE);
    }
    return n;
}

unsigned char lireChar(int fd)
{
    unsigned char c;
    if (read(fd, &c, sizeof(c)) == -1)
    {
        perror("Erreur read ");
        exit(EXIT_FAILURE);
    }
    return c;
}

char *strrev(char *str)
{
    char *r = malloc((strlen(str) + 1) * sizeof(char));
    char *p1, *p2;
    if (!str || !*str){
        return str;
    }
    strcpy(r,str);
    for (p1 = r, p2 = r + strlen(r) - 1; p2 > p1; ++p1, --p2)
    {
        *p1 ^= *p2;
        *p2 ^= *p1;
        *p1 ^= *p2;
    }
    return r;
}