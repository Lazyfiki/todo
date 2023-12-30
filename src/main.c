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

void listTasks(tasks* t) {
    node* curr = t->head;
    for (int i = 0; i < t->length; ++i) {
        printf("%s\n", curr->value);
        curr = curr->next;
    }
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

    if (!strcmp(argv[1], "ls")) {
        printf("%s\n", TaskList.head->value);
        listTasks(&TaskList);
    } else if (!strcmp(argv[1], "rm")) {
        printf("%s command!\n", argv[1]);
    } else if (!strcmp(argv[1], "add")) {
        addTask(&TaskList, argv[2]);
    } else {
        helpUsage(argv[0]);
        helpCommands();
        exit(1);
    }
    return 0;
}
