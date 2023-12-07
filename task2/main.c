#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void handle_signal(int signo) {
    switch (signo) {
        case SIGINT:
            printf("Caught SIGINT signal\n");
            break;
        case SIGTERM:
            printf("Caught SIGTERM signal\n");
            break;
        case SIGUSR1:
            printf("Caught SIGUSR1 signal. Exiting...\n");
            exit(EXIT_SUCCESS);
        default:
            break;
    }
}

int main() {
    struct sigaction sa;

    sa.sa_handler = handle_signal;
    sa.sa_flags = 0;

    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);

    signal(SIGPROF, SIG_DFL);
    signal(SIGHUP, SIG_IGN);

    while (1) {
        pause();
    }

    return 0;
}
