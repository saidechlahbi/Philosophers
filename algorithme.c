/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:03:51 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/15 22:36:53 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// printf("%d  %d  died\n");

void eating (t_philosophers *arg)
{
    printf("%d  %d  is eating\n", arg->data->time_to_eat, arg->id);
    usleep(arg->data->time_to_eat * 1000);
    pthread_mutex_unlock(arg->r_chopstick);
    pthread_mutex_unlock(arg->l_chopstick);
}
void thinking(t_philosophers *arg)
{
    printf("%d  %d  is thinking\n", arg->data->time_to_eat, arg->id);
    // usleep((arg->data->time_to_die - (arg->data->time_to_eat + arg->data->time_to_sleep)) * 1000);
}

void sleeping(t_philosophers *arg)
{
    printf("%d  %d  is sleeping\n", arg->data->time_to_sleep, arg->id);
    usleep(arg->data->time_to_sleep * 1000);
}
void *routine(void *arg)
{
    t_philosophers *data;

    data = (t_philosophers *)arg;
    if (data->id % 2)
        usleep(1000);
    if (data->id % 2 == 0)
    {
        pthread_mutex_lock(data->l_chopstick);
        pthread_mutex_lock(data->r_chopstick);
    }else
    {
        pthread_mutex_lock(data->r_chopstick);
        pthread_mutex_lock(data->l_chopstick);
    }
    while (1)
    {
        
        eating(data);
        sleeping(data);
        thinking(data);
    }
    return data;
}
