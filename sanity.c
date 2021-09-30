#include "types.h"
#include "user.h"
#include <stdbool.h>

// 1 second == 100 ticks //

int fibo(int n) {
	if(n <= 1) return 1;
	return fibo(n-1) + fibo(n-2);
}

int
main(int argc, char *argv[])
{
	if (argc != 2){
		printf(1, "Usage: sanity <n>\n");
		exit();
 	}

	int n = atoi(argv[1]), j = 0;
	int retime, rutime, stime;
	int ctime;

	int avgRetime[3], avgRutime[3], avgStime[3];
	memset(avgRetime, 0, sizeof(avgRetime));
	memset(avgRutime, 0, sizeof(avgRutime));
	memset(avgStime, 0, sizeof(avgStime));

	int pid;
	for (int i = 0; i < 3 * n; i++) {
		j = i % 3;
		pid = fork();
		if (pid == 0) {
            // child
            // parent process has pid 3
			j = (getpid() - 4) % 3; // ensures independence from the first son's pid when gathering the results in the second part of the program
			switch(j) {
				case 0:
				// 1000000
                    //CPU‐bound process (CPU):
					for (int k = 0; k < 100; k++){
						for (j = 0; j < 1000000; j++){
							fibo(2);
						}
					}
					break;
				case 1:
                    // short tasks based CPU‐bound process (S‐CPU):
					for (int k = 0; k < 100; k++){
						for (j = 0; j < 1000000; j++){
                            fibo(2);
                        }
						yield();
					}
					break;
				case 2:
                    // simulate I/O bound process (IO)
					for(int k = 0; k < 100; k++){
						sleep(1);
					}
					break;
			}
			exit(); // children exit here
		}
		
		// parent continues to spawn the next child
	}

	for (int i = 0; i < 3 * n; i++) {
		pid = wait2(&retime, &rutime, &stime, &ctime);
		int res = (pid - 4) % 3; // correlates to j in the dispatching loop
		switch(res) {
			case 0: 
                // CPU bound processes
				printf(1, "CPU-bound, pid: %d, ready: %d, running: %d, sleeping: %d, turnaround: %d, creation time: %d, end time: %d\n", pid, retime, rutime, stime, retime + rutime + stime, ctime, ctime + retime + rutime + stime);
				avgRetime[0] += retime;
				avgRutime[0] += rutime;
				avgStime[0] += stime;
				break;
			case 1: 
                // CPU bound processes, short tasks
				printf(1, "CPU-S bound, pid: %d, ready: %d, running: %d, sleeping: %d, turnaround: %d, creation time: %d, end time: %d\n", pid, retime, rutime, stime, retime + rutime + stime, ctime, ctime + retime + rutime + stime);
				avgRetime[1] += retime;
				avgRutime[1] += rutime;
				avgStime[1] += stime;
				break;
			case 2: 
                // simulating I/O bound processes
				printf(1, "I/O bound, pid: %d, ready: %d, running: %d, sleeping: %d, turnaround: %d, creation time: %d, end time: %d\n", pid, retime, rutime, stime, retime + rutime + stime, ctime, ctime + retime + rutime + stime);
				avgRetime[2] += retime;
				avgRutime[2] += rutime;
				avgStime[2] += stime;
				break;
		}
	}

	for (int i = 0; i < 3; i++){
		avgRetime[i] /= n;
		avgRutime[i] /= n;
		avgStime[i] /= n;
	}

	printf(1, "\n\nCPU bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", avgRetime[0], avgRutime[0], avgStime[0], avgRetime[0] + avgRutime[0] + avgStime[0]);
	printf(1, "CPU-S bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", avgRetime[1], avgRutime[1], avgStime[1], avgRetime[1] + avgRutime[1] + avgStime[1]);
	printf(1, "I/O bound:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", avgRetime[2], avgRutime[2], avgStime[2], avgRetime[2] + avgRutime[2] + avgStime[2]);
	exit();
}