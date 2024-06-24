#include "header.h"

void    biby(FILE *fptr)
{
    int fd, fd2;
    int i = 1;
    char *line, *val;
    char  valiny[250];

    fd = open("dic/biby.txt", O_RDONLY);
    printf("IZA ARY AHO\n");
    while(line = get_next_line(fd))
    {
        while (line[0] == i + '0')
        {
            line +=2;
            fd2 = open("dic/valiny.txt", O_RDONLY);
            val = get_next_line(fd2);
            val += 2;
            printf("Izaho dia %s", line);
            scanf("%s", &valiny);
            if (strcmp(valiny, val) == 0)
            {
                printf("Marina pr\n");
                i++; 
            }
        }

    }
}