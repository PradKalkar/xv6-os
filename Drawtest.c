#include "types.h"
#include "user.h"

int main(int argc, char *argv[]){
    // setting the max buf size for ascii art image
    const int max_buffer_size = 1000;

    // allocated a buffer with the specified max size
    char google_buffer[max_buffer_size];

    // invoked the draw() system call and stored the number of bytes copied in google_size
    int google_size = draw((void *)google_buffer, max_buffer_size);

    if (google_size == -1){
        // file descriptor 1 is used to print on the stdout
        printf(1, "Buffer size is too small\n");
        exit();
    }

    // file descriptor 1 is used to print on the stdout
    printf(1, "%s\n", (char *)google_buffer);

    // invoked the exit system call to exit from the program
    exit();
}