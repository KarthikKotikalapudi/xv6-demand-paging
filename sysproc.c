#include "types.h"
#include "x86.h"
#include "defs.h"
#include "date.h"
#include "param.h"
#include "memlayout.h"
#include "mmu.h"
#include "proc.h"

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

int
sys_date(struct rtcdate *r)
{
  if (argptr(0, (void*)&r, sizeof(*r)) < 0)
    return -1;
  cmostime(r);
  return 0;
}

int
sys_pgtPrint(void) {
  //page table directory
  pde_t *pgdir = myproc()->pgdir;
  //for entry numbers
  int entry_num = 0;
  //page table entry
  pte_t *pte;
  //virtual, physical address
  uint va = 0, pa;

  for (int i = 0; i < NPDENTRIES; i++) {
    if (!pgdir[i])
      continue;

    pte = (pte_t*)P2V(PTE_ADDR(pgdir[i]));

    for (int j = 0; j < NPTENTRIES; j++) {
      if (pte[j] & PTE_P && pte[j] & PTE_U) {
        pa = PTE_ADDR(pte[j]);
        cprintf("pgdir entry num: %d, Pgt entry num: %d, Virtual addr: 0x%x, Physical addr: 0x%x, W-bit: %x\n", i, entry_num, va, pa, (*pte & PTE_W)/2);
        entry_num++;
      }
      va += PGSIZE;
    }
  }

  return 0;
}