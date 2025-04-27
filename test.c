#include <pthread.h>
#include <stdio.h>

// typedef struct s_philo
// {
//     pthread_t *philosophers;
//     pthread_mutex_t *forks;
    
// }t_philo;

typedef struct node 
{
    int a ;
    pthread_mutex_t key;
}philo;


void *routine(void *arg)
{
    int i = 0;
    while ( i++ < 100000)
    {
        pthread_mutex_lock(&(((philo *)arg)->key));
        ((philo *)arg)->a++;
        pthread_mutex_unlock(&(((philo *)arg)->key));
    }
    return arg;
}
int main ()
{
    philo philo;
    philo.a = 0;

    pthread_t thread1;
    pthread_t thread2;
    pthread_create(&thread1, NULL, routine, &philo);
    pthread_create(&thread2, NULL, routine, &philo);
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);
    printf("value of a %d\n", philo.a);
}