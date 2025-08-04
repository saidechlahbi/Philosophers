/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:16:08 by sechlahb          #+#    #+#             */
/*   Updated: 2025/08/04 20:00:11 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	help(t_philosophers *philo)
{
	int		i;
	int		num_philos;
	t_data	*data;

	i = 0;
	data = philo->data;
	num_philos = data->number_of_philosophers;
	while (i < num_philos)
	{
		pthread_mutex_destroy(&philo[i].mutex_last_meal);
		pthread_mutex_destroy(&philo[i].mutex_nb_eat);
		i++;
	}
	if (data->chopsticks)
	{
		i = 0;
		while (i < num_philos)
		{
			pthread_mutex_destroy(&data->chopsticks[i]);
			i++;
		}
		free(data->chopsticks);
	}
}

void	clean(t_philosophers *philo)
{
	t_data	*data;

	if (!philo)
		return ;
	data = philo->data;
	if (!data)
		return ;
	help(philo);
	pthread_mutex_destroy(&data->mutex_for_printf);
	pthread_mutex_destroy(&data->mutex_most_stop);
	pthread_mutex_destroy(&data->mutex_failed);
	free(data);
	free(philo);
}
