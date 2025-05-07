/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:05:41 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/07 21:35:59 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void init_philo(t_data *data)
{
    int i;
    
    data->philosophers = malloc(data->number_of_philosophers * sizeof(t_philosophers));
    if (!data->philosophers)
    {
        clean(data);
        exit(1);
    }
    data->val = malloc(4);
    if (!data->val)
    {
        clean(data);
        exit(1);
    }
    *data->val = 0;
    memset(data->philosophers, 0, data->number_of_philosophers * sizeof(t_philosophers));
    i = 0;
    while (i < data->number_of_philosophers)
    {
        data->philosophers[i].id= i;
        i++;
    }
}

void init_chopstick(t_data *data)
{
    int i;
    
    data->chopsticks = malloc(data->number_of_philosophers *sizeof(pthread_mutex_t));
    if (!data->chopsticks)
    {
        clean(data);
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

void take_chopstick(t_data *data)
{
    int i;

    i = 0;
    while (i < data->number_of_philosophers - 1)
    {
        data->philosophers->l_chopstick = &data->chopsticks[i];
        data->philosophers->r_chopstick = &data->chopsticks[i + 1];
        i++;
    }
    data->philosophers->l_chopstick = &data->chopsticks[i];
    data->philosophers->r_chopstick = &data->chopsticks[0];
}

void init_threads(t_data *data)
{
    int i;
    
    data->threads = malloc(data->number_of_philosophers * sizeof(pthread_t));
    if (!data->threads)
    {
        clean(data);
        exit(1);
    }
    memset(data->threads, 0, data->number_of_philosophers * sizeof(pthread_t ));
    i = -1;
    while (i++ < data->number_of_philosophers - 1)
        pthread_create(&data->threads[i], NULL,routine, (void *)data);
    i = -1;
    while (i++ < data->number_of_philosophers - 1)
        pthread_join(data->threads[i], NULL);
}
