/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:03:51 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/26 11:53:21 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int how_mush(t_philosophers *philo)
{
    int i;

    i = 0;
    while (i < philo->data->number_of_philosophers)
    {
        if (philo[i].nb_eat >= philo[i].data->number_of_times_each_philosopher_must_eat)
            i++;
        else
            return 0;        
    }
    printf("simulation stop\n");
    return 1;
}

void *monitor(void *philo)
{
    t_philosophers *philosophers;
    int number_philo;
    int i;

    philosophers = (t_philosophers *)philo;
    number_philo = philosophers->data->number_of_philosophers;
    while (1)
    {
        if (philosophers->data->number_of_times_each_philosopher_must_eat)
            if (how_mush(philo))
                exit(0);
        usleep(philosophers->data->time_to_die * 1000);
        i = 0;
        while (i < number_philo)
        {
            if (get_time() - philosophers[i].last_meal >= philosophers[i].data->time_to_die)
            {
                ft_printf(philosophers , "%ld  %d  died\n", get_time() - philosophers[i].data->start_time, philosophers[i].id);
                exit(1);
            }
            i++;
        }
        usleep(500);
    }
    return NULL;
}

void daily_day (t_philosophers *arg)
{
    arg->nb_eat++;
    ft_printf(arg ,"%ld  %d  is eating\n", get_time() - arg->data->start_time, arg->id);
    usleep(arg->data->time_to_eat * 1000);
    pthread_mutex_unlock(arg->r_chopstick);
    pthread_mutex_unlock(arg->l_chopstick);
    ft_printf(arg ,"%ld  %d  is sleeping\n", get_time() - arg->data->start_time, arg->id);
    usleep(arg->data->time_to_sleep * 1000);
    ft_printf(arg ,"%ld  %d  is thinking\n", get_time() - arg->data->start_time, arg->id);
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
        ft_printf(philo ,"%ld  %d  has taken a fork\n",  get_time() - philo->data->start_time, philo->id);
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
            ft_printf(philo ,"%ld  %d  has taken a fork\n",  get_time() - philo->data->start_time, philo->id);
            pthread_mutex_lock(philo->r_chopstick);
            ft_printf(philo ,"%ld  %d  has taken a fork\n",  get_time() - philo->data->start_time, philo->id);
        }else
        {
            pthread_mutex_lock(philo->l_chopstick);
            ft_printf(philo ,"%ld  %d  has taken a fork\n",  get_time() - philo->data->start_time, philo->id);
            pthread_mutex_lock(philo->r_chopstick);
            ft_printf(philo ,"%ld  %d  has taken a fork\n",  get_time() - philo->data->start_time, philo->id);
        }
        philo->last_meal = get_time();
        daily_day(philo);
    }
    return philo;
}
