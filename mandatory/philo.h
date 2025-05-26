/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:02:13 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/26 18:31:43 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct s_data
{
    int must_stop;
    pthread_mutex_t mutex_for_printf;;
    long start_time;
    pthread_mutex_t *chopsticks;
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int n_of_t_e_p_m_e;
}t_data;

typedef struct s_philosophers
{
    pthread_t thread;
    int id;
    long last_meal;
    int nb_eat;
    pthread_mutex_t *r_chopstick;
    pthread_mutex_t *l_chopstick;
    t_data *data;
} t_philosophers;

/*-------------------- parsing----------------*/
t_data *parsing(int ac, char **av);

/*-------------------- clean------------------*/
void clean(t_philosophers *philo);

long    get_time();

/*---------------- algorithme----------------*/
void *routine(void *arg);
void *monitor(void *philo);
void ft_printf(t_philosophers *philo, char *str, long time, int id);

/*---------------- initialisation-------------*/
t_philosophers *init_philo(t_data *data);
t_data  *init_chopstick(t_data *data);
void take_chopstick(t_philosophers *philo,t_data *data);
void init_threads(t_philosophers *philo, t_data *data);

#endif