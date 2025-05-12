#include "philo.h"

//SLEEP TIME : tiempo en milisegundos
time_t get_time(void)
{
	struct timeval tv;
	if(gettimeofday(&tv, NULL))
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

// INIT ESTRUCTURE

int init_struct(t_table *table, int argc , char **argv)
{
	table->num_philo = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	printf("time_to_sleep: %ld\n", table->time_to_sleep);
	if(argc == 6)
		table->must_eat = ft_atoi(argv[5]);
	else
		table->must_eat = -1;
	table->philo = (t_philo *)malloc(sizeof(t_philo) * table->num_philo);
	if (table->philo == NULL)
		return (MALLOC_ERROR);
	/*table->fork_lock = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * table->num_philo);
	if (table->fork_lock == NULL)
	{
		free(table->philo);
		return (1);
	}*/
	return (0);
}

//INIT PHILO

