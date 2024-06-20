#include "types.h"
#include "stat.h"
#include "user.h"


int main() {
    int child1, child2, child3;
    int grandchild;

    child1 = fork();
    if (child1 == 0) {
        printf(1, "Child 1 forked successfully (PID: %d)\n", getpid());
        sleep(100);
        grandchild = fork();
        if (grandchild == 0) {
            printf(1, "Grandchild process forked successfully (PID: %d)\n", getpid());
            int uncle_count = get_uncle_count();
            printf(1, "Uncle count: %d\n", uncle_count);
            exit();
        }
        wait();
        exit();
    }

    child2 = fork();
    if (child2 == 0) {
        printf(1, "Child 2 process forked successfully (PID: %d)\n", getpid());
        sleep(200);
        exit();
    }

    child3 = fork();
    if (child3 == 0) {
        printf(1, "Child 3 process forked successfully (PID: %d)\n", getpid());
        sleep(300);
        exit();
    }

    wait();
    wait();
    wait();

    exit();
}
