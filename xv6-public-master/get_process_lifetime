#include "types.h"
#include "stat.h"
#include "user.h"

int main(void) 
{
    int pid;
    pid = fork();
  
    if (pid < 0) {
        printf(1, "Fork failed\n");
        exit();
    } 
    else if (pid == 0) {
        sleep(1000);  
        printf(1, "Child process with PID: %d has lifetime: %d deciseconds\n",getpid(), get_process_lifetime());
        exit();
    } 
    else {
        wait(); 
        printf(1, "Parent process with PID: %d has lifetime: %d deciseconds\n",getpid(), get_process_lifetime());
        exit();
    }
}

