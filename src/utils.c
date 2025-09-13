/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarcas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:46:29 by rmarcas-          #+#    #+#             */
/*   Updated: 2025/05/20 11:10:31 by rmarcas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

void	error_exit(const char *error)
{
	printf(RED" %s \n"RESET, error);
	exit(EXIT_FAILURE);
}

int	check_dead(t_table *table, int i)
{
	long long	current_time;

	safe_mutex_handle(&table->status_m, LOCK);
	current_time = get_time();
	if ((current_time - table-> philo[i].last_eat_time) > table ->time_to_die)
	{
		table ->stop_time = 1;
		safe_mutex_handle(&table->status_m, UNLOCK);
		safe_mutex_handle(&table->write_lock, LOCK);
		printf(RED "%lld %d died\n" RESET, \
				current_time - table->start_time, table->philo[i].id);
		safe_mutex_handle(&table->write_lock, UNLOCK);
		return (1);
	}
	safe_mutex_handle(&table->status_m, UNLOCK);
	return (0);
}

long long	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	check_stop(t_table *table)
{
	int	result;

	pthread_mutex_lock(&table->status_m);
	result = table->stop_time;
	pthread_mutex_unlock(&table->status_m);
	return (result);
}

void	precise_usleep(int time)
{
	long	start_time;

	start_time = get_time();
	while (get_time() - start_time < time)
		usleep(100);
}
