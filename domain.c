#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"domain.h"

void createDatabase()
{
    FILE *file;
    file = fopen ("database", "w");
    fclose(file);
    printf("database created\n");
}
void save()
{
    FILE *file;
    file = fopen ("database", "a");
    Patient p;
    printf("%s", "enter age\n");
    scanf("%d", &p.age);
    printf("%s", "enter name\n");
    scanf("%s", &p.name);
    printf("%s", "enter diagnosis\n");
    scanf("%s", &p.diagnosis);
    fprintf(file, "%d %s %s\n", p.age, p.name, p.diagnosis);
    fclose(file);
    printf("data saved\n");
}
void search()
{
    FILE *file;
    file = fopen ("database", "r");
    int count = 0;
    Patient p;
    while (fscanf(file, " %d %s %s ", &p.age, p.name, p.diagnosis) == 3) {
        count++;
    }
    fclose(file);
    file = fopen ("database", "r");
    Patient *patients = (Patient*) malloc(sizeof(Patient) * count);
    for (int i = 0; i < count; i++)
    {
        int a;
        char n[20];
        char d[20];
        fscanf(file, "%d %s %s\n", &a, n, d);
        patients[i * sizeof(Patient)].age = a;
        strcpy(patients[i * sizeof(Patient)].name, n);
        strcpy(patients[i * sizeof(Patient)].diagnosis ,d);
    }
    printf("Select search type\n");
        printf("1 - by name\n");
        printf("2 - by age\n");
        printf("3 - by diagnosis\n");
        int type;
        scanf("%d", &type);
        switch (type)
        {
        case 1:
            char name[20];
            printf("Enter name\n");
            scanf("%s", &name);
            for (int i = 0; i < count; i++)
            {
                if(strcmp(patients[i * sizeof(Patient)].name, name) == 0)
                {
                    printf("name: %s\n", patients[i * sizeof(Patient)].name);
                    printf("age: %d\n", patients[i * sizeof(Patient)].age);
                    printf("diagnosis: %s\n\n", patients[i * sizeof(Patient)].diagnosis);
                }
            }
            break;
        case 2:
            int age;
            printf("Enter age\n");
            scanf("%d", &age);
            for (int i = 0; i < count; i++)
            {
                if(patients[i * sizeof(Patient)].age == age)
                {
                    printf("name: %s\n", patients[i * sizeof(Patient)].name);
                    printf("age: %d\n", patients[i * sizeof(Patient)].age);
                    printf("diagnosis: %s\n\n", patients[i * sizeof(Patient)].diagnosis);
                }
            }
            break;
        case 3:
            char diagnosis[20];
            printf("Enter diagnosis\n");
            scanf("%s", &diagnosis);
            for (int i = 0; i < count; i++)
            {
                if(strcmp(patients[i * sizeof(Patient)].diagnosis, diagnosis) == 0)
                {
                    printf("name: %s\n", patients[i * sizeof(Patient)].name);
                    printf("age: %d\n", patients[i * sizeof(Patient)].age);
                    printf("diagnosis: %s\n\n", patients[i * sizeof(Patient)].diagnosis);
                }
            }
            break;
        default:
            printf("type %d not found\n", type);
            break;
        }
    fclose(file);
    free(patients);
}

void getAll(){
    FILE *file;
    file = fopen ("database", "r");
    int count = 0;
    Patient p;
    while (fscanf(file, " %d %s %s\n", &p.age, p.name, p.diagnosis) == 3) {
        count++;
    }
    fclose(file);
    file = fopen ("database", "r");
    Patient *patients = (Patient*) malloc(sizeof(Patient) * count);
    for (int i = 0; i < count; i++)
    {
        int a;
        char n[20];
        char d[20];
        fscanf(file, "%d %s %s\n", &a, n, d);
        patients[i * sizeof(Patient)].age = a;
        strcpy(patients[i * sizeof(Patient)].name, n);
        strcpy(patients[i * sizeof(Patient)].diagnosis ,d);
    }
    for (int i = 0; i < count; i++)
    {
        printf("name: %s\n", patients[i * sizeof(Patient)].name);
        printf("age: %d\n", patients[i * sizeof(Patient)].age);
        printf("diagnosis: %s\n\n", patients[i * sizeof(Patient)].diagnosis);
    }
    fclose(file);
    free(patients);
}


