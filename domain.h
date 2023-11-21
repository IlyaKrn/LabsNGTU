typedef struct patient
{
    int age;
    char name[20];
    char diagnosis[20];
} Patient;

void createDatabase();
void save();
void search();
void getAll();


