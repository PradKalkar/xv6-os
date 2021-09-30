#include "types.h"
#include "user.h"

int main(void)
{
    int retime, rutime, stime, pid;
    pid = fork();
    if (pid == 0){
        // in child 
        long long int sum = 0;

        for(long long i = 0; i < (long long) 1e9; i++){
            sum += i;
        }
        sleep(5);
        exit();
    }
    else{
        // inside parent
        // parent waits for child to finish
        pid = wait2(&retime, &rutime, &stime);
        printf(1, "pid:%d retime:%d rutime:%d stime:%d\n", pid, retime, rutime, stime);
    }
    
	exit();
}