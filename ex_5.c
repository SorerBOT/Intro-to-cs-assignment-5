#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ex_5.h"

int main() {
    Company company;
    company.workerCount = 0;
    company.projectCount = 0;
    company.workers = NULL;
    company.projects = NULL;

    menu(&company);
    for (int i = 0; i < company.workerCount; i++) {
        freeWorker(company.workers[i]);
    }
    return 0;
}

void menu(Company *company) {
    if (company->workerCount > 0) printWorkers(company->workers, company->workerCount);
    if (company->projectCount > 0) printProjects(company->projects, company->projectCount);

    int selectedOption;
    printf(
        "Welcome!\n"
        "Please select the desired option:\n"
        "1. Join the company\n"
        "2. Open a new project\n"
        "3. Join an existing project\n"
        "4. See what projects are in work\n"
        "5. See which people are in what projects\n"
        "6. Work on existing project\n"
        "7. Leave the company\n"
        "8. Exit\n"
    );
    scanf( "%d", &selectedOption );

    if ( selectedOption > 8 || selectedOption < 1 ) {
        printf( "Invalid choice. Please try again." );
        return menu(company);
    }
    if ( selectedOption == FIRST_OPTION ) {
        firstOption(company);
    }
    if ( selectedOption == SECOND_OPTION ) {
        secondOption(company);
    }
    if ( selectedOption == EIGHTH_OPTION ) {
        return;
    }
    menu(company);
}

void firstOption(Company *company) {
    Worker *worker = NULL;
    char *workerName = NULL;

    printf("Enter the name of the new worker: ");
    workerName = getChars();
    if (isWorkerNameExists(company->workers, company->workerCount, workerName)) {
        printf(
            "A worker with this name already exists.\n"
            "There is not enough space in this company for both of us\n"
        );
        return;
    }
    company->workers = (Worker**)realloc(company->workers, (company->workerCount + 1) * sizeof(Worker*));
    if (company->workers == NULL) {
        exit(FAILED_TO_ALLOCATE_WORKERS_ARRAY_CODE);
    }
    company->workers[company->workerCount] = (Worker*)malloc(sizeof(Worker));
    if (company->workers[company->workerCount] == NULL) {
        exit(FAILED_TO_ALLOCATE_WORKER_CODE);
    }
    worker = company->workers[company->workerCount];
    worker->name = (char*)malloc((strlen(workerName) + 1) * sizeof(char));
    if (worker->name == NULL) {
        exit(FAILED_TO_ALLOCATE_WORKER_NAME_CODE);
    }
    strcpy(company->workers[company->workerCount]->name, workerName);
    worker->projectCount = 0;
    worker->projects = NULL;
    company->workerCount++;
}
void secondOption(Company *company) {
    char *projectName = NULL;
    Worker *worker = NULL;
    Project *project = NULL;
    int chosenWorkerIndex;
    if (company->workerCount == 0) {
        printf("There are no workers in the company yet, please join the company first.\n");
        return;
    }
    printf("Who are you? Choose a number:\n");
    for (int i = 0; i < company->workerCount; i++) {
        printf("%d. %s\n", i+1, company->workers[i]->name);
    }
    scanf("%d", &chosenWorkerIndex);
    if (chosenWorkerIndex - 1 > company->workerCount || chosenWorkerIndex < 0) {
        printf("Invalid worker selection.\n");
        return;
    }
    worker = company->workers[chosenWorkerIndex - 1];
    printf("Enter the name of the new project: ");
    projectName = getChars();
    company->projects = (Project**)realloc(company->projects, (company->projectCount + 1) * sizeof(Project*));
    if (company->projects == NULL) {
        exit(FAILED_TO_ALLOCATE_PROJECTS_ARRAY_CODE);
    }
    company->projects[company->projectCount] = (Project*)malloc(sizeof(Project));
    if (company->projects[company->projectCount] == NULL) {
        exit(FAILED_TO_ALLOCATE_PROJECT);
    }
    project = company->projects[company->projectCount];
    project->name = (char*)malloc((strlen(projectName) + 1) * sizeof(char));
    if (project->name == NULL) {
        exit(FAILED_TO_ALLOCATE_PROJECT_NAME_CODE);
    }
    strcpy(project->name, projectName);
    project->workers = (Worker**)malloc(sizeof(Worker*));
    if (project->workers == NULL) {
        exit(FAILED_TO_ALLOCATE_PROJECT_WORKERS_ARRAY_CODE);
    }
    project->workers[0] = worker;
    project->workerCount = 1;
    project->features = (FeatureNode*)malloc(sizeof(FeatureNode));
    if (project->features == NULL) {
        exit(FAILED_TO_ALLOCATE_PROJECT_FEATURES_CODE);
    }
    worker->projects = (Project**)realloc(worker->projects, (worker->projectCount + 1) * sizeof(Project*));
    if (worker->projects == NULL) {
        exit(FAILED_TO_REALLOCATE_WORKER_PROJECT_ARRAY_CODE);
    }
    worker->projects[worker->projectCount] = project;
    worker->projectCount++;
    company->projectCount++;
}
void freeWorker( Worker *worker ) {
    free( worker->name );
    for ( int i = 0; i < worker->projectCount; i++ )
        freeProject(worker->projects[i]);
}
void freeProject(Project *project) {
    free(project->name);
    return;
}
void printWorkers(Worker **workers, int numOfWorkers) {
    printf("Workers: [");
    for (int i = 0; i < numOfWorkers; i++) {
        printf("%s", workers[i]->name);
        if (i != numOfWorkers - 1) printf(", ");
    }
    printf("]\n");
}
void printProjects(Project **projects, int numOfProjects) {
    printf("Projects: [\n");
    for (int i = 0; i < numOfProjects; i++) {
        Project *project = projects[i];
        printf("\t{\n");
        printf("\t\tName: %s\n", project->name);
        printf("\t\tWorker count: %d\n", project->workerCount);
        printf("\t\t");
        printWorkers(project->workers, project->workerCount);
        printf("\t}");
        if (i != numOfProjects - 1) printf(",");
        printf("\n");
    }
    printf("]\n");
}
boolean isWorkerNameExists(Worker *workers[], int workerCount, const char *name) {
    for (int i = 0; i < workerCount; i++) {
        if (strcmp(workers[i]->name, name) == 0) return true;
    }
    return false;
}
boolean isProjectNameExists(Project *projects[], int projectCount, const char *name) {
    for (int i = 0; i < projectCount; i++) {
        if (strcmp(projects[i]->name, name) == 0) return true;
    }
    return false;
}
char *getChars(void) {
    int currentSize = 0;
    char c;
    char spaceEater; 
    char* string = NULL;
    scanf("%c", &spaceEater);
    while (scanf("%c", &c) == 1 && c != '\n') {
        string = (char*) realloc(string, (currentSize + 1) * sizeof(char));
        if (string == NULL) exit(FAILED_TO_ALLOCATE_STRING_CODE);
        string[currentSize] = c;
        currentSize++;
    }
    string = (char*) realloc(string, currentSize * sizeof(char));
    if (string == NULL) exit(FAILED_TO_ALLOCATE_STRING_CODE);
    string[currentSize] = '\0';
    return string;    
}