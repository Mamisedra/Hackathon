#include "../../include/header.h"


void    biby(int *fd)
{
    int i = 0, j = 0, l = 1;
    //int pts = 0;
    char *line;
    char  str[250];
    t_sub   sub;

    sub.ques = (questab *)malloc(50 * sizeof(questab));
    if (!sub.ques)
    {
        perror("Error malloc");
        return ;
    }
    while ((line = get_next_line(fd[0])))
    {
        if (j == 0)
        {
            sub.ques[i].q = (question *)malloc(8 * sizeof(question));
            if(!sub.ques[i].q)
            {
                perror("Erreur malloc");
                return ;
            }
        }
        line += 2;
        // printf("Line:%s\n", line);
        sub.ques[i].q[j].q = strdup(line);
        if(sub.ques[i].q[j].q == NULL)
        {
            perror("Erreur farany");

        }
        if (j % 3 == 0 && j != 0)
        {
            i++;
            j = -1;
        }
        j++;
    }
    i = 0;
    while((line = get_next_line(fd[1])))
    {
        line += 2;
        sub.ques[i].answer = strdup(line);
        i++;
    }
    for (size_t i = 0; i < 5; i++)
    {
        printf("IZA ARY AHO?\n");
        for (size_t j = 0; j < 4; j++)
        {
            printf("Izaho dia %s",sub.ques[i].q[j].q);
            scanf("%s", str);
            for(size_t k = 0; k < strlen(str); k++)
                str[k] = tolower(str[k]);
            if (strncmp(str, sub.ques[i].answer, strlen(str)) == 0)
            {
                printf("\x1b[32m""Marina ehhh!!\n""\x1b[0m");
                l = 1;
                break;
            }
            else
            {
                printf("\x1b[31m""Disoo\n""\x1b[0m");
                l = 0;
            }
        }
        if (l == 0)
        {
            printf("\x1b[32m""Valiny: %s\n""\x1b[0m", sub.ques[i].answer);
            break;
        }
    }
}
