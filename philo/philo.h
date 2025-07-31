/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:02:13 by sechlahb          #+#    #+#             */
/*   Updated: 2025/07/31 18:50:13 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data
{
	int				number_of_philosophers;
	pthread_mutex_t	mutex_nb_ph;
	int				must_stop;
	pthread_mutex_t	mutex_most_stop;
	long			start_time;
	int				time_to_die;
	pthread_mutex_t	*chopsticks;
	int				time_to_eat;
	int				time_to_sleep;
	int				n_of_t_e_p_m_e;
	pthread_mutex_t	mutex_for_printf;
	int				some_think_failed;
	pthread_mutex_t	mutex_failed;
	pthread_t		monitoring;
}					t_data;

typedef struct s_philosophers
{
	pthread_t		thread;
	int				id;
	long			last_meal;
	pthread_mutex_t	mutex_last_meal;
	int				nb_eat;
	pthread_mutex_t	mutex_nb_eat;
	pthread_mutex_t	*r_chopstick;
	pthread_mutex_t	*l_chopstick;
	t_data			*data;
}					t_philosophers;

/*-------------------- parsing----------------*/
t_data				*parsing(int ac, char **av);

/*---------------- initialisation-------------*/
t_philosophers		*init_philo(t_data *data);
t_data				*init_chopstick(t_data *data, t_philosophers *philo);
void				take_chopstick(t_philosophers *philo, t_data *data);
void				init_threads(t_philosophers *philo, t_data *data);

/*-------------------- tools------------------*/
void				clean(t_philosophers *philo);
long				get_time(void);
void				ft_printf(t_philosophers *philo, char *str, int id);
void				ft_usleep(t_philosophers *philo, long time);
/*---------------- algorithme----------------*/
void				*routine(void *arg);
void				*monitor(void *arg);

#endif