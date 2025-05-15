#include "../includes/philo.h"

void destroy_mutex(t_table *table)
{
	int i;

	i = 0;
	while (i < table->num_philo)
	{
		safe_mutex_handle(&table->forks[i], DESTROY);
		i++;
	}
	safe_mutex_handle(&table->write_lock, DESTROY);
	safe_mutex_handle(&table->status_m, DESTROY);
	free(table->philo);
	free(table->forks);
}
int init_struct(t_table *table, int argc , char **argv)
{
	table->num_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if(argc == 6)
		table->must_eat = ft_atoi(argv[5]);
	else
		table->must_eat = -1;
	return (0);
}

int init_struct_data(t_table *table)
{
	table->philo = safe_malloc(sizeof(t_philo) * table->num_philo);
	table->forks = safe_malloc(sizeof(pthread_mutex_t) * table->num_philo);
	table->start_time = get_time();
	table->stop_time = 0;
	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->status_m, NULL);
	return (0);
}

