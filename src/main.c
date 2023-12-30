// TODO: refarctor code
// TODO: save tasks in a better location
// TODO: allow for file input and output
// TODO: setup unit testing
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define COMMAND_LS "ls\t   List all tasks"
#define COMMAND_ADD "add\t   Add task"
#define COMMAND_RM "rm\t   Remove task"

typedef struct node {
    char* value;
    struct node* next;
} node;

typedef struct {
    int length;
    node* head;
    node* tail;
} tasks;

void helpUsage(char* name) {
    fprintf(stderr, "usage: %s [-h | help] <command> [<args>]\n", name);
}

void helpCommands() {
    fprintf(stderr, "   %s\n", COMMAND_LS);
    fprintf(stderr, "   %s\n", COMMAND_RM);
    fprintf(stderr, "   %s\n", COMMAND_ADD);
}

void addTask(tasks* t, char* task) {
    node* newTask = (node*)malloc(sizeof(node));
    newTask->value = task;
    t->length++;

    if (t->tail == NULL) {
        t->head = t->tail = newTask;
        return;
    }

    t->tail->next = newTask;
    t->tail = newTask;
    return;
}

void saveTask(char* task) {
    FILE* file;
    file = fopen("db.txt", "a");

    fprintf(file, "%s\n", task);

    fclose(file);
}

void loadTasks(tasks* t, char* input) {
    int idx = 0;
    FILE* file;
    char content[256];

    file = fopen(input, "r");
    if (file == NULL) {
        fprintf(stderr, "fatal: file not found\n");
        exit(1);
    }
    while (fgets(content, 256, file) != NULL) {
        printf("[%d] - %s", idx, content);
        addTask(t, content);
        idx++;
    }

    fclose(file);
}

node* getNode(tasks* t, int idx) {
    node* curr = t->head;
    if (idx > t->length) {
        fprintf(stderr, "fatal: task doesn't exist\n");
        exit(1);
    }

    for (int i = 0; i < idx; ++i) {
        curr = curr->next;
    }

    return curr;
}

void deleteTask(tasks* t, int idx) {
    if (idx == 0) {
        t->head = t->head->next;
        return;
    }

    if (idx == t->length) {
        t->tail = NULL;
        return;
    }

    node* curr = getNode(t, idx-1);
    curr->next = curr->next->next;
}

int main(int argc, char* argv[]) {
    tasks TaskList;
    TaskList.head = NULL;
    TaskList.tail = NULL;
    TaskList.length = 0;

    int opt;
    opterr = 0;
    while ((opt = getopt(argc, argv, "ho:")) != -1) {
        switch (opt) {
            case 'h':
                helpUsage(argv[0]);
                exit(0);
            case '?':
                fprintf(stderr, "unknown option: -%c\n", optopt);
                helpUsage(argv[0]);
                exit(1);
        }
    }

    if (argc < 2) {
        helpUsage(argv[0]);
        helpCommands();
        return 1;
    }
    printf("%d\n", TaskList.length);
    if (!strcmp(argv[1], "ls")) {
        loadTasks(&TaskList, "db.txt");
    } else if (!strcmp(argv[1], "rm")) {
        // TODO: fix this mess
        loadTasks(&TaskList, "db.txt");
        deleteTask(&TaskList, atoi(argv[2]));
    } else if (!strcmp(argv[1], "add")) {
        addTask(&TaskList, argv[2]);
        saveTask(argv[2]);
    } else {
        helpUsage(argv[0]);
        helpCommands();
        exit(1);
    }
    return 0;
}
