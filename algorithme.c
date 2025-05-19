/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:03:51 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/19 18:38:20 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void eating (t_philosophers *arg)
{
    printf("%ld  %d  is eating\n", get_time() - arg->data->start_time, arg->id);
    usleep(arg->data->time_to_eat * 1000);
    pthread_mutex_unlock(arg->r_chopstick);
    pthread_mutex_unlock(arg->l_chopstick);
}
void thinking(t_philosophers *arg)
{
    printf("%ld  %d  is thinking\n", get_time() - arg->data->start_time, arg->id);
    // usleep((arg->data->time_to_die - (arg->data->time_to_eat + arg->data->time_to_sleep)) * 1000);
}

void sleeping(t_philosophers *arg)
{
    printf("%ld  %d  is sleeping\n", get_time() - arg->data->start_time, arg->id);
    usleep(arg->data->time_to_sleep * 1000);
}
void *routine(void *arg)
{
    t_philosophers *data;

    data = (t_philosophers *)arg;
    if (data->id % 2)
        usleep(1000);
    while (1)
    {
        if (data->id % 2 == 0)
        {
            pthread_mutex_lock(data->l_chopstick);
            printf("%ld  %d has taken a fork\n",  get_time() - data->data->start_time, data->id);
            pthread_mutex_lock(data->r_chopstick);
            printf("%ld  %d has taken a fork\n",  get_time() - data->data->start_time, data->id);
        }else
        {
            pthread_mutex_lock(data->l_chopstick);
            printf("%ld  %d has taken a fork\n",  get_time() - data->data->start_time, data->id);
            pthread_mutex_lock(data->r_chopstick);
            printf("%ld  %d has taken a fork\n",  get_time() - data->data->start_time, data->id);
        }
        data->last_meal = get_time();
        eating(data);
        sleeping(data);
        thinking(data);
    }
    return data;
}
