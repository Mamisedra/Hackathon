#include "header.h"

void    biby(FILE *fptr)
{
    int fd, fd2;
    int i = 1, k = 0;
    char *line, *val;
    char  valiny[250];

    fd = open("dic/biby.txt", O_RDONLY);
    fd2 = open("dic/valiny.txt", O_RDONLY);
    printf("IZA ARY AHO?\n");
    while(line = get_next_line(fd))
    {
        while (line[0] == i + '0')
        {
            line +=2;
            val = get_next_line(fd2);
            val += 2;
            printf("Izaho dia %s", line);
            scanf("%s", &valiny);
            for (int j = 0; j < strlen(valiny); j++) {
                valiny[j] = tolower(valiny[j]);
            }
            if (strstr(val, valiny))
            {
                printf("Marina\n");
                i++;
                k = 1;
            }
        }
        if (k)
            printf("IZA ARY AHO?\n");
        k = 0;
    }
}