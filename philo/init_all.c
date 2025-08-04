/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:05:41 by sechlahb          #+#    #+#             */
/*   Updated: 2025/08/04 16:56:39 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philosophers	*init_philo(t_data *data)
{
	int				i;
	int				nb_philo;
	t_philosophers	*philosophers;

	nb_philo = data->number_of_philosophers;
	philosophers = malloc(nb_philo * sizeof(t_philosophers));
	if (!philosophers)
		return (free(data), NULL);
	if (!memset(philosophers, 0, nb_philo * sizeof(t_philosophers)))
	{
		free(data);
		free(philosophers);
		return (NULL);
	}
	i = 0;
	while (i < nb_philo)
	{
		philosophers[i].id = i + 1;
		philosophers[i].data = data;
		i++;
	}
	return (philosophers);
}

static int	create(t_philosophers *philo, t_data *data)
{
	int	i;

	philo->data->start_time = get_time();
	i = 0;
	while (i < data->number_of_philosophers)
	{
		philo[i].last_meal = data->start_time;
		i++;
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&philo[i].thread, NULL, routine,
				(void *)(&philo[i])))
		{
			while (i--)
				pthread_detach(philo[i].thread);
			return (1);
		}
		i++;
	}
	if (pthread_create(&data->monitoring, NULL, monitor, (void *)philo))
		return (1);
	return (0);
}

void	init_threads(t_philosophers *philo, t_data *data)
{
	int	i;

	if (create(philo, data))
	{
		pthread_mutex_lock(&data->mutex_failed);
		data->some_think_failed = 1;
		pthread_mutex_unlock(&data->mutex_failed);
		return ;
	}
	if (pthread_join(data->monitoring, NULL))
		return ;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(philo[i].thread, NULL))
			return ;
		i++;
	}
}
