#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "mp.h"

int
sys_fork(void)
{
  return fork();
}

int
sys_exit(void)
{
  exit();
  return 0;  // not reached
}

int
sys_wait(void)
{
  return wait();
}

int
sys_kill(void)
{
  int pid;

  if(argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

int
sys_getpid(void)
{
  return myproc()->pid;
}

int
sys_sbrk(void)
{
  int addr;
  int n;

  if(argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

int
sys_sleep(void)
{
  int n;
  uint ticks0;

  if(argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(myproc()->killed){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

// return how many clock tick interrupts have occurred
// since start.
int
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

int sys_find_digital_root(void)
{
  int number = myproc()->tf->ebx;
  cprintf("KERNEL: sys_find_digital_root() is called for n = %d\n", number);
  return find_digital_root(number);
}


int
sys_get_uncle_count(void)
{
  int child_count = get_child_count();
  return child_count-1;
}

int sys_get_process_lifetime(void) {
  return get_process_lifetime();
}

int
sys_change_scheduling_queue(void)
{
  int queue_number, pid;
  if(argint(0, &pid) < 0 || argint(1, &queue_number) < 0)
    return -1;

  if(queue_number < ROUND_ROBIN || queue_number > BJF)
    return -1;

  return change_queue(pid, queue_number);
}

void sys_print_processes_info(void) {
  print_processes_info();
}

int
sys_set_proc_bjf_params(void)
{
  int pid;
  float priority_ratio, arrival_time_ratio, executed_cycle_ratio, process_size_ratio;
  if(argint(0, &pid) < 0 ||
     argfloat(1, &priority_ratio) < 0 ||
     argfloat(2, &arrival_time_ratio) < 0 ||
     argfloat(3, &executed_cycle_ratio) < 0||
     argfloat(4, &process_size_ratio)<0 ){
    return -1;
  }

  return set_proc_bjf_params(pid, priority_ratio, arrival_time_ratio, executed_cycle_ratio,process_size_ratio);
}

int
sys_set_system_bjf_params(void)
{
  int pid;
  float priority_ratio, arrival_time_ratio, executed_cycle_ratio,process_size_ratio;
  if(argint(0, &pid) < 0 ||
     argfloat(1, &priority_ratio) < 0 ||
     argfloat(2, &arrival_time_ratio) < 0 ||
     argfloat(3, &executed_cycle_ratio) < 0||
     argfloat(4,&process_size_ratio)<0){
    return -1;
  }

  set_system_bjf_params(priority_ratio, arrival_time_ratio, executed_cycle_ratio,process_size_ratio);
  return 0;
}

void sys_prioritylock_test(void){
    prioritylock_test();
}



int sys_getsyscallcount(void)
{
  int i, total = 0;
  for (i = 0; i < ncpu; i++) {
    int count = syscallcount(i);
    if(count >= 0) {
      cprintf("System call count for %d-th core: %d\n", i, count);
      total += count;
    }
  }
  cprintf("total syscall count: %d\n", total);
  cprintf("shared syscall count: %d\n", shared_syscallcount);
  return total;
}


extern int close_sharedmem(void*);
extern void * open_sharedmem(int);

int sys_close_sharedmem(void)
{
  int i;
  if(argint(0,&i)<0)
    return 0;
  return close_sharedmem((void*)i);
}

void*
sys_open_sharedmem(void)
{
  int shmid;
  if(argint(0, &shmid) < 0)
    return (void*)0;

  return open_sharedmem(shmid);
}
