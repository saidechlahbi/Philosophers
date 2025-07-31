/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:05:41 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/31 02:43:11 by sechlahb         ###   ########.fr       */
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
		pthread_mutex_init(&philosophers[i].mutex_nb_eat, NULL);
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
		return (free(data), NULL);
	if (!memset(data->chopsticks, 0, value * sizeof(pthread_mutex_t)))
	{
		free(data->chopsticks);
		free(data);
		return (NULL);
	}
	i = 0;
	while (i < value)
	{
		pthread_mutex_init(&data->chopsticks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->mutex_for_printf, NULL);
	pthread_mutex_init(&data->mutex_nb_ph, NULL);
	pthread_mutex_init(&data->mutex_most_stop, NULL);
	return (data);
}

void	take_chopstick(t_philosophers *philo, t_data *data)
{
	int	i;

	i = 0;
    while (i < data->number_of_philosophers)
    {
        philo[i].l_chopstick = &data->chopsticks[i];
        philo[i].r_chopstick = &data->chopsticks[(i + 1) % data->number_of_philosophers];
        i++;
	}
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
			return 1;
		i++;
	}
	if (pthread_create(&data->monitoring, NULL, monitor, (void *)philo))
		return 1;
	return 0;
}

void	init_threads(t_philosophers *philo, t_data *data)
{
	int	i;

	if (create(philo, data))
		return ;
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
