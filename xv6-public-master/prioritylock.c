#include "types.h"
#include "defs.h"
#include "param.h"
#include "x86.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"
#include "spinlock.h"
#include "prioritylock.h"



void
initprioritylock(struct prioritylock *lk, char *name)
{
  initlock(&lk->lk, "priority lock");
  lk->name = name;
  lk->locked = 0;
  lk->pid = 0;
}

void
acquirepriority(struct prioritylock *lk)
{
  acquire(&lk->lk);
  while (lk->locked) {
    sleep(lk, &lk->lk);
  }
  lk->locked = 1;
  lk->pid = myproc()->pid;
  release(&lk->lk);
}

void
releasepriority(struct prioritylock *lk)
{
  if (myproc()->pid != lk->pid)
    panic("release");
    
  acquire(&lk->lk);
  lk->locked = 0;
  lk->pid = 0;
  wakeup2(lk);
  release(&lk->lk);
}

int
holdingpriority(struct prioritylock *lk)
{
  int r;
  acquire(&lk->lk);
  r = lk->locked && (lk->pid == myproc()->pid);
  release(&lk->lk);
  return r;
}


