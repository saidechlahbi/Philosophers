/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:38:10 by sechlahb          #+#    #+#             */
/*   Updated: 2025/06/26 00:37:01 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_search(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'd' && str[i + 1] == 'i')
			return 1;
		i++;
	}
	return 0;
}

void	ft_printf(t_philosophers *philo, char *str, long time, int id)
{
	int val;

	val = 0;
	pthread_mutex_lock(&philo->data->mutex_most_stop);
	if (philo->data->must_stop == 1)
	{
		
		val = ft_search(str);
		pthread_mutex_unlock(&philo->data->mutex_most_stop);
		if (val == 1)
		{
			pthread_mutex_lock(&philo->data->mutex_for_printf);
			printf(str, time, id);
			pthread_mutex_unlock(&philo->data->mutex_for_printf);
			return;
		}
		return ;
	}
	pthread_mutex_unlock(&philo->data->mutex_most_stop);
	pthread_mutex_lock(&philo->data->mutex_for_printf);
	printf(str, time, id);
	pthread_mutex_unlock(&philo->data->mutex_for_printf);
}

void	clean(t_philosophers *philo)
{
	t_data	*data;

	data = philo->data;
	if (data->chopsticks)
		free(data->chopsticks);
	if (data)
		free(data);
	if (philo)
		free(philo);
	return ;
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_usec / 1000) + (time.tv_sec * 1000));
}
