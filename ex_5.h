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
#define ADD_PROJECT_COMMAND "add"
#define REMOVE_PROJECT_COMMAND "remove"
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
#define FAILED_TO_ALLOCATE_FEATURE_CODE 111
#define FAILED_TO_ALLOCATE_FEATURE_STRING_CODE 112
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
char *getChars(void);
void addFeatureToProject(Project *project);
void removeFeatureFromProject(Project *project);
void freeWorker(Worker *worker);
void freeWorkers(Worker **workers, int workerCount);
void freeProject(Project *project);
void freeProjects(Project **projects, int projectCount);
void freeFeatures(FeatureNode *head);
void firstOption(Company *company);
void secondOption(Company *company);
void thirdOption(Company *company);
void fourthOption(Company *company);
void fifthOption(Company *company);
void sixthOption(Company *company);
void seventhOption(Company *company);
boolean isWorkerNameExists(Worker *workers[], int workerCount, const char *name);
boolean isProjectNameExists(Project *projects[], int projectCount, const char *name);
boolean isWorkerInProject(Project *project, Worker *worker);
Worker *selectWorkerByIndex(Worker **workers, int workerCount, char *message);
Project *selectProjectByIndex(Project **projects, int projectCount, char *message, boolean verbose);
char *selectFeatureByIndex(FeatureNode *features, char *message);