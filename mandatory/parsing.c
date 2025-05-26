/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:44:25 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/26 18:09:45 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int ft_atoi(char *str, t_data *data)
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
            free(data);
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

static int check(t_data *data)
{
    if (data->number_of_philosophers == 0 || data->time_to_die == 0
    || data->time_to_eat == 0 || data->time_to_sleep == 0)
        return 1;
    return 0;
}
t_data *parsing(int ac, char **av)
{
    t_data *data;

    data = NULL;
    look_at(ac, av);
    data = malloc(sizeof(t_data));
    if (!data)
        return NULL;
    if (!memset(data, 0, sizeof(t_data)))
        return (free(data), NULL);
    data->number_of_philosophers = ft_atoi(av[1], data);
    data->time_to_die = ft_atoi(av[2], data);
    data->time_to_eat = ft_atoi(av[3], data);
    data->time_to_sleep = ft_atoi(av[4], data);
    if (ac == 6)
        data->n_of_t_e_p_m_e = ft_atoi(av[5], data);
    if (check(data) || (ac == 6 && data->n_of_t_e_p_m_e == 0))
        return (free(data), NULL);
    return data;
}
