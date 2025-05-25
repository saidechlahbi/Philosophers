/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:05:41 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/25 13:51:52 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void routine (t_philosophers *philo, t_data *data)
{
    while(1)
    {
        
    }
}

void init_philo(t_philosophers *philo, t_data *data)
{
    int i;

    i = 0;
    while (i < data->number_of_philosophers)
    {
        philo->pid = fork();
        if (philo->pid == 0)
            routine(philo, data);
        i++;
    }
}