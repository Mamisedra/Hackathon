#include "../include/header.h"

int main()
{
    int choix;
    int fd[2];
 
    
    printf("1-Biby\n2-Toerana\n");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        {
            fd[0] = open("srcs/dic/biby.txt", O_RDONLY);
            fd[1] = open("srcs/dic/valiny.txt", O_RDONLY);
            biby(fd);
            close(fd[0]);
            close(fd[1]);
        }
        break;
    // case 2:
    //     {
    //         fd[0] = open("srcs/dic/toerana.txt", O_RDONLY);
    //         fd[1] = open("srcs/dic/v_toerana.txt", O_RDONLY);
    //         biby(fd);
    //         close(fd[0]);
    //         close(fd[1]);
    //     }
    //     break;
    default:
        break;
    }
    return (0);
}