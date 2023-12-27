// Long-term locks for processes
struct prioritylock {
  uint locked;       // Is the lock held?
  struct spinlock lk; // spinlock protecting this sleep lock
  
  // For debugging:
  char *name;        // Name of lock.
  int pid;           // Process holding lock
  // int  num_queue_proc;
  // struct proc queue[NPROC];
};

