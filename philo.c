/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:38:10 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/06 16:12:54 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void clean(t_data *data)
{
    if (data->philosophers)
        free(data->philosophers);
    if (data->threads)
        free(data->threads);
    if (data->chopsticks)
        free(data->chopsticks);
    free(data);
    return ;
}

int main (int ac, char **av)
{
    t_data *data;

    if (ac == 5 || ac == 6)
    {
        data = parsing(ac, av);
        init_philo(data);
        init_chopstick(data);
        take_chopstick(data);
        init_threads(data);

        
        //     printf("%d %d %d %d %d\n", data->number_of_philosophers
        //     ,data->time_to_die,data->time_to_eat
        // , data->time_to_sleep, data->number_of_times_each_philosopher_must_eat);
    }
 
    // printf("%d  %d  is eating\n");
    // printf("%d  %d  is sleeping\n");
    // printf("%d  %d  is thinking\n");
    // printf("%d  %d  died\n");
    // clean(data);
    exit(1);
}

