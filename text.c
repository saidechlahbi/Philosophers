# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>



typedef struct s_data
{
	long			start_time;
	pthread_mutex_t	*chopsticks;
	int				number_of_philosophers;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_of_t_e_p_m_e;
}					t_data;

typedef struct s_philosophers
{
	int				id;
	pthread_t		thread;
	long			last_meal;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	t_data			*data;
}					t_philosophers;


void    *ft_handler(void *data)
{
    t_philosophers *philo = (t_philosophers *)data;
    printf("I am philo number %d\n", philo->id);
    return NULL;
}

int main()
{
    t_data data;
    data.number_of_philosophers = 10;
    data.time_to_die = 100;
    data.time_to_eat = 20;
    data.time_to_sleep = 200;
    pthread_mutex_t mutex[10];
    data.chopsticks = &mutex;

    t_philosophers philo[10];

    for (int i = 0; i < 10 ; i++)
    {
        philo[i].id = i;
        philo[i].data = &data;
    }
    for (int i = 0; i < 10; i++)
    {
        philo[i].r_fork = &mutex[i];
        if (i != 9)
            philo[i].l_fork = &mutex[i + 1];
        else
            philo[i].l_fork = &mutex[0];
    }
    for (int j = 0; j < 10; j++)
    {
        pthread_create(&(philo[j].thread), NULL, ft_handler, &philo[j]); 
    }
    for (int i = 0; i < 10 ; i++)
    {
        pthread_join(philo[i].thread, NULL);
    }
}

