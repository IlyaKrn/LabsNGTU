#include <stdio.h>
#include "domain.h"

int main()
{
    printf("Select action\n");
    printf("1 - create database\n");
    printf("2 - save data\n");
    printf("3 - get all data\n");
    printf("4 - search\n");

    int action;
    scanf("%d", &action);

    switch (action)
    {
    case 1:
        createDatabase();
        break;
    case 2:
        save();
        break;
    case 3:
        getAll();
        break;
    case 4:
        search();
        break;
    default:
        printf("action %d not found\n", action);
        break;
    }
    
}