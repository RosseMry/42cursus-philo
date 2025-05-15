#ifndef PHILO_H
# define PHILO_H

# define WRONG_INPUT 1
# define MALLOC_ERROR 2
# define RESET			"\033[0m"
# define BLACK			"\033[30m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define YELLOW			"\033[33m"
# define BLUE			"\033[34m"
# define MAGENTA		"\033[35m"
# define CYAN			"\033[36m"
# define WHITE			"\033[37m"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <string.h>
# include <limits.h>
# include <stdbool.h>
#include <errno.h>

typedef pthread_mutex_t t_mtx;

typedef enum status_p
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	FULL,
	TAKEN_FORK,
}	t_status;

typedef enum opcode
{
	LOCK,
	UNLOCK,
	INIT,
	DESTROY,
	CREATE,
	JOIN,
	DETACH,
}	t_opcode;

typedef struct s_philo
{
	int	id;
	int	eat_count;
	long	last_eat_time;
	pthread_t	thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	struct s_table	*table;
}	t_philo;
typedef struct s_table
{
	int	num_philo;
    int	must_eat;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	long	start_time;
	int	stop_time;
    t_philo	*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
    pthread_mutex_t	status_m;
	pthread_t monitor_t;
}	t_table;

void	error_exit(const char *error);
void	destroy_mutex(t_table *table);
int	init_struct(t_table *table, int argc , char **argv);
int	init_struct_data(t_table *table);
int	init_philo_data(t_table *table);
int	ft_simulation(int argc, char **argv);
int	main(int argc, char **argv);
void	*monitor_routine(void *arg);
int	create_monitor_thread(t_table *table, pthread_t *monitor);
int	create_threads(t_table *table);
int	ft_atoi(char *str);
int	is_digit(int argc, char **argv);
int	check_input(int argc, char **argv);
void	wait_philo(t_table *table);
void	*philosopher_routine(void *arg);
int	create_philosopher_thread(t_table *table);
int	init_philo(t_table *table);
void	*safe_malloc(size_t bytes);
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode);
void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *table, t_opcode opcode);
long long	get_time(void);
int	check_stop(t_table *table);
void	precise_usleep(int time);
int check_dead(t_table *table, int i);
int get_nb_philos(t_table *table);
int all_eat(t_table *table);
void eat(t_philo *philo);
void write_status(t_philo *philo, t_status status);
void lonely_philo(t_philo *philo);
#endif