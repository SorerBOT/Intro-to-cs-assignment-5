#define MAX_WORKERS 50
#define MAX_PROJECTS 100
#define FIRST_OPTION 1
#define SECOND_OPTION 2
#define THIRD_OPTION 3
#define FOURTH_OPTION 4
#define FIFTH_OPTION 5
#define SIXTH_OPTION 6
#define SEVENTH_OPTION 7
#define EIGHTH_OPTION 8

// Exit codes
#define FAILED_TO_ALLOCATE_WORKERS_ARRAY_CODE 101
#define FAILED_TO_ALLOCATE_STRING_CODE 102
#define FAILED_TO_ALLOCATE_WORKER_CODE 103
#define FAILED_TO_ALLOCATE_WORKER_NAME_CODE 104
#define FAILED_TO_ALLOCATE_PROJECTS_ARRAY_CODE 105
#define FAILED_TO_ALLOCATE_PROJECT 106
#define FAILED_TO_ALLOCATE_PROJECT_NAME_CODE 107
#define FAILED_TO_ALLOCATE_PROJECT_WORKERS_ARRAY_CODE 108
#define FAILED_TO_ALLOCATE_PROJECT_FEATURES_CODE 109
#define FAILED_TO_REALLOCATE_WORKER_PROJECT_ARRAY_CODE 110
// Forward declarations
typedef struct Worker Worker;
typedef struct FeatureNode FeatureNode;
typedef struct Project Project;
typedef struct Company Company;

typedef enum { false, true } boolean;

struct Worker
{
    char *name;
    Project **projects;
    int projectCount;
};

struct FeatureNode
{
    char *feature;
    struct FeatureNode *next;
};

struct Project
{
    char *name;
    Worker **workers;
    int workerCount;
    FeatureNode *features;
};
struct Company
{
    Worker** workers;
    int workerCount;
    Project** projects;
    int projectCount;
};

void menu(Company *company);
void clearInputBuffer(void);
char *getChars(void);
int isStringEmpty(const char *name);
boolean isWorkerNameExists(Worker *workers[], int workerCount, const char *name);
boolean isProjectNameExists(Project *projects[], int projectCount, const char *name);
boolean isWorkerInProject(Project *project, Worker *worker);
int isFeatureExists(FeatureNode *head, const char *featureName);
void joinCompany(Worker *workers[], int *workerCount);
void openNewProject(Worker *workers[], int workerCount, Project *projects[], int *projectCount);
void workerJoinsProject(Worker *workers[], int workerCount, Project *projects[], int projectCount);
void addWorkerToProject(Worker *worker, Project *project);
void displayWorkers(Worker *workers[], int workerCount);
void displayProjects(Project *projects[], int projectCount);
void displayAllProjects(Project *projects[], int projectCount);
void displayAllWorkers(Worker *workers[], int workerCount);
void workOnProject(Worker *workers[], int workerCount, int *projectCount);
void addFeatureToProject(Project *project);
void removeFeatureFromProject(Project *project);
void leaveCompany(Worker *workers[], int *workerCount, Project *projects[], int *projectCount);
void freeWorker(Worker *worker);
void freeWorkers(Worker **workers, int workerCount);
void freeProject(Project *project);
void freeProjects(Project **projects, int projectCount);
void freeFeatures(FeatureNode *head);
void freeAllAllocations(Worker *workers[], int workerCount, Project *projects[], int projectCount);
void firstOption(Company *company);
void secondOption(Company *company);
void thirdOption(Company *company);
void printWorkers(Worker **workers, int numOfWorkers);
void printProjects(Project **projects, int numOfProjects);
Worker *selectWorkerByIndex(Worker **workers, int workerCount, char *message);
Project *selectProjectByIndex(Project **projects, int projectCount, char *message);