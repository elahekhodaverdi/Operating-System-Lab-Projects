#include "types.h"
#include "user.h"
#include "fcntl.h"
#include "stat.h"

#define PROCS_NUM 5

int main()
{
    for (int i = 0; i < PROCS_NUM; ++i)
    {
        int pid = fork();
        if (pid == 0)
        {
            prioritylock_test();
        }
    }
    for (int i = 0; i < PROCS_NUM; i++)
        wait();
    exit();
}
