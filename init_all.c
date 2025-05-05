/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:05:41 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/05 14:56:21 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void *routine(void *data)
{
    return NULL;
}

void init_philo(t_data *data)
{
    int i;

    i = 0;
    data->philosophers = malloc(data->number_of_philosophers * sizeof(t_philosophers));
    if (!data->philosophers)
        return(clean(data), 1);
    while (i < data->number_of_philosophers)
    {
        
    }
}
void init_threads(t_data *data)
{
   int i;

   data->threads = malloc(data->number_of_philosophers *sizeof(data->threads));
   if (!data->threads)
       return(clean(data), 1);
   i = 0;
   while (i < data->number_of_philosophers)
   {
        pthread_create(data->threads[i], NULL,routine, data);
        i++;
   }
   i = 0;
   while (i < data->number_of_philosophers)
    {
        pthread_join(data->threads[i], NULL);
        i++;
    }
}

void init_chopstick(t_data *data)
{
    int i;

    data->threads = malloc(data->number_of_philosophers *sizeof(data->chopsticks));
    if (!data->threads)
        return(clean(data), 1);
    i = 0;
    while (i < data->number_of_philosophers)
    {
        pthread_mutex_init(&data->chopsticks[i], NULL);
        i++;
    }
}