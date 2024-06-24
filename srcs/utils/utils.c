#include "../../include/header.h"

void    biby()
{
    int fd, fd2;
    int i = 1, k = 0;
    char *line, *val;
    char  valiny[250];

    fd = open("srcs/dic/biby.txt", O_RDONLY);
    fd2 = open("srcs/dic/valiny.txt", O_RDONLY);
    printf("IZA ARY AHO?\n");
    val = get_next_line(fd2);
    val += 2;
    while((line = get_next_line(fd)))
    {
        // printf("\ts:%s\n", val);
        while (line[0] == i + '0')
        {
            line +=2;
            printf("Izaho dia %s", line);
            scanf("%249s", valiny);
            for (size_t j = 0; j < strlen(valiny); j++) {
                valiny[j] = tolower(valiny[j]);
            }
            if (strncmp(val, valiny, strlen(valiny)) == 0)
            {
                printf("Marina\n");
                i++;
                val = get_next_line(fd2);
                if (val == NULL)
                {
                    k = 3;
                    break;
                }
                val += 2;
                k = 1;
                break;
            }
        }
        if (k == 1)
            printf("IZA ARY AHO?\n");
        else if(k == 3)
            exit(EXIT_SUCCESS);
        k = 0;
    }
    close(fd);
    close(fd2);
}
