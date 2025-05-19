#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

// void *routine(void *data)
// {
//     *(int *)data +=1;
//     return NULL;
// }
// int main(int ac, char **av, char **env)
// {
//     pthread_t    thread;
    
//     int a = 7;
//     pthread_create(&thread,NULL, routine, (void *)&a);
//     // pthread_join(thread, NULL);
//     printf("%d\n", a);
//     printf("hello\n");
// }

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

void* worker_thread(void* arg) {
    printf("Worker thread starting...\n");
    // sleep(2);
    printf("Worker thread finishing...\n");
    return NULL;
}

int main() {
    pthread_t thread;
    
    // Create a new thread
   pthread_create(&thread, NULL, worker_thread, NULL);

    
    // Detach the thread
    // pthread_detach(thread);

    
    printf("Main thread: Worker thread has been detached\n");
    printf("Main thread: Main thread can exit without waiting\n");
    
    // Sleep briefly to allow seeing the worker thread output
    sleep(1);
    // printf("Main thread exiting...\n");
    
    return 0;
}