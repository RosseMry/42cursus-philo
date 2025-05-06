/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarcas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:50:29 by rmarcas-          #+#    #+#             */
/*   Updated: 2025/04/28 16:50:32 by rmarcas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_philo(t_table *table)
{
	t_philo *philo;
	int i;

	i = -1;
	philo = table->philo;
	while(++i < table->num_philo)
	{
		philo[i].id = i + 1;
		philo[i].left_fork = i;
		philo[i].right_fork = (i + 1) % table->num_philo;
		philo[i].eat_count = 0;
		philo[i].last_eat_time = 0;
		philo[i].status = IDLE;
		pthread_mutex_init(&philo[i].left_fork_m, NULL);
		pthread_mutex_init(&philo[i].right_fork_m, NULL);
		//pthread_mutex_init(&philos[i].mut_nb_meals_had, NULL);
		pthread_mutex_init(&philo[i].status_m, NULL);
		pthread_mutex_init(&philo[i].last_eat_time_m, NULL);
		//i++;
	}
	return(0);
} 

int main(int argc, char **argv)
{
	//check input funcction : less than 5 , more than 6, is not digit or number
	if(check_input(argc, argv) != 0)
	{
		write(2, "Error: Invalid input\n", 21);
		return (WRONG_INPUT);
	}
	if(init_data(argc, argv) != 0)
	{
		write(2, "Error: Failed to initialize philosopher\n", 40);
		return (MALLOC_ERROR);
	}
	return (0);
}
