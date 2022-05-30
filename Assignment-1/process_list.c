#include "types.h"
#include "user.h"
#include "date.h"

/*
User program to test the system call ps which prints the currently running processes.
*/
int 
main(int argc, char *argv[])
{
  ps();
  exit(); 
}
