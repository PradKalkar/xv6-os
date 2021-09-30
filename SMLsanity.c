#include "types.h"
#include "user.h"

int fibo(int n) {
	if(n <= 1) return 1;
	return fibo(n-1) + fibo(n-2);
}

int
main(int argc, char *argv[])
{
	if (argc != 2){
		printf(1, "Usage: SMLsanity <n>\n");
		exit();
 	}

	int n = atoi(argv[1]), j = 0, retime, rutime, stime, ctime;

	int avgRetime[3], avgRutime[3], avgStime[3];
	memset(avgRetime, 0, sizeof(avgRetime));
	memset(avgRutime, 0, sizeof(avgRutime));
	memset(avgStime, 0, sizeof(avgStime));

	for (int i = 0; i < 3 * n; i++) {
		j = i % 3;
		int pid = fork();
		if (pid == 0) {
			//child
			j = (getpid() - 4) % 3; // ensures independence from the first son's pid when gathering the results in the second part of the program
			#ifdef SML
				switch(j) {
					case 0:
						set_prio(1);
						break;
					case 1:
						set_prio(2);
						break;
					case 2:
						set_prio(3);
						break;
				}
			#endif
			for (int k = 0; k < 100; k++){
				for (j = 0; j < 1000000; j++){
					fibo(2);
				}
			}
			exit(); // children exit here
		}
		continue; // father continues to spawn the next child
	}
	for (int i = 0; i < 3 * n; i++) {
		int pid = wait2(&retime, &rutime, &stime, &ctime);
		int res = (pid - 4) % 3; // correlates to j in the dispatching loop
		switch(res) {
			case 0:
				printf(1, "Priority 1, pid: %d, ready: %d, running: %d, sleeping: %d, turnaround: %d, creation time: %d, end time: %d\n", pid, retime, rutime, stime, retime + rutime + stime, ctime, ctime + retime + rutime + stime);
				avgRetime[0] += retime;
				avgRutime[0] += rutime;
				avgStime[0] += stime;
				break;
			case 1:
				printf(1, "Priority 2, pid: %d, ready: %d, running: %d, sleeping: %d, turnaround: %d, creation time: %d, end time: %d\n", pid, retime, rutime, stime, retime + rutime + stime, ctime, ctime + retime + rutime + stime);
				avgRetime[1] += retime;
				avgRutime[1] += rutime;
				avgStime[1] += stime;
				break;
			case 2:
				printf(1, "Priority 3, pid: %d, ready: %d, running: %d, sleeping: %d, turnaround: %d, creation time: %d, end time: %d\n", pid, retime, rutime, stime, retime + rutime + stime, ctime, ctime + retime + rutime + stime);
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
		
  	printf(1, "\n\nPriority 1:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", avgRetime[0], avgRutime[0], avgStime[0], avgRetime[0] + avgRutime[0] + avgStime[0]);
	printf(1, "Priority 2:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", avgRetime[1], avgRutime[1], avgStime[1], avgRetime[1] + avgRutime[1] + avgStime[1]);
	printf(1, "Priority 3:\nAverage ready time: %d\nAverage running time: %d\nAverage sleeping time: %d\nAverage turnaround time: %d\n\n\n", avgRetime[2], avgRutime[2], avgStime[2], avgRetime[2] + avgRutime[2] + avgStime[2]);
	exit();
}