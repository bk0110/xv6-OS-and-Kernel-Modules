#include "types.h"
#include "user.h"
#include "date.h"

// A simple function to consume CPU time.
void 
consumeCPUtime(void){
  double x = 125.0;
  x = x+ 3.14*9.04;
}

int 
main(int argc, char *argv[])
{
  // Check if correct no. of arguments passed.
  if(argc<2){
    printf(1,"Invalid no. of arguments. Found no. of arguments = %d\n", argc);
    exit();
  }
  
  // Find no. of processes passed as argument.
  int numProcesses = atoi(argv[1]);
  
  // Check if no. of processes are greater than 5.
  if(numProcesses <= 5){
    printf(1,"Expected a no. greater than 5, found %d\n", numProcesses);
    exit();
  }
  int i, pid;
  int runtime, sleeptime, readytime;
  int avg_runtime[3], avg_sleeptime[3], avg_readytime[3], n[3];
  
  // Create child processes
  for(i=0; i<numProcesses; i++){
    pid = fork();
    if( pid == 0){
	    int temp = getpid()%3;
	    // Change priority of processes so that processes of all priority are present.
	    if(temp == 0){
	      chpr(getpid(),1);
	    }
	    else if(temp == 1){
	      chpr(getpid(),2);
	    }
	    else{
	      chpr(getpid(),3);
	    }
	    for(double j=0; j<10000000; j++){
  				consumeCPUtime();
  		}
	    exit();
	    
    }
    continue;
  }
  
  // Print statistics for each process.
  printf(1,"Printing statistics for each process --------\n");
  printf(1,"PID | Priority | Ready time | Run time | Sleep time | Turnaround time\n");
  for(i=0; i<numProcesses; i++){
    pid = waitstat(&readytime, &runtime, &sleeptime);  
    int temp = pid%3;
    n[temp]++;
    printf(1,"%d   | %d        | %d         | %d         | %d          | %d\n",pid, temp+1,readytime, runtime, sleeptime, readytime+runtime+sleeptime);
    avg_runtime[temp] += runtime;
    avg_sleeptime[temp] += sleeptime;
    avg_readytime[temp] += readytime;
  }
  
  // Print average statistics
  printf(1,"\nPrinting Average Statistics -------\n");
  printf(1,"Priority  | Avg Ready time | Avg Run time | Avg Sleep time | Avg turnaround time\n"); 
  for(i=0; i<3; i++){
  	printf(1,"%d       | %d             | %d            | %d             | %d\n",i+1,avg_readytime[i]/n[i], avg_runtime[i]/n[i], avg_sleeptime[i]/n[i], (avg_readytime[i]+avg_runtime[i]+avg_sleeptime[i])/n[i]);
  }
  printf(1,"\n");
  printf(1,"For all process with MLQ scheduling policy\n");
  printf(1,"Average ready time = %d\n",(avg_readytime[0]+avg_readytime[1]+avg_readytime[2])/numProcesses);
  printf(1,"Average run time = %d\n",(avg_runtime[0]+avg_runtime[1]+avg_runtime[2])/numProcesses);
  printf(1,"Average sleep time = %d\n",(avg_sleeptime[0]+avg_sleeptime[1]+avg_sleeptime[2])/numProcesses);
  printf(1,"Average turnaround time = %d\n",(avg_readytime[0]+avg_readytime[1]+avg_readytime[2]+avg_runtime[0]+avg_runtime[1]+avg_runtime[2]+avg_sleeptime[0]+avg_sleeptime[1]+avg_sleeptime[2])/numProcesses);
  
  exit();
}
