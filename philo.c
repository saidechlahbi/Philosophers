/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:38:10 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/05 14:13:46 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void clean(t_data *data)
{
    return ;
}


int main (int ac, char **av)
{
    t_data *data;

    if (ac == 5 || ac == 6)
    {
        data = parsing(ac, av);
        init_threads(data);
        init_chopstick(data);
    }
    // printf("%d  %d  has taken a fork\n");
    // printf("%d  %d  is eating\n");
    // printf("%d  %d  is sleeping\n");
    // printf("%d  %d  is thinking\n");
    // printf("%d  %d  died\n");
    exit(1);
}

