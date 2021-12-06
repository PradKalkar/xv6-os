#include "types.h"
#include "user.h"

#define PAGE_SIZE 4096
#define NUM_ITER 20
#define NUM_CHILD 20

void Child_Function(int i) {
    char *ptr[NUM_ITER];
    
    // Allocates 4KB pages to each of the char pointer
    for(int j = 0; j < NUM_ITER; j++){
        ptr[j] = (char *)malloc(PAGE_SIZE);
    }
    
    // Assign values to the allocated memory
    for (int j = 0; j < NUM_ITER; j++) {
        for (int k = 0; k < PAGE_SIZE; k++){
            ptr[j][k] = (i * j * k) % 128;
        }
    }
    
    // Error detection
    for (int j=0; j < NUM_ITER; j++) {
        for (int k=0; k < PAGE_SIZE; k++) {
            if (ptr[j][k] != (i * j * k) % 128){
                printf(1, "Error at i = %d, j = %d, k = %d, val = %c\n", i, j, k, ptr[j][k]);
            }       
        }
    }
        
    exit();
}

int main(int argc, char *argv[])
{    
    printf(1, "--------------------------------------------------------------------------------------------\n");
    printf(1, "|           Event           | PID | VA |                      Remark                       |\n");
    printf(1, "--------------------------------------------------------------------------------------------\n");

    for (int i = 1; i <= NUM_CHILD; i++){
        if (!fork()) {
            Child_Function(i);
        }
    }
    
    for (int i = 1; i <= NUM_CHILD; i++){
        wait();
    }
    
    exit();
}