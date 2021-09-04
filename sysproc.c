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

// copies the ASCII art image of Google's logo to a user-supplied buffer
// if success return the number of byted copied else return -1
int
sys_draw(void)
{
  char* buffer;
  int size;

  // Fetch the 1st 32 bit call argument and assign it to the variable size i.e. the max-size of the buffer in bytes
  // Return -1 if an invalid address is accessed
  if (argint(1, &size) == -1){
    return -1;
  }

  // Fetch the 0th word-sized system call argument as a pointer
  // to a block of memory of size bytes. Check that the pointer
  // lies within the process address space if it does not then return -1.
  if (argptr(0, (char **)&buffer, size) == -1){
    return -1;
  }

  // ASCII art image of Google's logo
  char google[] = \
  "          ,((                                                                          \n"
  "      ((((((((((((((                                              ***                  \n"
  "    ((((                                                          ***                  \n"
  "  (((                      *//*          /((/          /((/      ***     *//*          \n"
  "  ((((       (((((((((  *//////////   ,((((((((((    (((((((((((  ***  //////////      \n"
  "  (((             ((( *//,      ///..(((      (((* (((      (((  *** ///  */////*      \n"
  "  *(((           /((( ///*      ///*(((/      ((((.(((      (((  *** //////            \n"
  "    ((((((   ((((((    ////.  *////  ((((/  *((((  ((((*   ((((  ***  ///*   ///*      \n"
  "        ((((((((          //////        ((((((        (((((.(((  ***    //////         \n"
  "                                                    (((     .(((                       \n"
  "                                                      ((((((((,                        \n";

  // finding the size of google_logo in bytes
  uint google_size = sizeof(google);

  // if the max-size of buffer is less than the google ascii art image size
  if (size < google_size){
    return -1;
  }           

  // copy the google logo to buf character by character
  int index = 0;
  while (google[index] != '\0'){
    buffer[index] = google[index];
    index++;
  }         
  buffer[index] = '\0';

  // returning the number of bytes copied i.e. size of the google logo
  return google_size;                                                        
}