#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"domain.h"

void createDatabase()
{
    FILE *file;
    file = fopen ("database", "w");
    fclose(file);
    printf("%s", "database created\n");
}
void save(Patient p)
{
    FILE *file;
    file = fopen ("database", "w");
    fprintf(file, "%d %20s %20s\n", &p.age, &p.name, &p.diagnosis);
    fclose(file);
    printf("%s", "data saved\n");
}
void search(SearchType searchType, int age, char name[20], char diagnosis[20])
{
    FILE *file;
    file = fopen ("database", "r");
    int count = 0;
    Patient p;
    while (fscanf(file, " %d %20s %20s\n", &p.age, &p.name, &p.diagnosis) == 5) {
        count++;
    }
    Patient *patients = malloc(sizeof(Patient) * count);
    for (int i = 0; i < count; i++)
    {
        fscanf(file, "%d %20s %20s\n", 
         &patients[i * sizeof(Patient)].age,
         &patients[i * sizeof(Patient)].name, 
         &patients[i * sizeof(Patient)].diagnosis);
    }
    switch (searchType)
    {
    case AGE:
        for (int i = 0; i < count; i++)
        {
            if(patients[i * sizeof(Patient)].age == age)
            {
                printf("%d\n", patients[i * sizeof(Patient)].age);
                printf("%s\n", patients[i * sizeof(Patient)].name);
                printf("%s\n\n", patients[i * sizeof(Patient)].diagnosis);
            }
        }
        break;
    case NAME:
        for (int i = 0; i < count; i++)
        {
            if(strcmp(patients[i * sizeof(Patient)].name, name) == 0)
            {
                printf("%d\n", patients[i * sizeof(Patient)].age);
                printf("%s\n", patients[i * sizeof(Patient)].name);
                printf("%s\n\n", patients[i * sizeof(Patient)].diagnosis);
            }
        }
        break;
    case DIAGNISIS:
        for (int i = 0; i < count; i++)
        {
            if(strcmp(patients[i * sizeof(Patient)].diagnosis, diagnosis) == 0)
            {
                printf("%d\n", patients[i * sizeof(Patient)].age);
                printf("%s\n", patients[i * sizeof(Patient)].name);
                printf("%s\n\n", patients[i * sizeof(Patient)].diagnosis);
            }
        }
        break;
    default:
        break;
    }
    free(patients);
}

void getAll(){
    FILE *file;
    file = fopen ("database", "r");
    int count = 0;
    Patient p;
    while (fscanf(file, " %d %20s %20s\n", &p.age, &p.name, &p.diagnosis) == 5) {
        count++;
    }
    Patient *patients = malloc(sizeof(Patient) * count);
    for (int i = 0; i < count; i++)
    {
        fscanf(file, "%d %20s %20s\n", 
         &patients[i * sizeof(Patient)].age,
         &patients[i * sizeof(Patient)].name, 
         &patients[i * sizeof(Patient)].diagnosis);
    }
    for (int i = 0; i < count; i++)
    {
        printf("%d\n", patients[i * sizeof(Patient)].age);
        printf("%s\n", patients[i * sizeof(Patient)].name);
        printf("%s\n\n", patients[i * sizeof(Patient)].diagnosis);
    }
    free(patients);
}


