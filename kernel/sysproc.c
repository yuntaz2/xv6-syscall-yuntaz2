#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_exit(void)
{
  int n;
  if (argint(0, &n) < 0)
    return -1;
  exit(n);
  return 0; // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  if (argaddr(0, &p) < 0)
    return -1;
  return wait(p);
}

uint64
sys_sbrk(void)
{
  int addr;
  int n;

  if (argint(0, &n) < 0)
    return -1;
  addr = myproc()->sz;
  if (growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  if (argint(0, &n) < 0)
    return -1;
  acquire(&tickslock);
  ticks0 = ticks;
  while (ticks - ticks0 < n)
  {
    if (myproc()->killed)
    {
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  if (argint(0, &pid) < 0)
    return -1;
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}

// argint and argaddr get arguments from user space to the kernel space
uint64
sys_pidguess(void)
{
  // remember, the function will exec in kernel space and parameter is from user space.
  int guess;
  if (argint(0, &guess) < 0)
  {
    // the function is called incorrectly
    return -1;
  }
  if (myproc()->pid == guess)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

// lab-2 activity-1: add a sys_trace() function
uint64
sys_trace(void)
{
  int mask; // remember its arg in a new var in the proc structure in proc.h
  argint(0, &mask);
  if (mask < 0 || mask > 2147483647)
  {
    printf("Input mask value in invalid.\n");
    return -1; // illegal mask value
  }
  struct proc *currProc = myproc(); // Not sure if it is necessary as it is also in syscall.c
  if (currProc)
  {
    currProc->mask = mask;
  }
  // printf("sys_trace is called with arg %d\n", mask);
  else
    printf("No current process");
  return 0;
}
