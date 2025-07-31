/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_chopstick.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 18:23:18 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/31 18:51:12 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	assisstance(t_philosophers *philo, t_data *data)
{
	int	i;
	int	value;

	i = 0;
	value = philo->data->number_of_philosophers;
	while (i < value)
	{
		if (pthread_mutex_init(&philo[i].mutex_last_meal, NULL))
			return (1);
		if (pthread_mutex_init(&philo[i].mutex_nb_eat, NULL))
			return (1);
		i++;
	}
	if (pthread_mutex_init(&data->mutex_for_printf, NULL))
		return (1);
	if (pthread_mutex_init(&data->mutex_nb_ph, NULL))
		return (1);
	if (pthread_mutex_init(&data->mutex_most_stop, NULL))
		return (1);
	if (pthread_mutex_init(&data->mutex_failed, NULL))
		return (1);
	return (0);
}

t_data	*init_chopstick(t_data *data, t_philosophers *philo)
{
	int	i;
	int	value;

	value = data->number_of_philosophers;
	data->chopsticks = malloc(value * sizeof(pthread_mutex_t));
	if (!data->chopsticks)
		return (NULL);
	if (!memset(data->chopsticks, 0, value * sizeof(pthread_mutex_t)))
		return (NULL);
	i = 0;
	while (i < value)
	{
		if (pthread_mutex_init(&data->chopsticks[i], NULL))
			return (NULL);
		i++;
	}
	if (assisstance(philo, data))
	{
		return (NULL);
	}
	return (data);
}

void	take_chopstick(t_philosophers *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->number_of_philosophers)
	{
		philo[i].l_chopstick = &data->chopsticks[i];
		philo[i].r_chopstick = &data->chopsticks[(i + 1)
			% data->number_of_philosophers];
		i++;
	}
}
