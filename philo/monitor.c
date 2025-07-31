/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 16:17:10 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/31 02:55:32 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	how_mush(t_philosophers *philo)
{
	int	i;
	int	num_philo;
	int count;

	count = 0;
	i = 0;
	pthread_mutex_lock(&philo->data->mutex_nb_ph);
	num_philo = philo->data->number_of_philosophers;
	pthread_mutex_unlock(&philo->data->mutex_nb_ph);
	while (i < num_philo)
	{	pthread_mutex_lock(&philo[i].mutex_nb_eat);
		if (philo[i].nb_eat >= philo[i].data->n_of_t_e_p_m_e)
			count++;
		pthread_mutex_unlock(&philo[i].mutex_nb_eat);
		i++;
	}
	if (count == num_philo)
		return 1;
	return 0;
}

static int	assistance(t_philosophers *philo)
{
	int		number_philo;
	long	time;
	int		i;

	pthread_mutex_lock(&philo->data->mutex_nb_ph);
	number_philo = philo->data->number_of_philosophers;
	pthread_mutex_unlock(&philo->data->mutex_nb_ph);
	i = 0;
	while (i < number_philo)
	{
		pthread_mutex_lock(&philo[i].mutex_last_meal);
		time = philo[i].last_meal;
		pthread_mutex_unlock(&philo[i].mutex_last_meal);
		if ((get_time() - time ) >= philo[i].data->time_to_die)
		{
			pthread_mutex_lock(&philo->data->mutex_most_stop);
			philo->data->must_stop = 1;
			pthread_mutex_unlock(&philo->data->mutex_most_stop);
			ft_printf(&philo[i], "%ld  %d  died\n", philo[i].id);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	while (1)
	{
		if (philo->data->n_of_t_e_p_m_e)
		{
			if (how_mush(philo))
			{
				pthread_mutex_lock(&philo->data->mutex_most_stop);
				philo->data->must_stop = 1;
				pthread_mutex_unlock(&philo->data->mutex_most_stop);
				return (NULL);
			}
		}
		if (assistance(philo))
			return (NULL);		
		ft_usleep(philo, 100);
	}
	return (NULL);
}
