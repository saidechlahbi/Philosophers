/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:44:25 by sechlahb          #+#    #+#             */
/*   Updated: 2025/04/28 10:19:55 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int ft_atoi(char *str, t_philo *philo)
{
    long result;

    result = 0;
    while ((*str >= 9 && *str <= 13) || *str == 127)
        str++;
    if (*str == '+')
        str++;
    while(*str && (*str >= '0' && *str <= '9'))
    {
        result = (result * 10) + (*str - 48);
        if (result < -2147483648 || result > 2147483647)
        {
            free(philo);
            exit(1);
        }
        str++;
    }
    return ((int)result);
}

static void look_at(int ac, char **av)
{
    int i;
    int j;

    i = 1;
    while (i < ac)
    {
        j = 0;
        while (av[i][j])
        {
            if (av[i][0] == '+' && av[i][1] != '+')
                j++;
            else if (av[i][j] >= '0' && av[i][j] <= '9')
                j++;
            else
                exit(1);
        }
        i++;
    }   
}

static void initialisation(t_philo *philo)
{
    philo->number_of_philosophers = 0;
    philo->time_to_die = 0;
    philo->time_to_eat = 0;
    philo->time_to_sleep = 0;
    philo->number_of_times_each_philosopher_must_eat = 0;
}

t_philo *parsing(int ac, char **av)
{
    t_philo *philo;
    int i;
    int j;

    look_at(ac, av);
    philo = malloc(sizeof(t_philo));
    if (!philo)
        exit(1);
    initialisation(philo);
    if (ac == 5)
    {
        philo->number_of_philosophers = ft_atoi(av[1], philo);
        philo->time_to_die = ft_atoi(av[2], philo);
        philo->time_to_eat = ft_atoi(av[3], philo);
        philo->time_to_sleep = ft_atoi(av[4], philo);
    }
    else
    {
        philo->number_of_philosophers = ft_atoi(av[1], philo);
        philo->time_to_die = ft_atoi(av[2], philo);
        philo->time_to_eat = ft_atoi(av[3], philo);
        philo->time_to_sleep = ft_atoi(av[4], philo);
        philo->number_of_times_each_philosopher_must_eat = ft_atoi(av[5], philo);
    }
    return philo;
}
