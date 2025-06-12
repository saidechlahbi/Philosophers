/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:05:41 by sechlahb          #+#    #+#             */
/*   Updated: 2025/06/11 10:48:15 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philosophers	*init_philo(t_data *data)
{
	int				i;
	int				value;
	t_philosophers	*philosophers;

	value = data->number_of_philosophers;
	philosophers = malloc(value * sizeof(t_philosophers));
	if (!philosophers)
		return (free(data), NULL);
	if (!memset(philosophers, 0, value * sizeof(t_philosophers)))
	{
		free(data);
		free(philosophers);
		return (NULL);
	}
	i = 0;
	while (i < data->number_of_philosophers)
	{
		philosophers[i].id = i + 1;
		philosophers[i].data = data;
		pthread_mutex_init(&philosophers[i].mutex_last_meal, NULL);
		i++;
	}
	return (philosophers);
}

t_data	*init_chopstick(t_data *data)
{
	int	i;
	int	value;

	value = data->number_of_philosophers;
	data->chopsticks = malloc(value * sizeof(pthread_mutex_t));
	if (!data->chopsticks)
	{
		free(data);
		return (NULL);
	}
	if (!memset(data->chopsticks, 0, value * sizeof(pthread_mutex_t)))
	{
		free(data->chopsticks);
		free(data);
		return (NULL);
	}
	i = -1;
	while (i++ < value - 1)
		pthread_mutex_init(&data->chopsticks[i], NULL);
	pthread_mutex_init(&data->mutex_for_printf, NULL);
	pthread_mutex_init(&data->mutex, NULL);
	pthread_mutex_init(&data->mutex_most_stop, NULL);
	return (data);
}

void	take_chopstick(t_philosophers *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers - 1)
	{
		philo[i].l_chopstick = &data->chopsticks[i];
		philo[i].r_chopstick = &data->chopsticks[i + 1];
		i++;
	}
	philo[i].l_chopstick = &data->chopsticks[i];
	philo[i].r_chopstick = &data->chopsticks[0];
}

static void	create(t_philosophers *philo, t_data *data)
{
	int	i;

	philo->data->start_time = get_time();
	i = -1;
	while (i++ < data->number_of_philosophers - 1)
		philo[i].last_meal = data->start_time;
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_create(&philo[i].thread, NULL, routine,
				(void *)(&philo[i])))
		{
			clean(philo);
			return ;
		}
		i++;
	}
	if (pthread_create(&data->monitoring, NULL, monitor, (void *)philo))
	{
		clean(philo);
		return ;
	}
}

void	init_threads(t_philosophers *philo, t_data *data)
{
	int	i;

	create(philo, data);
	
	i = 0;
	while (i < data->number_of_philosophers)
	{
		if (pthread_join(philo[i].thread, NULL))
		{
			clean(philo);
			return ;
		}
		i++;
	}
	if (pthread_join(data->monitoring, NULL))
	{
		clean(philo);
		return ;
	}
}
