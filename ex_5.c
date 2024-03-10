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

    freeWorkers(company.workers, company.workerCount);
    company.workers = NULL;
    freeProjects(company.projects, company.projectCount);
    company.projects = NULL;

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
    scanf("%d", &selectedOption);

    if (selectedOption > 8 || selectedOption < 1 ) {
        printf( "Invalid choice. Please try again." );
        return menu(company);
    }
    if (selectedOption == FIRST_OPTION) {
        firstOption(company);
    }
    if (selectedOption == SECOND_OPTION) {
        secondOption(company);
    }
    if (selectedOption == THIRD_OPTION) {
        thirdOption(company);
    }
    if (selectedOption == FOURTH_OPTION) {
        fourthOption(company);
    }
    if (selectedOption == FIFTH_OPTION) {
        fifthOption(company);
    }
    if (selectedOption == EIGHTH_OPTION) {
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
    strcpy(worker->name, workerName);
    free(workerName);
    worker->projectCount = 0;
    worker->projects = NULL;
    company->workerCount++;
}
void secondOption(Company *company) {
    char *projectName = NULL;
    Worker *worker = NULL;
    Project *project = NULL;
    if (company->workerCount == 0) {
        printf("There are no workers in the company yet, please join the company first.\n");
        return;
    }
    printf("Who are you? Choose a number:\n");
    worker = selectWorkerByIndex(company->workers, company->workerCount, "Enter your choice: ");
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
    project->features = NULL; 
    worker->projects = (Project**)realloc(worker->projects, (worker->projectCount + 1) * sizeof(Project*));
    if (worker->projects == NULL) {
        exit(FAILED_TO_REALLOCATE_WORKER_PROJECT_ARRAY_CODE);
    }
    free(projectName);
    worker->projects[worker->projectCount] = project;
    worker->projectCount++;
    company->projectCount++;
}
void thirdOption(Company *company) {
    Worker *worker = NULL;
    Project *project = NULL;

    if (company->workerCount == 0) {
        printf("There are no workers in the company yet, please join the company first.\n");
        return;
    }
    if (company->projectCount == 0) {
        printf("There are no projects in the company yet, please create one first.\n");
        return;
    }
    printf("Select a worker to join a project:\n");
    worker = selectWorkerByIndex(company->workers, company->workerCount, "Enter the worker's number: ");
    project = selectProjectByIndex(company->projects, company->projectCount, "Enter the project's number: ");
    if (isWorkerInProject(project, worker)) {
        printf("This worker is already part of the project '%s'.\n", project->name);
        return;
    }
    if (project->workerCount >= 4) {
        printf("Project is full.\n");
        return;
    }
    project->workers = (Worker**)realloc(
        project->workers,
        (project->workerCount + 1) * sizeof(Worker*)
    );
    project->workers[project->workerCount] = worker;
    project->workerCount++;

    worker->projects = (Project**)realloc(
        worker->projects,
        (worker->projectCount + 1) * sizeof(Project*)
    );
    worker->projects[worker->projectCount] = project;
    worker->projectCount++;
}
void fourthOption(Company *company) {
    Worker *worker = NULL;
    Project *project = NULL;
    FeatureNode *feature = NULL;

    if (company->projectCount == 0) {
        printf("There are no projects to display.\n");
        return;
    }
    for (int i = 0; i < company->projectCount; i++) {
        project = company->projects[i];
        printf("Project: %s\n", project->name);
        printf("  Workers in this project:\n");
        if (project->workerCount == 0) printf("    None\n");
        else {
            for (int j = 0; j < project->workerCount; j++) {
                worker = project->workers[j];
                printf("    - %s\n", worker->name);
            }
        }
        printf("  Features of the project:\n");
        if (project->features == NULL) printf("    No features\n");
        else {
            feature = project->features;
            while (feature != NULL) {
                printf("    - %s\n", feature->feature);
                feature = feature->next;
            }
        }
    }
    printf("\n");
}
void fifthOption(Company *company) {
    Worker *worker = NULL;
    Project *project = NULL;

    if (company->workerCount == 0) {
        printf("There are no workers to display.\n");
        return;
    }
    for (int i = 0; i < company->workerCount; i++) {
        worker = company->workers[i];
        printf("Worker: %s\n", worker->name);
        if (worker->projectCount == 0) {
            printf("  Not involved in any projects.\n");
            continue;
        }
        printf("  Projects this worker is involved in:\n");
        for (int j = 0; j < worker->projectCount; j++) {
            project = worker->projects[j];
            printf("    - %s\n", project->name);
        }
    }
    printf("\n");
}
void freeWorkers(Worker **workers, int workerCount) {
    if (workers == NULL) return;
    for (int i = 0; i < workerCount; i++) {
        if (workers[i] != NULL) freeWorker(workers[i]);
        workers[i] = NULL;
    }
    free(workers);
}
void freeWorker(Worker *worker) {
    free(worker->name);
    free(worker->projects);
    free(worker);
}
void freeProjects(Project **projects, int projectCount) {
    if (projects == NULL) return;
    for (int i = 0; i < projectCount; i++) {
        if (projects[i] != NULL) freeProject(projects[i]);
        projects[i] = NULL;
    }
    free(projects);
}
void freeProject(Project *project) {
    free(project->name);
    free(project->workers);
    freeFeatures(project->features);
    free(project);
}
void freeFeatures(FeatureNode *head) {
    if (head == NULL) return;
    freeFeatures(head->next);
    free(head->feature);
    free(head->next);
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
    string = (char*) realloc(string, (currentSize + 1) * sizeof(char));
    if (string == NULL) exit(FAILED_TO_ALLOCATE_STRING_CODE);
    string[currentSize] = '\0';
    return string;
}
Worker *selectWorkerByIndex(Worker **workers, int workerCount, char *message) {
    int chosenWorkerIndex;
    for (int i = 0; i < workerCount; i++) {
        printf("%d. %s\n", i+1, workers[i]->name);
    }
    printf("%s", message);
    scanf("%d", &chosenWorkerIndex);
    chosenWorkerIndex--;
    if (chosenWorkerIndex > workerCount || chosenWorkerIndex < 0) {
        printf("Invalid worker selection.\n");
        return NULL;
    }

    return workers[chosenWorkerIndex];
}
Project *selectProjectByIndex(Project **projects, int projectCount, char *message) {
    int chosenProjectIndex;
    for (int i = 0; i < projectCount; i++) {
        printf("%d. %s\n", i+1, projects[i]->name);
    }
    printf("%s", message);
    scanf("%d", &chosenProjectIndex);
    chosenProjectIndex--;
    if (chosenProjectIndex > projectCount || chosenProjectIndex < 0) {
        printf("Invalid worker selection.\n");
        return NULL;
    }
    return projects[chosenProjectIndex];
}
boolean isWorkerInProject(Project *project, Worker *worker) {
    for (int i = 0; i < project->workerCount; i++) {
        if (strcmp(project->workers[i]->name, worker->name) == 0) return true;
    }
    return false;
}