/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:38:10 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/26 18:40:02 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_printf(t_philosophers *philo, char *str, long time, int id)
{
    if (philo->data->must_stop)
        return;
    pthread_mutex_lock(&philo->data->mutex_for_printf);
    printf(str, time, id);
    pthread_mutex_unlock(&philo->data->mutex_for_printf);
}

void clean(t_philosophers *philo)
{
    t_data *data;

    data = philo->data;
    if (data->chopsticks)
        free(data->chopsticks);
    if(data)
        free(data);
    if (philo)
        free(philo);
    return;
}

long    get_time()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return ((time.tv_usec / 1000) + (time.tv_sec * 1000));
}
