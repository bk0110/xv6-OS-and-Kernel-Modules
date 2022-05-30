#include "types.h"
#include "user.h"
#include "date.h"

/*
User program to test the system call memtop which tells the amount of 
free memory available in the system.
*/

int 
main(int argc, char *argv[])
{
  printf(1,"available memory: %d\n", memtop());
  exit(); 
}
