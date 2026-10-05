#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    char *line = NULL;
    size_t len = 0;
    ssize_t nread;

    while (1) {
        printf("shellforge$ ");
        fflush(stdout);

        nread = getline(&line, &len, stdin);

        if (nread == -1) {
            printf("\nExiting cleanly...\n");
            break;
        }

        if (nread > 0 && line[nread - 1] == '\n') {
            line[nread - 1] = '\0';
        }

        if (strcmp(line, "exit") == 0) {
            break;
        }

        if (strlen(line) == 0) {
            continue;
        }

        char *args[64];
        int i = 0;

        char *token = strtok(line, " ");

        while (token != NULL && i < 63) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }

        args[i] = NULL;
        pid_t pid = fork();

if (pid == 0) {
    execvp(args[0], args);
    perror("ShellForge");
    exit(1);
}
else if (pid > 0) {
    wait(NULL);
}
else {
    perror("fork");
}
    }

    free(line);
    return 0;
}
