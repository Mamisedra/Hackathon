#include "header.h"

int main()
{
    int choix, fd;
    
    printf("1-Biby\n2-Fomba malagasy\n");
    scanf("%d", &choix);
    switch (choix)
    {
    case 1:
        biby();
        break;
    default:
        break;
    }
    return (0);
}