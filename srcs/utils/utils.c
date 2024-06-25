#include "../../include/header.h"


void    biby()
{
    int fd, fd2;
    int i = 0, j = 0;//, k = 1;
    char *line;//, *val;
    char  str[250];
    t_sub   sub;

    fd = open("srcs/dic/biby.txt", O_RDONLY);
    fd2 = open("srcs/dic/valiny.txt", O_RDONLY);
    // printf("IZA ARY AHO?\n");
    sub.ques = (questab *)malloc(50 * sizeof(questab));
    if (!sub.ques)
    {
        perror("Error malloc");
        return ;
    }
    while ((line = get_next_line(fd)))
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
    while((line = get_next_line(fd2)))
    {
        line += 2;
        sub.ques[i].answer = strdup(line);
        i++;
    }
    for (size_t i = 0; i < 2; i++)
    {
        printf("IZA ARY AHO?\n");
        for (size_t j = 0; j < 4; j++)
        {
            printf("Izaho dia %s",sub.ques[i].q[j].q);
            scanf("%s", str);
            if (strncmp(str, sub.ques[i].answer, strlen(str)) == 0)
            {
                printf("Marina ehhh!!\n");
                break;
            }
        }
        
    }
    
    // val = get_next_line(fd2);
    // val += 2;
    // while((line = get_next_line(fd)))
    // {
    //     // printf("\ts:%s\n", val);
    //     while (line[0] == i + '0')
    //     {
    //         line +=2;
    //         printf("Izaho dia %s", line);
    //         scanf("%s", str);
    //         for (size_t j = 0; j < strlen(str); j++) {
    //             str[j] = tolower(str[j]);
    //         }
    //         if (strncmp(val, str, strlen(str)) == 0)
    //         {
    //             printf("Marina\n");
    //             i++;
    //             val = get_next_line(fd2);
    //             if (val == NULL)
    //             {
    //                 k = 3;
    //                 break;
    //             }
    //             val += 2;
    //             k = 1;
    //             break;
    //         }
    //     }
    //     if (k == 1)
    //         printf("IZA ARY AHO?\n");
    //     else if(k == 3)
    //         exit(EXIT_SUCCESS);
    //     k = 0;
    // }
    // close(fd);
    // close(fd2);
}
