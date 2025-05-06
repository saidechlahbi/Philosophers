/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithme.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sechlahb <sechlahb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:03:51 by sechlahb          #+#    #+#             */
/*   Updated: 2025/05/06 17:56:09 by sechlahb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// void *routine(void *arg)
// {
//     int i;
//     t_data *data;

//     data = (t_data *)arg;
//     if (data->philosophers->id % 2 == 0)
//     {
//         pthread_mutex_lock(data->philosophers[i].l_chopstick);
//         pthread_mutex_lock(data->philosophers[i].r_chopstick);
//     }
// }


// void *routine(void *arg)
// {
//     int i;
//     t_data *data;

//     data = (t_data *)arg;
//     i = 0;
//     while (1)
//     {
//         i = 0;
//         while (i < data->number_of_philosophers)
//         {
//             if (i % 2 == 0)
//             {  
//                 pthread_mutex_lock(data->philosophers[i].l_chopstick);
//                 pthread_mutex_lock(data->philosophers[i].r_chopstick);
//                 printf("  %d  has taken a fork\n",data->philosophers[i].id);
//             }
//             i++;
//         }
//         usleep(1000);
//         i = 0;
//         while (i < data->number_of_philosophers)
//         {
//             if (i % 2 == 0)
//             {  
//                 pthread_mutex_unlock(data->philosophers[i].l_chopstick);
//                 pthread_mutex_unlock(data->philosophers[i].r_chopstick);
//             }
//             i++;
//         }
//         i = 0;
//         while (i < data->number_of_philosophers)
//         {
//             if (i % 2 != 0)
//             {  
//                 pthread_mutex_lock(data->philosophers[i].l_chopstick);
//                 pthread_mutex_lock(data->philosophers[i].r_chopstick);
//                 printf("%d  %d  has taken a fork\n",1,data->philosophers[i].id);
//             }
//             i++;
//         }
//         usleep(1000);
//         i = 0;
//         while (i < data->number_of_philosophers)
//         {
//             if (i % 2 != 0)
//             {  
//                 pthread_mutex_unlock(data->philosophers[i].l_chopstick);
//                 pthread_mutex_unlock(data->philosophers[i].r_chopstick);
//             }
//             i++;
//         }
//     }
//     return data;
// }

void mimi (t_data *arg)
{
    printf("i am mimi %d\n",(*arg->philosophers->id));
}
void nini(t_data *arg)
{
    printf("i am nini %d\n",(*arg->philosophers->id));
}

void khikhi(t_data *arg)
{
    printf("i am khikhi%d\n",(*arg->philosophers->id));
}
void *routine(void *arg)
{
    t_data *data;

    data = (t_data *)arg;
int i = 1;
    while (i--)
    {
        mimi(data);
        nini(data);
        khikhi(data);
        printf("======\n");
    }
    return data;
}
