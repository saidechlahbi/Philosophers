/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:38:10 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/30 22:12:33 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(t_philosophers *philo, long time)
{
	long start;
	long elapsed;

	start = get_time();
	while (1)
	{
		elapsed = get_time() - start;
		if (elapsed >= time)
			break;
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

void	ft_printf(t_philosophers *philo, char *str, int id)
{
	int val;
	long  time;

	val = 0;
	pthread_mutex_lock(&philo->data->mutex_for_printf);
	time = get_time() - philo->data->start_time;
	pthread_mutex_unlock(&philo->data->mutex_for_printf);
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

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_usec / 1000) + (time.tv_sec * 1000));
}

void clean(t_philosophers *philo)
{
    t_data *data;
    int i;
    int num_philos;

    if (!philo) return;
    data = philo->data;
    if (!data) return;
    
    num_philos = data->number_of_philosophers;
        i = 0;
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
    pthread_mutex_destroy(&data->mutex_for_printf);
    pthread_mutex_destroy(&data->mutex_nb_ph);
    pthread_mutex_destroy(&data->mutex_most_stop);
    free(data);
    free(philo);
}
