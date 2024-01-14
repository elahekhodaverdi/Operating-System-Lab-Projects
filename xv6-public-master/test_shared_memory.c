 
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define NCHILD 10

void test_open_sharedmem() {
  int shmid = 0; 
  void *addr = (void *)open_sharedmem(shmid); 
  if (addr == (void *)-1) {
    printf(1, "open_sharedmem failed\n");
    return;
  }

  printf(1, "Shared memory region with shmid %d attached at address %p\n", shmid, addr);
}

void test_close_sharedmem() {
  int shmid = 0; 
  void *addr = (void *)open_sharedmem(shmid); 

  if (close_sharedmem(addr) == -1) { 
    printf(1, "close_sharedmem failed\n");
    return;
  }

  printf(1, "Shared memory region detached\n");
}

void test_sharedmem_increment() {
  int shmid = 0; 
  void *addr = (void *)open_sharedmem(shmid); 

  for (int i = 0; i < NCHILD; i++) {
    int pid = fork();
    if (pid < 0) {
      printf(1, "fork failed\n");
      return;
    } else if (pid == 0) {

      (*(int *)addr)++;
      exit();
    }
  }

 
  for (int i = 0; i < NCHILD; i++) {
    wait();
  }

  printf(1, "Final value in shared memory: %d\n", *(int *)addr);
}

int main(void) {
  // test_open_sharedmem();
  // test_close_sharedmem();
  test_sharedmem_increment();


  exit();
}
