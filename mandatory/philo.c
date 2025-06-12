/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 17:38:10 by sechlahb          #+#    #+#             */
/*   Updated: 2025/06/11 10:42:07 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_data			*data;
	t_philosophers	*philo;

	if (ac == 5 || ac == 6)
	{
		data = parsing(ac, av);
		if (!data)
			return (1);
		philo = init_philo(data);
		if (!philo)
			return (1);
		data = init_chopstick(data);
		if (!data)
			return (free(data), 1);
		take_chopstick(philo, data);
		init_threads(philo, data);
		clean(philo);
	}
	return (0);
}
