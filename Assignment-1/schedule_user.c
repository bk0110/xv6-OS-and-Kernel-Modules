#include "types.h"
#include "user.h"
#include "date.h"

// A simple function to consume CPU time.
void 
consumeCPUtime(void){
  for (double i = 0; i < 10000; i++){
    double x = 125.0;
    x = x+ 3.14*9.04;
  }
}
int 
main(int argc, char* argv[])
{
	
	// Check if correct no. of arguments passed.
	if(argc!=2){
    printf(1,"Invalid no. of arguments. Expected 2 arguments, found = %d\n", argc);
    exit();
  }
  
  // Find no. of processes passed as argument.
  int numProcesses = atoi(argv[1]);
  
  // Check if no. of processes are greater than 5.
  if(numProcesses <= 5){
    printf(1,"Expected a no. greater than 5, found %d\n", numProcesses);
    exit();
  }
  
  int pid;
  int runtime, sleeptime, readytime;
  int avg_runtime[3], avg_sleeptime[3], avg_readytime[3], n[3];
  for(int i=0; i<3; i++){
    avg_runtime[i] = 0;
    avg_sleeptime[i] = 0;
    avg_readytime[i] = 0;
    n[i] = 0;
  }
  
  //Create child processes
  for(int i=0; i<numProcesses; i++){
  	pid = fork();
  	
  	if(!pid){
  		int temp = getpid()%3;
  		
  		// CPU bound process
  		if(temp == 0){
  			for(int j=0; j<100000; j++){
  				consumeCPUtime();
  			}
  		}
  		
  		// Short tasks based on CPU bound process
  		else if(temp == 1){
  			for(int j=0; j<100; j++){
  				for(int k=0; k<100000; k++){
  				}
  				yield();
  			}
  		}
  		
  		// IO bound process
  		else{
  			for(int j=0; j<1000; j++){
  				sleep(1);
  			}
  		}
  		
  		exit();
  	}
  	continue;
  }
  
  printf(1,"Printing statistics for each process --------\n");
  printf(1,"PID | Type | Ready time | Run time | Sleep time | Turnaround time\n");
  // Wait for termination of all child processes
  for(int i=0; i<numProcesses; i++){
  	pid = waitstat(&readytime, &runtime, &sleeptime);
  	
  	// Print statistics of each process
  	int temp = pid%3;
  	if(temp == 0){
  		printf(1,"%d   | CPU  | %d         | %d         | %d          | %d\n",pid, readytime, runtime, sleeptime, readytime+runtime+sleeptime);
  	}
		else if(temp == 1){
			printf(1,"%d   | S-CPU| %d         | %d         | %d          | %d\n",pid, readytime, runtime, sleeptime, readytime+runtime+sleeptime);
		}
		else{
			printf(1,"%d   | IO   | %d         | %d         | %d          | %d\n",pid, readytime, runtime, sleeptime, readytime+runtime+sleeptime);
  	}
  	
  	avg_runtime[temp] += runtime;
    avg_sleeptime[temp] += sleeptime;
    avg_readytime[temp] += readytime;
    n[temp]++;
  }
  printf(1,"\n");
  
  // Print average statistics
  printf(1,"Printing Average Statistics -------\n");
  printf(1,"Type  | Avg Ready time | Avg Run time | Avg Sleep time | Avg turnaround time\n"); 
  printf(1,"CPU   | %d             | %d            | %d             | %d\n",avg_readytime[0]/n[0], avg_runtime[0]/n[0], avg_sleeptime[0]/n[0], (avg_readytime[0]+avg_runtime[0]+avg_sleeptime[0])/n[0]);
  printf(1,"S-CPU | %d             | %d            | %d             | %d\n",avg_readytime[1]/n[1], avg_runtime[1]/n[1], avg_sleeptime[1]/n[1], (avg_readytime[1]+avg_runtime[1]+avg_sleeptime[1])/n[1]);
  printf(1,"IO    | %d             | %d            | %d             | %d\n",avg_readytime[2]/n[2], avg_runtime[2]/n[2], avg_sleeptime[2]/n[2], (avg_readytime[2]+avg_runtime[2]+avg_sleeptime[2])/n[2]);
  
  exit();
}
