/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarcas- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 16:52:13 by rmarcas-          #+#    #+#             */
/*   Updated: 2025/04/28 16:52:16 by rmarcas-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#ifndef PHILO
# define PHILO 65536
# define WRONG_INPUT 1
# define MALLOC_ERROR 2
#endif

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>

typedef enum status_p
{
	EATING = 0,
	SLEEPING = 1,
	THINKING = 2,
	DEAD = 3,
	FULL = 4,
	IDLE = 5,
}	t_status;

typedef struct s_philo
{
	int	id;
	int	left_fork;
	int	right_fork;
	int	eat_count;
	long	last_eat_time;
	struct s_table *table; //check this
	pthread_t	thread;
	pthread_mutex_t	left_fork_m;
	pthread_mutex_t	right_fork_m;
	pthread_mutex_t	status_m;
	pthread_mutex_t	last_eat_time_m; //nose para q lo necesito , en caso el monitor lo use
	t_status	status;
}	t_philo;
typedef struct s_table
{
	int	num_philo;
	time_t	time_to_die;
	time_t	time_to_eat;
	time_t	time_to_sleep;
	int	must_eat;
	time_t	start_time;
	t_philo	*philo;
	bool keep_iter;
	//pthread_mutex_t	*fork_lock;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	keep_iter_m;
	pthread_t monitor_t;
	/*int	dead_flag;
	int	eat_count_flag;*/
}	t_table;

int	ft_atoi(char *str);
int	is_digit(int argc, char **argv);
int	init_struct(t_table *table, int argc , char **argv);
int	init_data(int argc, char **argv);
int	check_input(int argc, char **argv);
int	init_philo(t_table *table);
int ft_death(t_philo *philo);
time_t get_time(void);
int init_struct(t_table *table, int argc , char **argv);
int init_data(int argc, char **argv);
int create_threads(t_table *table);
void *philo_routine(void *arg);
void *monitor_routine(void *arg);
int get_nb_philos(t_table *table);
#endif
