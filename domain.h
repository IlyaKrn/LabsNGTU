typedef struct patient
{
    int age;
    char name[20];
    char diagnosis[20];
} Patient;

typedef enum searchType
{
    AGE, NAME, DIAGNISIS
} SearchType;

void createDatabase();
void save(Patient p);
void search(SearchType searchType, int age, char name[20], char diagnosis[20]);
void getAll();


