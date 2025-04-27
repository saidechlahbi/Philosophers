/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:38:10 by sechlahb          #+#    #+#             */
/*   Updated: 2025/04/27 17:46:20 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void initialisation(t_philo *philo)
{
    philo->number_of_philosophers = 0;
    philo->time_to_die = 0;
    philo->time_to_eat = 0;
    philo->time_to_sleep = 0;
    philo->number_of_times_each_philosopher_must_eat = 0;
}

int main (int ac, char **av)
{
    t_philo *philo;

    if (ac == 5 || ac == 6)
    {
        philo = malloc(sizeof(philo));
        if (!philo)
            exit(1);
        initialisation(philo);
        parsing(ac, av, philo);
    }
    exit(1);
}