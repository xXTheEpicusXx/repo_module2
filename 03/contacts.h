#define STR_LEN 30
#define ARR_SIZE 10

typedef struct
{
    char surname[STR_LEN];
    char name[STR_LEN];
    char secondname[STR_LEN];
} Fullname;

typedef struct
{
    char place[STR_LEN];
    char post[STR_LEN];
} Work;

typedef struct
{
    char name[STR_LEN];
    char link[STR_LEN];
} SocialNetwork;

typedef struct
{
    Fullname fullname;
    Work work;
    char phone[STR_LEN];
    char email[STR_LEN];
    int socialCnt;
    SocialNetwork socNets[ARR_SIZE];
} Contact;

void add(Fullname fn, ...);
void edit(Fullname fn, ...);
void delete(Fullname fn);
void print_contact(const Contact *c);
void find_and_print(Fullname fn);
