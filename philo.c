/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:38:10 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/15 23:11:53 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void clean(t_data *data)
{
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
    t_philosophers *philo;

    if (ac == 5 || ac == 6)
    {
        data = parsing(ac, av);
        philo = init_philo(data);
        init_chopstick(data);
        take_chopstick(philo, data);
        init_threads(philo, data);
    }
 
   
    // clean(data);
    exit(1);
}

long    get_time()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_usec * 1000 + time.tv_sec / 1000);
}
