#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <strings.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

char     tab[300][300];
int     width;
int     hight;
char    bg;

typedef struct s_map 
{
    char c;
    float x;
    float y;
    float r;
    char character;
}   t_map;

void    init_map()
{
    int i;

    i = -1;
    while (++i < hight)
        memset(tab[i], bg, width);
}

int    print_all()
{
    int i;

    i = -1;
    while (++i < hight)
    {
        write(1, tab[i], width);
        write(1, "\n", 1);
    }
    return (0);
}

int print_err(char *s)
{
    int i;

    i = -1;
    while (s[++i])
        write(1, &s[i], 1);
    return (1);
}

int main(int ac, char **av)
{
    int i;
    int j;
    FILE *fd;
    int res;
    t_map map;
    float sqr;

    if (ac != 2)
        return (print_err("Error: argument\n"));
    fd = fopen(av[1], "r");
    if (!fd)
        return (print_err("Error: Operation file corrupted\n"));
    res = fscanf(fd,"%d %d %c \n", &width, &hight, &bg);
    if (res != 3 || width <= 0 || width > 300 || hight <= 0 || hight > 300)
        return (print_err("Error: Operation file corrupted\n"));
    init_map();
    while (res != -1)
    {
        res = fscanf(fd, "%c %f %f %f %c \n", &map.c , &map.x, &map.y, &map.r, &map.character);
        if (res == -1)
            return (print_all());
        if (res != 5 || (map.c != 'c' && map.c != 'C') || map.r <= 0)
            return (print_err("Error: Operation file corrupted\n"));
        i = -1;
        while (++i < hight)
        {
            j = -1;
            while (++j < width)
            {
                sqr = sqrt((j - map.x) * (j - map.x) + (i - map.y) * (i - map.y));
                if (sqr <= map.r)
                {
                    if (map.c == 'C' || (map.c == 'c' && sqr + 1 >= map.r))
                        tab[i][j] = map.character;
                }
            }
        }
    }
    return (0);
}