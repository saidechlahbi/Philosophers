/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:05:41 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/20 17:42:31 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philosophers *init_philo(t_data *data)
{
    int i;
    t_philosophers *philosophers;
    
    philosophers = malloc(data->number_of_philosophers * sizeof(t_philosophers));
    if (!philosophers)
    {
        free(data);
        exit(1);
    }
    memset(philosophers, 0, data->number_of_philosophers * sizeof(t_philosophers));
    i = 0;
    while (i < data->number_of_philosophers)
    {
        philosophers[i].id= i + 1;
        philosophers[i].data = data;
        i++;
    }
    return philosophers;
}

void init_chopstick(t_data *data)
{
    int i;
    
    data->chopsticks = malloc(data->number_of_philosophers *sizeof(pthread_mutex_t));
    if (!data->chopsticks)
    {
        free(data);
        exit(1);
    }
    memset(data->chopsticks, 0, data->number_of_philosophers * sizeof(pthread_mutex_t));
    i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_mutex_init(&data->chopsticks[i], NULL);
        i++;
    }
}

void take_chopstick(t_philosophers *philo,t_data *data)
{
    int i;

    i = 0;
    while (i < data->number_of_philosophers - 1)
    {
        philo[i].l_chopstick = &data->chopsticks[i];
        philo[i].r_chopstick = &data->chopsticks[i + 1];
        i++;
    }
    philo[i].l_chopstick = &data->chopsticks[i];
    philo[i].r_chopstick = &data->chopsticks[0];
}

int how_mush(t_philosophers *philo)
{
    int i;

    i = 0;
    while (i < philo->data->number_of_philosophers)
    {
        if (philo[i].nb_eat >= philo[i].data->number_of_times_each_philosopher_must_eat)
            i++;
        else
            return 0;        
    }
    printf("simulation stop\n");
    return 1;
}

void *monitor(void *philo)
{
    t_philosophers *philosophers;
    int number_philo;
    int i;

    philosophers = (t_philosophers *)philo;
    number_philo = philosophers->data->number_of_philosophers;
    while (1)
    {
        if (philosophers->data->number_of_times_each_philosopher_must_eat)
            if (how_mush(philo))
                exit(0);
        usleep(philosophers->data->time_to_die * 1000);
        i = 0;
        while (i < number_philo)
        {
            if (get_time() - philosophers[i].last_meal >= philosophers[i].data->time_to_die)
            {
                printf("%ld %ld %d\n", get_time() - philosophers[i].last_meal,
                 philosophers[i].last_meal , philosophers[i].data->time_to_die);
                printf("%ld  %d  died\n", get_time() - philosophers[i].data->start_time, philosophers[i].id);
                exit(1);
            }
            i++;
        }
        usleep(500);
    }
    return NULL;
}

void init_threads(t_philosophers *philo, t_data *data)
{
    int i;

    pthread_t monitoring;
    data->threads = malloc(data->number_of_philosophers * sizeof(pthread_t));
    if (!data->threads)
    {
        free(data);
        exit(1);
    }
    memset(data->threads, 0, data->number_of_philosophers * sizeof(pthread_t ));
    i = 0;
    philo->data->start_time = get_time();
    while (i < data->number_of_philosophers)
    {
        if(pthread_create(&data->threads[i], NULL,routine, (void *)(&philo[i])))
        clean(philo);
        i++;
    }
    if(pthread_create(&monitoring, NULL, monitor, (void *)philo))
        clean(philo);
    i = -1;
    while (i++ < data->number_of_philosophers - 1)
        if(pthread_join(data->threads[i], NULL))
            clean(philo);
    if(pthread_join(monitoring, NULL))
        clean(philo);
}
