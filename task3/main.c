#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

char *alarm_message;

void alarm_handler(int signo) {
    printf("%s\n", alarm_message);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <interval_seconds> <message>\n", argv[0]);
        return 1;
    }

    int interval = atoi(argv[1]);
    alarm_message = argv[2];

    signal(SIGALRM, alarm_handler);

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        return 1;
    } else if (child_pid == 0) {
        alarm(interval);
        pause();
        exit(0);
    } else {
        waitpid(child_pid, NULL, 0);
    }

    return 0;
}

