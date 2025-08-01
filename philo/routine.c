/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:03:51 by sechlahb          #+#    #+#             */
/*   Updated: 2025/08/01 11:20:44 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	daily_day(t_philosophers *philo)
{
	pthread_mutex_lock(&philo->mutex_nb_eat);
	philo->nb_eat++;
	pthread_mutex_unlock(&philo->mutex_nb_eat);
	ft_printf(philo, "%ld  %d  is eating\n", philo->id);
	ft_usleep(philo, philo->data->time_to_eat);
	if (philo->l_chopstick < philo->r_chopstick)
	{
		pthread_mutex_unlock(philo->r_chopstick);
		pthread_mutex_unlock(philo->l_chopstick);
	}
	else
	{
		pthread_mutex_unlock(philo->l_chopstick);
		pthread_mutex_unlock(philo->r_chopstick);
	}
	ft_printf(philo, "%ld  %d  is sleeping\n", philo->id);
	ft_usleep(philo, philo->data->time_to_sleep);
	ft_printf(philo, "%ld  %d  is thinking\n", philo->id);
	ft_usleep(philo, 1);
}

static void	taken_forck(t_philosophers *philo)
{
	if (philo->l_chopstick < philo->r_chopstick)
	{
		pthread_mutex_lock(philo->l_chopstick);
		ft_printf(philo, "%ld  %d  has taken a fork\n", philo->id);
		pthread_mutex_lock(philo->r_chopstick);
		ft_printf(philo, "%ld  %d  has taken a fork\n", philo->id);
	}
	else
	{
		pthread_mutex_lock(philo->r_chopstick);
		ft_printf(philo, "%ld  %d  has taken a fork\n", philo->id);
		pthread_mutex_lock(philo->l_chopstick);
		ft_printf(philo, "%ld  %d  has taken a fork\n", philo->id);
	}
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->mutex_last_meal);
}

static void	assistance(t_philosophers *philo)
{
	pthread_mutex_unlock(&philo->data->mutex_nb_ph);
	pthread_mutex_lock(philo->l_chopstick);
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->mutex_last_meal);
	ft_printf(philo, "%ld  %d  has taken a fork\n", philo->id);
	ft_usleep(philo, philo->data->time_to_die);
	pthread_mutex_unlock(philo->l_chopstick);
	return ;
}

void	*routine(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	pthread_mutex_lock(&philo->data->mutex_nb_ph);
	if (philo->data->number_of_philosophers == 1)
		return (assistance(philo), NULL);
	pthread_mutex_unlock(&philo->data->mutex_nb_ph);
	pthread_mutex_lock(&philo->data->mutex_failed);
	if (philo->data->some_think_failed == 1)
		return (pthread_mutex_unlock(&philo->data->mutex_failed), NULL);
	pthread_mutex_unlock(&philo->data->mutex_failed);
	if (philo->id % 2)
		ft_usleep(philo, 15);
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex_most_stop);
		if (philo->data->must_stop == 1)
			return (pthread_mutex_unlock(&philo->data->mutex_most_stop), NULL);
		pthread_mutex_unlock(&philo->data->mutex_most_stop);
		taken_forck(philo);
		daily_day(philo);
	}
	return (NULL);
}
