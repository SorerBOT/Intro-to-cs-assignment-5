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
#define INVALID_STRING_INPUT_CODE 113
// Forward declarations
typedef struct Worker Worker;
typedef struct FeatureNode FeatureNode;
typedef struct Project Project;
typedef struct Company Company;
// booleans
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
// New struct established in order to organise the data
struct Company
{
    Worker** workers;
    int workerCount;
    Project** projects;
    int projectCount;
};
/**
 * @param {company} an initialized Company
 * Recursively prompts the user to select an option number
 * Then runs the function associated with that option number
*/
void menu(Company *company);
/**
 * Prompts the user to enter a string
 * Clears the input buffer as it reads the string
 * Allowing for inputs like '   add' to be taken for 'add'
 * @return {char *}
*/
char *getChars(void);
/**
 * @param {project} the project to which the user would like to have a feature appended
 * adds the feature to the project
*/
void addFeatureToProject(Project *project);
/**
 * @param {project} the project from which the user would like to have a feature removed
 * removes the feature from the project
*/
void removeFeatureFromProject(Project *project);
/**
 * @param {worker} the worker which is to be free'd
 * frees the worker by individually freeing each of its members
*/
void freeWorker(Worker *worker);
/**
 * @param {workers} a dynamic array of {Worker}
 * @param {workerCount} the size of array {workers}
 * Iteratively frees each of the elements in {workers}
 * Relies on freeWorker
*/
void freeWorkers(Worker **workers, int workerCount);
/**
 * @param {project} the project to be free'd
 * frees the project by individually freeing each of its members
*/
void freeProject(Project *project);
/**
 * @param {projects} a dynamic array of {Project}
 * @param {projectCount} the size of the the array {projects}
 * Iteratively frees each of the elements in {projects}
 * Relies on freeProject
*/
void freeProjects(Project **projects, int projectCount);
/**
 * @param {head} a FeatureNode
 * Recursively frees every FeatureNode in the list
*/
void freeFeatures(FeatureNode *head);
/**
 * @param {company} the company
 * Runs the first option
*/
void firstOption(Company *company);
/**
 * @param {company}
 * Runs the second option
*/
void secondOption(Company *company);
/**
 * @param {company}
 * Runs the third option
*/
void thirdOption(Company *company);
/**
 * @param {company}
 * Runs the fourth option
*/
void fourthOption(Company *company);
/**
 * @param {company}
 * Runs the fifth option
*/
void fifthOption(Company *company);
/**
 * @param {company}
 * Runs the sixth option
*/
void sixthOption(Company *company);
/**
 * @param {company}
 * Runs the seventh option
*/
void seventhOption(Company *company);
/**
 * @param {workers} a dynamic array of {Worker}
 * @param {workerCount} the size of the array {workers}
 * @param {name} a name of a worker
 * Iteratively checks whether a worker of name {name} exists in the array {workers}
 * @return {boolean} true if such worker is found and false otherwise
*/
boolean isWorkerNameExists(Worker **workers, int workerCount, const char *name);
/**
 * @param {projects} a dynamic array of {Project}
 * @param {projectCount} the size of the array {projects}
 * @param {name} a name of project 
 * Iteratively checks whether a project of name {name} exists in the array {projects}
 * @return {boolean} true if such project is found and false otherwise
*/
boolean isProjectNameExists(Project **projects, int projectCount, const char *name);
/**
 * @param {project}
 * @param {worker}
 * @return {boolean} true if the worker is found in the project and false otherwise
*/
boolean isWorkerInProject(Project *project, Worker *worker);
/**
 * @param {workers} a dynamic array of type {Worker}
 * @param {workerCount} the size of the array {workers}
 * @param {message} a string
 * 
 * Firstly prints a list of all workers availably by interating over the array {workers}
 * Then prompts the user to select the index of the desired worker using {message}
 * 
 * @return {Worker*} a pointer to the selected worker
*/
Worker *selectWorkerByIndex(Worker **workers, int workerCount, char *message);
/**
 * @param {projects} a dynamic array of type {Project} 
 * @param {projectCount} the size of the array {projects}
 * @param {message} a string
 * 
 * Firstly prints a list of all projects availably by interating over the array {projects}
 * Then prompts the user to select the index of the desired project using {message}
 * 
 * @return {Project*} a pointer to the selected worker
*/

Project *selectProjectByIndex(Project **projects, int projectCount, char *message, boolean verbose);
/**
 * @param {features} a pointer to the first FeatureNode which may be chosen by the user
 * @param {message} a string
 * 
 * Firstly prints a list of all features availably by interating over the list {features}
 * Then prompts the user to select the index of the desired feature using {message}
 * 
 * @return {FeatureNode*} a pointer to the selected  
*/
char *selectFeatureByIndex(FeatureNode *features, char *message);