/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithme_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:03:51 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/29 15:06:59 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int how_mush(t_philosophers *philo)
{
    int i;

    i = 0;
    while (i < philo->data->number_of_philosophers)
    {
        if (philo[i].nb_eat >= philo[i].data->n_of_t_e_p_m_e)
            i++;
        else
            return 0;        
    }
    printf("simulation stop\n");
    return 1;
}

void *monitor(void *arg)
{
    t_philosophers *philo;
    int number_philo;
    int i;

    philo = (t_philosophers *)arg;
    number_philo = philo->data->number_of_philosophers;
    while (1)
    {
        if (philo->data->n_of_t_e_p_m_e)
            if (how_mush(philo))
                return (philo->data->must_stop = 1, NULL);
        usleep(philo->data->time_to_die * 1000);
        i = -1;
        while (++i < number_philo)
        {
            if (get_time() - philo[i].last_meal >= philo[i].data->time_to_die)
            {
                philo->data->must_stop = 1;
                printf("%ld  %d  died\n", get_time() - philo[i].data->start_time, philo[i].id);
                return (NULL);
            }
        }
    }
    return (NULL);
}

static void daily_day (t_philosophers *philo)
{
    philo->nb_eat++;
    ft_printf(philo ,"%ld  %d  is eating\n", get_time() - philo->data->start_time, philo->id);
    usleep(philo->data->time_to_eat * 1000);
    pthread_mutex_unlock(philo->r_chopstick);
    pthread_mutex_unlock(philo->l_chopstick);
    ft_printf(philo ,"%ld  %d  is sleeping\n", get_time() - philo->data->start_time, philo->id);
    usleep(philo->data->time_to_sleep * 1000);
    ft_printf(philo ,"%ld  %d  is thinking\n", get_time() - philo->data->start_time, philo->id);
}

static void taken_forck(t_philosophers *philo)
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
    while (philo->data->must_stop == 0)
    {
        taken_forck(philo);
        daily_day(philo);
    }
    return NULL;
}


void init_philosophers(t_philosophers *philo)
{
    sem_t *semaphore;

    semaphore = sem_open()
}