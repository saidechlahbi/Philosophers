/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 16:02:13 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/07 21:16:50 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct s_philosophers
{
    int id;
    pthread_mutex_t *r_chopstick;
    pthread_mutex_t *l_chopstick;
} t_philosophers;

typedef struct s_data
{
    int *val;
    t_philosophers *philosophers;
    pthread_t *threads;
    pthread_mutex_t *chopsticks;
    int number_of_philosophers;
    int time_to_die;
    int time_to_eat;
    int time_to_sleep;
    int number_of_times_each_philosopher_must_eat;
}t_data;

/*-------------------- parsing----------------*/
t_data *parsing(int ac, char **av);

/*-------------------- clean------------------*/
void clean(t_data *data);



/*---------------- algorithme----------------*/
void *routine(void *arg);


/*---------------- initialisation-------------*/
void init_threads(t_data *data);
void init_chopstick(t_data *data);
void init_philo(t_data *data);
void take_chopstick(t_data *data);

#endif