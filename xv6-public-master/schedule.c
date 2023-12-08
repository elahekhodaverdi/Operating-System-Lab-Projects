#include "types.h"
#include "user.h"

void help()
{
    printf(1, "usage: schedule command [arg...]\n");
    printf(1, "Commands and Arguments:\n");
    printf(1, "  info\n");
    printf(1, "  set_queue <pid> <new_queue>\n");
    printf(1, "  set_process_bjf <pid> <priority_ratio> <arrival_time_ratio> <executed_cycle_ratio> <process_size_ratio>\n");
    printf(1, "  set_system_bjf <priority_ratio> <arrival_time_ratio> <executed_cycle_ratio> <process_size_ratio>\n");
}

void print_info()
{
    print_process_info();
}

void set_queue(int pid, int new_queue)
{
    if (pid < 1)
    {
        printf(1, "Invalid pid\n");
        return;
    }
    if (new_queue < 1 || new_queue > 3)
    {
        printf(1, "Invalid queue\n");
        return;
    }
    int res = change_scheduling_queue(pid, new_queue);
    if (res < 0)
        printf(1, "Error changing queue\n");
    else
        printf(1, "Queue changed successfully\n");
}



void set_bjf_params(int pid, int priority_ratio, int arrival_time_ratio, int executed_cycle_ratio,int process_size_ratio, int system)
{
    if (priority_ratio < 0 || arrival_time_ratio < 0 || executed_cycle_ratio < 0 || process_size_ratio < 0)
    {
        printf(1, "Invalid ratios\n");
        return;
    }
    int res;
    if (system)
        res = set_bjf_params_system(priority_ratio, arrival_time_ratio, executed_cycle_ratio);
    else if (pid < 1)
    {
        printf(1, "Invalid pid\n");
        return;
    }
    else
        res = set_bjf_params_process(pid, priority_ratio, arrival_time_ratio, executed_cycle_ratio);
    
    if (res < 0)
        printf(1, "Error setting BJF params\n");
    else
        printf(1, "BJF params set successfully\n");
}

void wrong_command(){
    help();
    exit();
}
int main(int argc, char *argv[])
{
    if (argc < 2)
        wrong_command();

    if (!strcmp(argv[1], "info"))
        print_info();

    else if (!strcmp(argv[1], "set_queue"))
    {
        if (argc < 4)
            wrong_command();
        set_queue(atoi(argv[2]), atoi(argv[3]));
    }

    else if (!strcmp(argv[1], "set_process_bjf"))
    {
        if (argc < 7)
            wrong_command();
        set_bjf_params(atoi(argv[2]), atoi(argv[3]), atoi(argv[4]), atoi(argv[5]),atoi(argv[6]),1);
    }

    else if (!strcmp(argv[1], "set_system_bjf"))
    {
        if (argc < 6)
            wrong_command();
        set_bjf_params(0,atoi(argv[2]), atoi(argv[3]), atoi(argv[4]),atoi(argv[5]),0);
    }
    else
        help();

    exit();
}
