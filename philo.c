/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:38:10 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/03 12:03:28 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void clean(t_simulation *simulation)
{
    return ;
}

int main (int ac, char **av)
{
    t_simulation *simulation;

    if (ac == 5 || ac == 6)
    {
        simulation = parsing(ac, av);
        simulation->philo = malloc(sizeof(simulation->philo));
        if (!simulation->philo)
            return(clean(simulation), 1);
        
    }
    // printf("%d  %d  has taken a fork\n");
    // printf("%d  %d  is eating\n");
    // printf("%d  %d  is sleeping\n");
    // printf("%d  %d  is thinking\n");
    // printf("%d  %d  died\n");
    exit(1);
}

