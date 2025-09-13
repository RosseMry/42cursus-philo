/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarcas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 08:59:28 by rmarcas-          #+#    #+#             */
/*   Updated: 2025/05/20 11:17:09 by rmarcas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

int	all_eat(t_table *table)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (table->must_eat <= 0 || check_stop(table))
		return (0);
	safe_mutex_handle(&table->status_m, LOCK);
	while (i < table->num_philo)
	{
		if (table->philo[i].eat_count >= table->must_eat)
			count++;
		i++;
	}
	if (count == table->num_philo)
	{
		table->stop_time = 1;
		safe_mutex_handle(&table->status_m, UNLOCK);
		return (1);
	}
	safe_mutex_handle(&table->status_m, UNLOCK);
	return (0);
}

void	take_forks(t_philo *philo)
{
	if (philo ->id % 2 == 0)
	{
		safe_mutex_handle(philo->right_fork, LOCK);
		write_status(philo, TAKEN_FORK);
		safe_mutex_handle(philo->left_fork, LOCK);
		write_status(philo, TAKEN_FORK);
	}
	else
	{
		safe_mutex_handle(philo->left_fork, LOCK);
		write_status(philo, TAKEN_FORK);
		safe_mutex_handle(philo->right_fork, LOCK);
		write_status(philo, TAKEN_FORK);
	}
	safe_mutex_handle(&philo->table ->status_m, LOCK);
	philo ->last_eat_time = get_time();
	philo ->eat_count++;
	safe_mutex_handle(&philo->table ->status_m, UNLOCK);
}

void	eat(t_philo *philo)
{
	long long	current_time;

	take_forks(philo);
	current_time = get_time();
	write_status(philo, EATING);
	precise_usleep(philo->table->time_to_eat);
	if (philo->id % 2 == 0)
	{
		safe_mutex_handle(philo->right_fork, UNLOCK);
		safe_mutex_handle(philo->left_fork, UNLOCK);
	}
	else
	{
		safe_mutex_handle(philo->left_fork, UNLOCK);
		safe_mutex_handle(philo->right_fork, UNLOCK);
	}
}
