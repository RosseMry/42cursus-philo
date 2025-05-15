#include "../includes/philo.h"
void	*monitor_routine(void *arg)
{
	t_table	*table;
	int	i;

	table = (t_table *)arg;
	usleep(5000);
	while (!check_stop(table))
	{
		i = 0;
		while (i < table->num_philo && !check_stop(table))
		{
			if (check_dead(table, i))
				return (NULL);
			i++;
		}
		if (table->must_eat > 0)
			all_eat(table);
		precise_usleep(1);
	}
	return (NULL);
}

int	create_monitor_thread(t_table *table, pthread_t *monitor)
{
	int i;
	if (pthread_create(monitor, NULL, monitor_routine, table) != 0)
	{
		i = table->num_philo;
		while (i >= 0)
		{
			safe_thread_handle(&table->philo[i].thread, NULL, NULL, JOIN);
			i--;
		}
		return (1);
	}
	return (0);
}
int	create_threads(t_table *table)
{
	pthread_t monitor;

	table ->start_time = get_time();
	if(create_philosopher_thread(table) != 0)
	{
		printf(RED"Error: Failed to create philosopher threads\n");
		return (MALLOC_ERROR);
	}
	if(create_monitor_thread(table, &monitor) != 0)
	{
		printf(RED"Error: Failed to create monitor thread\n");
		return (MALLOC_ERROR);
	}
	table ->monitor_t = monitor;
	while(!check_stop(table))
		precise_usleep(1);
	return (0);
	
}