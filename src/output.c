/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarcas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 09:26:03 by rmarcas-          #+#    #+#             */
/*   Updated: 2025/05/20 11:43:40 by rmarcas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/philo.h"

void	write_status(t_philo *philo, t_status status)
{
	safe_mutex_handle(&philo->table->write_lock, LOCK);
	if (!check_stop(philo ->table))
	{
		if (status == EATING)
			printf(GREEN "%lld %d is eating\n" RESET, \
					get_time() - philo ->table->start_time, philo->id);
		else if (status == SLEEPING)
			printf(CYAN "%lld %d is sleeping\n" RESET, \
					get_time() - philo ->table->start_time, philo->id);
		else if (status == THINKING)
			printf(CYAN "%lld %d is thinking\n" RESET, \
					get_time() - philo ->table->start_time, philo->id);
		else if (status == DEAD)
			printf(RED "%lld %d died\n" RESET, \
					get_time() - philo ->table->start_time, philo->id);
		else if (status == TAKEN_FORK)
			printf(MAGENTA "%lld %d has taken a fork\n" RESET, \
					get_time() - philo ->table->start_time, philo->id);
	}
	safe_mutex_handle(&philo->table->write_lock, UNLOCK);
}
