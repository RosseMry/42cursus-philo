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
	table->time_to_die = (time_t)ft_atoi(argv[2]);
	table->time_to_eat = (time_t)ft_atoi(argv[3]);
	table->time_to_sleep = (time_t)ft_atoi(argv[4]);
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

int init_data(int argc, char **argv)
{
	t_table  table;

	if(init_struct(&table, argc, argv) != 0)
	{
		write(2, "Error: Failed to initialize philosopher\n", 40);
		return (MALLOC_ERROR);
	}
	init_philo(&table);
	/*
	inicializar cada filosofo por id y el id menor a la cantidad de filosofos
	init_fork(); recordar invocar filosofo y rellenar el tenedor de derecha y el de izquierda iniciar mutex
	etc...
	*/
	return (0);

}