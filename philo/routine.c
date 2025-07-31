/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:03:51 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/31 03:04:14 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void daily_day(t_philosophers *philo)
{
    pthread_mutex_lock(&philo->mutex_nb_eat);
    philo->nb_eat++;
    pthread_mutex_unlock(&philo->mutex_nb_eat);
    
    ft_printf(philo, "%ld  %d  is eating\n", philo->id);
    ft_usleep(philo, philo->data->time_to_eat);
    
    // Release in reverse order of acquisition for good practice
    if (philo->l_chopstick < philo->r_chopstick) {
        pthread_mutex_unlock(philo->r_chopstick);  // second_fork
        pthread_mutex_unlock(philo->l_chopstick);  // first_fork
    } else {
        pthread_mutex_unlock(philo->l_chopstick);  // second_fork  
        pthread_mutex_unlock(philo->r_chopstick);  // first_fork
    }
    
    ft_printf(philo, "%ld  %d  is sleeping\n", philo->id);
    ft_usleep(philo, philo->data->time_to_sleep);
    ft_printf(philo, "%ld  %d  is thinking\n", philo->id);
    
    // Small delay to prevent immediate re-acquisition
    ft_usleep(philo, 1);
}

// static void daily_day(t_philosophers *philo)
// {
//     pthread_mutex_lock(&philo->mutex_nb_eat);
//     philo->nb_eat++;
//     pthread_mutex_unlock(&philo->mutex_nb_eat);
    
//     ft_printf(philo, "%ld  %d  is eating\n", philo->id);
//     ft_usleep(philo, philo->data->time_to_eat);
    
//     // Release forks
//     if (philo->id == philo->data->number_of_philosophers) {
//         // Last philosopher releases in same order as acquired
//         pthread_mutex_unlock(philo->r_chopstick);
//         pthread_mutex_unlock(philo->l_chopstick);
//     } else {
//         pthread_mutex_unlock(philo->l_chopstick);
//         pthread_mutex_unlock(philo->r_chopstick);
//     }
    
//     ft_printf(philo, "%ld  %d  is sleeping\n", philo->id);
//     ft_usleep(philo, philo->data->time_to_sleep);
//     ft_printf(philo, "%ld  %d  is thinking\n", philo->id);
    
//     // Small thinking time to prevent immediate re-acquisition
//     ft_usleep(philo, 1);
// }

// static void	daily_day(t_philosophers *philo)
// {
// 	pthread_mutex_lock(&philo->mutex_nb_eat);
// 	philo->nb_eat++;
// 	pthread_mutex_unlock(&philo->mutex_nb_eat);
// 	ft_printf(philo, "%ld  %d  is eating\n", philo->id);
// 	ft_usleep(philo, philo->data->time_to_eat);
// 	pthread_mutex_unlock(philo->l_chopstick);
// 	pthread_mutex_unlock(philo->r_chopstick);
// 	ft_printf(philo, "%ld  %d  is sleeping\n", philo->id);
// 	ft_usleep(philo, philo->data->time_to_sleep);
// 	ft_printf(philo, "%ld  %d  is thinking\n", philo->id);
// 	ft_usleep(philo, 1);
// }

// static void	taken_forck(t_philosophers *philo)
// {
// 	pthread_mutex_t *first_fork, *second_fork;
	
// 	// if (philo->l_chopstick < philo->r_chopstick) {
// 	// 	first_fork = philo->l_chopstick;
// 	// 	second_fork = philo->r_chopstick;
// 	// } else {
// 	// 	first_fork = philo->r_chopstick;
// 	// 	second_fork = philo->l_chopstick;
// 	// }
//    if (philo->id % 2 == 1) {
//         // Odd philosophers: left fork first
//         first_fork = philo->l_chopstick;
//         second_fork = philo->r_chopstick;
//     } else {
//         // Even philosophers: right fork first
//         first_fork = philo->r_chopstick;
//         second_fork = philo->l_chopstick;
//     }
// 	// if (philo->id % 2 == 0)
// 	// {
// 	pthread_mutex_lock(first_fork);
// 	ft_printf(philo, "%ld  %d  has taken a fork\n", philo->id);
	
// 	pthread_mutex_lock(second_fork);
// 	ft_printf(philo, "%ld  %d  has taken a fork\n", philo->id);
// 		// pthread_mutex_lock(philo->l_chopstick);
// 		// 	ft_printf(philo, "%ld  %d  has taken a fork\n", philo->id);
// 		// pthread_mutex_lock(philo->r_chopstick);
// 		// 	ft_printf(philo, "%ld  %d  has taken a fork\n", philo->id);
// 	// }
// 	// else
// 	// {
// 	// 	pthread_mutex_lock(philo->r_chopstick);
// 	// 		ft_printf(philo, "%ld  %d  has taken a fork\n", philo->id);
// 	// 	pthread_mutex_lock(philo->l_chopstick);
// 	// 		ft_printf(philo, "%ld  %d  has taken a fork\n", philo->id);
// 	// }
// 	pthread_mutex_lock(&philo->mutex_last_meal);
// 	philo->last_meal = get_time();
// 	pthread_mutex_unlock(&philo->mutex_last_meal);
// }


static void taken_forck(t_philosophers *philo)
{
    pthread_mutex_t *first_fork, *second_fork;
    
    // ALWAYS use consistent global ordering based on memory addresses
    // This prevents deadlock by ensuring all threads acquire locks in same order
    if (philo->l_chopstick < philo->r_chopstick) {
        first_fork = philo->l_chopstick;
        second_fork = philo->r_chopstick;
    } else {
        first_fork = philo->r_chopstick;
        second_fork = philo->l_chopstick;
    }
    
    // No special cases - all philosophers follow same order
    pthread_mutex_lock(first_fork);
    ft_printf(philo, "%ld  %d  has taken a fork\n", philo->id);
    
    pthread_mutex_lock(second_fork);
    ft_printf(philo, "%ld  %d  has taken a fork\n", philo->id);
    
    pthread_mutex_lock(&philo->mutex_last_meal);
    philo->last_meal = get_time();
    pthread_mutex_unlock(&philo->mutex_last_meal);
}
// static void taken_forck(t_philosophers *philo)
// {
//     pthread_mutex_t *first_fork, *second_fork;
    
//     // Prevent deadlock: lower numbered fork first
//     if (philo->l_chopstick < philo->r_chopstick) {
//         first_fork = philo->l_chopstick;
//         second_fork = philo->r_chopstick;
//     } else {
//         first_fork = philo->r_chopstick;
//         second_fork = philo->l_chopstick;
//     }
    
//     // Special case for philosopher with highest ID to prevent circular wait
//     if (philo->id == philo->data->number_of_philosophers) {
//         // Last philosopher picks up forks in reverse order
//         pthread_mutex_lock(second_fork);
//         ft_printf(philo, "%ld  %d  has taken a fork\n", philo->id);
//         pthread_mutex_lock(first_fork);
//         ft_printf(philo, "%ld  %d  has taken a fork\n", philo->id);
//     } else {
//         pthread_mutex_lock(first_fork);
//         ft_printf(philo, "%ld  %d  has taken a fork\n", philo->id);
//         pthread_mutex_lock(second_fork);
//         ft_printf(philo, "%ld  %d  has taken a fork\n", philo->id);
//     }
    
//     pthread_mutex_lock(&philo->mutex_last_meal);
//     philo->last_meal = get_time();
//     pthread_mutex_unlock(&philo->mutex_last_meal);
// }

static void	assistance(t_philosophers *philo)
{
	pthread_mutex_unlock(&philo->data->mutex_nb_ph);
	pthread_mutex_lock(philo->l_chopstick);
	pthread_mutex_lock(&philo->mutex_last_meal);
	philo->last_meal = get_time();
	pthread_mutex_unlock(&philo->mutex_last_meal);
	ft_printf(philo, "%ld  %d  has taken a fork\n", philo->id);
	ft_usleep(philo, philo->data->time_to_die);
	pthread_mutex_unlock(philo->l_chopstick); 
	return ;
}

void	*routine(void *arg)
{
	t_philosophers	*philo;

	philo = (t_philosophers *)arg;
	pthread_mutex_lock(&philo->data->mutex_nb_ph);
	if (philo->data->number_of_philosophers == 1)
	{
		assistance(philo);
		return (NULL);
	}
	pthread_mutex_unlock(&philo->data->mutex_nb_ph);
	if (philo->id % 2)
		ft_usleep(philo, 15);
	while (1)
	{
		pthread_mutex_lock(&philo->data->mutex_most_stop);
		if (philo->data->must_stop == 1)
		{
			pthread_mutex_unlock(&philo->data->mutex_most_stop);
			break;
		}
		pthread_mutex_unlock(&philo->data->mutex_most_stop);
		taken_forck(philo);
		daily_day(philo);
	}
	return (NULL);
}
