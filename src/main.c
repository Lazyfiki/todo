#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define COMMAND_LS "ls \t List all tasks"
#define COMMAND_ADD "add \t Add task"
#define COMMAND_RM "rm \t Remove task"


void helpUsage() {
    fprintf(stderr, "usage: %s [-h | help] <command> [<args>]\n", "todo");
}

void helpCommands() {
    fprintf(stderr, "   %s \n", COMMAND_LS);
    fprintf(stderr, "   %s \n", COMMAND_RM);
    fprintf(stderr, "   %s \n", COMMAND_ADD);
}

int main(int argc, char* argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "ho:")) != -1) {
        switch (opt) {
            case 'h':
                helpUsage();
                exit(0);
            case '?':
                fprintf(stderr, "unknown option: -%c\n", optopt);
                helpUsage();
                exit(1);
        }
    }
    if (argc < 2) {
        helpUsage();
        helpCommands();
        return 1;
    }
    printf("%s command!\n", argv[1]);
    return 0;
}
