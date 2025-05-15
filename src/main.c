#include "../includes/philo.h"

int	init_philo(t_table *table)
{
	if(init_struct_data(table) != 0)
	{
		printf(RED"Error: Failed to initialize philosopher\n");
		return (MALLOC_ERROR);
	}
	if(init_philo_data(table) != 0)
	{
		printf(RED"Error: Failed to initialize philosopher\n");
		return (MALLOC_ERROR);
	}
	return (0);
}

int	ft_simulation(int argc, char **argv)
{
	t_table  table;

	if(init_struct(&table, argc, argv) != 0)
	{
		printf(RED"Error: Failed to initialize philosopher\n");
		return (MALLOC_ERROR);
	}
	if( init_philo(&table) != 0 || create_threads(&table))
	{
		printf(RED"Error: Failed to initialize philosopher\n");
		destroy_mutex(&table);
		return (MALLOC_ERROR);
	}
	wait_philo(&table);
	destroy_mutex(&table);
	return (0);
}

int	main(int argc, char **argv)
{
	if(check_input(argc, argv) != 0)
	{
		printf(RED"Error: Invalid input\n");
		return (WRONG_INPUT);
	}
	if(ft_simulation(argc, argv) != 0)
	{
		printf(RED"Error: Failed to initialize philosopher\n");
		return (MALLOC_ERROR);
	}
	return (0);
}