#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

static void sighandler(int signo)
{
    if (signo == SIGINT)
    {
        printf("\nSIGINT received\nExiting...\n\n");
        int file = open("signal.out", O_CREAT | O_WRONLY, 0644); 
        if (file == -1) 
        {
            printf("errno: %d\terror: %s\n", errno, strerror(errno));
        }

        char msg [21]= "Exited due to SIGINT\n";
        lseek(file, 0, SEEK_END);
        int k = write(file, msg, sizeof(msg));

        if (k == -1)
        {
            printf("errno: %d\terror: %s\n", errno, strerror(errno));
        }
        close(file);
        exit(0);

    }
    if (signo == SIGUSR1)
    {
        printf("\nSIGUSR1 received\nPPID: %d\n\n", getppid());
    } 
}

int main() 
{
    signal(SIGINT, sighandler);
    signal(SIGUSR1, sighandler);
    while(1)
    {
        printf("PID: %d\n", getpid());
        sleep(1);
    }
}