/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:03:51 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/13 16:14:30 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void eating (t_philosophers *arg)
{
    printf("%d   I am eating\n",arg->id);
}
void thinking(t_philosophers *arg)
{
    printf("%d   I am thinking\n",arg->id);
}

void sleeping(t_philosophers *arg)
{
    printf("%d   I am sleeping\n",arg->id);
}
void *routine(void *arg)
{
    t_philosophers *data;

    data = (t_philosophers *)arg;
    if (data->id % 2 == 0)
    {
        data
    }
    eating(data);
    thinking(data);
    sleeping(data);
    printf("======\n"); 
    return data;
}
