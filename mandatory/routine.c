/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:03:51 by sechlahb          #+#    #+#             */
/*   Updated: 2025/06/11 10:41:09 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	daily_day(t_philosophers *philo)
{
	long	time;

	philo->nb_eat++;
	time = get_time() - philo->data->start_time;
	ft_printf(philo, "%ld  %d  is eating\n", time, philo->id);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->l_chopstick);
	pthread_mutex_unlock(philo->r_chopstick);
	time = get_time() - philo->data->start_time;
	ft_printf(philo, "%ld  %d  is sleeping\n", time, philo->id);
	usleep(philo->data->time_to_sleep * 1000);
	time = get_time() - philo->data->start_time;
	ft_printf(philo, "%ld  %d  is thinking\n", time, philo->id);
}

static void	taken_forck(t_philosophers *philo)
{
	long	time;

	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->l_chopstick);
		time = get_time() - philo->data->start_time;
		ft_printf(philo, "%ld  %d  has taken a fork\n", time, philo->id);
		pthread_mutex_lock(philo->r_chopstick);
		time = get_time() - philo->data->start_time;
		ft_printf(philo, "%ld  %d  has taken a fork\n", time, philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->r_chopstick);
		time = get_time() - philo->data->start_time;
		ft_printf(philo, "%ld  %d  has taken a fork\n", time, philo->id);
		pthread_mutex_lock(philo->l_chopstick);
		time = get_time() - philo->data->start_time;
		ft_printf(philo, "%ld  %d  has taken a fork\n", time, philo->id);
	}
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->mutex_last_meal);
}

static void	assistance(t_philosophers *philo)
{
	long	time;

	pthread_mutex_unlock(&philo->data->mutex);
	pthread_mutex_lock(philo->l_chopstick);
	philo->last_meal = get_time();
	time = get_time() - philo->data->start_time;
	ft_printf(philo, "%ld  %d  has taken a fork\n", time, philo->id);
	usleep(philo->data->time_to_die);
	return ;
}

void	*routine(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	pthread_mutex_lock(&philo->data->mutex);
	if (philo->data->number_of_philosophers == 1)
	{
		assistance(philo);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->data->mutex);
	if (philo->id % 2)
		usleep(1000);
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex_most_stop);
		if (philo->data->must_stop == 1)
		{
			pthread_mutex_unlock(&philo->data->mutex_most_stop);
			return (NULL);
		}
		pthread_mutex_unlock(&philo->data->mutex_most_stop);
		taken_forck(philo);
		daily_day(philo);
	}
	return (NULL);
}
