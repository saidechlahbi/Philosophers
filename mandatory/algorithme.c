/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:03:51 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/20 21:53:03 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void eating (t_philosophers *arg)
{
    arg->nb_eat++;
    ft_printf(arg ,"%ld  %d  is eating\n", get_time() - arg->data->start_time, arg->id);
    usleep(arg->data->time_to_eat * 1000);
    pthread_mutex_unlock(arg->r_chopstick);
    pthread_mutex_unlock(arg->l_chopstick);
}
void thinking(t_philosophers *arg)
{
    ft_printf(arg ,"%ld  %d  is thinking\n", get_time() - arg->data->start_time, arg->id);
    // usleep((arg->data->time_to_die - (arg->data->time_to_eat + arg->data->time_to_sleep)) * 1000);
}

void sleeping(t_philosophers *arg)
{
    ft_printf(arg ,"%ld  %d  is sleeping\n", get_time() - arg->data->start_time, arg->id);
    usleep(arg->data->time_to_sleep * 1000);
}
void *routine(void *arg)
{
    t_philosophers *philo;

    philo = (t_philosophers *)arg;
    if (philo->last_meal == 0)
        philo->last_meal = philo->data->start_time;
    if (philo->data->number_of_philosophers == 1)
    {
        pthread_mutex_lock(philo->l_chopstick);
        philo->last_meal = get_time();
        ft_printf(philo ,"%ld  %d has taken a fork\n",  get_time() - philo->data->start_time, philo->id);
        usleep(philo->data->time_to_die);
        return NULL;
    }
    if (philo->id % 2)
        usleep(1000);
    while (1)
    {
        if (philo->id % 2 == 0)
        {
            pthread_mutex_lock(philo->l_chopstick);
            ft_printf(philo ,"%ld  %d has taken a fork\n",  get_time() - philo->data->start_time, philo->id);
            pthread_mutex_lock(philo->r_chopstick);
            ft_printf(philo ,"%ld  %d has taken a fork\n",  get_time() - philo->data->start_time, philo->id);
        }else
        {
            pthread_mutex_lock(philo->l_chopstick);
            ft_printf(philo ,"%ld  %d has taken a fork\n",  get_time() - philo->data->start_time, philo->id);
            pthread_mutex_lock(philo->r_chopstick);
            ft_printf(philo ,"%ld  %d has taken a fork\n",  get_time() - philo->data->start_time, philo->id);
        }
        philo->last_meal = get_time();
        eating(philo);
        sleeping(philo);
        thinking(philo);
    }
    return philo;
}
