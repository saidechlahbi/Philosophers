/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:05:41 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/28 10:58:36 by sechlahb         ###   ########.fr       */
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
        return NULL;
    }
    if (!memset(philosophers, 0, data->number_of_philosophers * sizeof(t_philosophers)))
    {
        free(data);
        free(philosophers);
        return NULL;
    }
    i = 0;
    while (i < data->number_of_philosophers)
    {
        philosophers[i].id= i + 1;
        philosophers[i].data = data;
        i++;
    }
    return philosophers;
}

t_data  *init_chopstick(t_data *data)
{
    int i;
    
    data->chopsticks = malloc(data->number_of_philosophers *sizeof(pthread_mutex_t));
    if (!data->chopsticks)
    {
        free(data);
        return NULL;
    }
    if (!memset(data->chopsticks, 0, data->number_of_philosophers * sizeof(pthread_mutex_t)))
    {
        free(data->chopsticks);
        free(data);
        return NULL;
    }
    i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_mutex_init(&data->chopsticks[i], NULL);
        i++;
    }
    pthread_mutex_init(&data->mutex_for_printf, NULL);
    return data;
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

void init_threads(t_philosophers *philo, t_data *data)
{
    int i;

    pthread_t monitoring;
    i = -1;
    philo->data->start_time = get_time();
    while (i++ < data->number_of_philosophers -1)
        if(pthread_create(&philo[i].thread, NULL,routine, (void *)(&philo[i])))
        {
            clean(philo);
            return;
        }
    if(pthread_create(&monitoring, NULL, monitor, (void *)philo))
    {
        clean(philo);
        return;
    }
    i = -1;
    while (i++ < data->number_of_philosophers - 1)
        if(pthread_join(philo[i].thread, NULL))
        {
            clean(philo);
            return;
        }
    if(pthread_join(monitoring, NULL))
    {
        clean(philo);
        return;
    }
}
