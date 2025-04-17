#include <pthread.h>
#include <stdio.h>

void *function()
{
    printf("curve\n");
    return NULL;
}
void *function2()
{
    printf("my curve is better than your curve\n");
}
int main ()
{
    // pthread_attr_t attr;
    pthread_t thread1;
    pthread_t thread2;
    pthread_create(&thread2, NULL, function2, NULL);
    pthread_create(&thread1, NULL, function,NULL);
    pthread_detach(thread1);
    pthread_detach(thread2);
    // pthread_join(thread2, NULL);
    // pthread_join(thread1, NULL);
    // pthread_create(pthread_t *thread, pthread_attr_t *attr, void * (function), void *data);
}