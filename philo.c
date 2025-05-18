/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:38:10 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/18 14:08:23 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void clean(t_philosophers *philo)
{
    t_data *data;

    data = philo->data;
    free(philo);
    free(data->chopsticks);
    free(data->threads);
    free(data);
    exit(1);
}

long    get_time()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_usec * 1000) + (time.tv_sec / 1000));
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
    exit(1);
}
