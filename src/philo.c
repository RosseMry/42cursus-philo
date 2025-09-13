/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarcas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 11:36:28 by rmarcas-          #+#    #+#             */
/*   Updated: 2025/05/20 11:41:04 by rmarcas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

void	lonely_philo(t_philo *philo)
{
	safe_mutex_handle(philo->left_fork, LOCK);
	write_status(philo, TAKEN_FORK);
	usleep(philo->table->time_to_die * 1000);
	safe_mutex_handle(philo->left_fork, UNLOCK);
}

void	wait_philo(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		safe_thread_handle(&table ->philo[i].thread, NULL, NULL, JOIN);
		i++;
	}
	safe_thread_handle(&table ->monitor_t, NULL, NULL, JOIN);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo ->table ->num_philo == 1)
	{
		lonely_philo(philo);
		return (NULL);
	}
	if (philo ->id % 2 == 0)
		precise_usleep(philo ->table ->time_to_eat / 2);
	while (!check_stop(philo ->table))
	{
		eat(philo);
		if (check_stop(philo ->table))
			break ;
		write_status(philo, SLEEPING);
		precise_usleep(philo ->table ->time_to_sleep);
		if (!check_stop(philo ->table))
		{
			write_status(philo, THINKING);
			precise_usleep(1);
		}
	}
	return (NULL);
}

int	create_philosopher_thread(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_create(&table ->philo[i].thread, NULL, \
					philosopher_routine, &table ->philo[i]) != 0)
		{
			while (i >= 0)
			{
				safe_thread_handle(&table ->philo[i].thread, NULL, NULL, JOIN);
				i--;
			}
			return (1);
		}
		i++;
	}
	return (0);
}

int	init_philo_data(t_table *table)
{
	int	i;

	i = -1;
	while (++i < table->num_philo)
	{
		table ->philo[i].id = i + 1;
		table ->philo[i].left_fork = &table ->forks[i];
		table ->philo[i].right_fork = \
		&table ->forks[(i + 1) % table->num_philo];
		table ->philo[i].eat_count = 0;
		table ->philo[i].last_eat_time = table->start_time;
		table ->philo[i].table = table;
		pthread_mutex_init(&table ->forks[i], NULL);
	}
	return (0);
}
