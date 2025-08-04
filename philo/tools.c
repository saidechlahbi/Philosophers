/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:38:10 by sechlahb          #+#    #+#             */
/*   Updated: 2025/08/04 20:25:24 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_usec / 1000) + (time.tv_sec * 1000));
}

void	ft_usleep(t_philosophers *philo, long time)
{
	long	start;
	long	elapsed;

	start = get_time();
	while (1)
	{
		elapsed = get_time() - start;
		if (elapsed >= time)
			break ;
		pthread_mutex_lock(&(philo->data->mutex_most_stop));
		if (philo->data->must_stop)
		{
			pthread_mutex_unlock(&(philo->data->mutex_most_stop));
			return ;
		}
		pthread_mutex_unlock(&(philo->data->mutex_most_stop));
		usleep(100);
	}
	return ;
}

void	ft_printf(t_philosophers *philo, char *str, int id)
{
	long	time;

	pthread_mutex_lock(&philo->data->mutex_most_stop);
	if (philo->data->must_stop)
	{
		pthread_mutex_unlock(&philo->data->mutex_most_stop);
		return ;
	}
	pthread_mutex_lock(&philo->data->mutex_for_printf);
	time = get_time() - philo->data->start_time;
	printf(str, time, id);
	pthread_mutex_unlock(&philo->data->mutex_for_printf);
	pthread_mutex_unlock(&philo->data->mutex_most_stop);
}
