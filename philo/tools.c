/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:38:10 by sechlahb          #+#    #+#             */
/*   Updated: 2025/08/01 00:24:09 by sechlahb         ###   ########.fr       */
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
		usleep(500);
	}
	return ;
}

int	ft_search(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'd' && str[i + 1] == 'i')
			return (1);
		i++;
	}
	return (0);
}

void	ft_printf(t_philosophers *philo, char *str, int id)
{
	int		val;
	long	time;
	int		must_stop;

	val = 0;
	val = ft_search(str);
	pthread_mutex_lock(&philo->data->mutex_most_stop);
	must_stop = philo->data->must_stop;
	pthread_mutex_unlock(&philo->data->mutex_most_stop);
	pthread_mutex_lock(&philo->data->mutex_for_printf);
	time = get_time() - philo->data->start_time;
	if (must_stop == 1)
	{
		if (val == 1)
		{
			printf(str, time, id);
			pthread_mutex_unlock(&philo->data->mutex_for_printf);
			return ;
		}
		pthread_mutex_unlock(&philo->data->mutex_for_printf);
		return ;
	}
	printf(str, time, id);
	pthread_mutex_unlock(&philo->data->mutex_for_printf);
}
