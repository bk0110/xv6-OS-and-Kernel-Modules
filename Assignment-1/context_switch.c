#include "types.h"
#include "user.h"
#include "date.h"

/*
User program to test the system call csinfo which finds the 
number of context switches of a process.
*/
int 
main(int agrc, char *argv[])
{
  int cs1,cs2,cs3,cs4;
  cs1 = csinfo();
  cs2 = csinfo();
  sleep(1);
  cs3 = csinfo();
  sleep(1);
  cs4 = csinfo();
  printf(1,"context switch counts = %d %d %d %d\n", cs1, cs2, cs3, cs4);
  exit();
}
