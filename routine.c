#include "philo.h"

int ft_death(t_table *table)
{
    t_philo *philo;
    time_t current_time = get_time();
    if((current_time - philo ->last_eat_time) > table ->time_to_die)
    {
        if(philo ->status == 0)
        {
            philo ->status = 3;
            //funcion para imprimir status
            return(1);
        }
    }
    return(0);
}

static int get_nb_philos(t_table *table)
{
    return table->num_philo;
}

void *philo_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;

    while (1)
    {
        printf("Philosopher %d is thinking\n", philo->id);
        // Simulate thinking
        usleep(philo->table->time_to_sleep * 1000);

        printf("Philosopher %d is hungry\n", philo->id);
        // Take forks (mutex lock)
        pthread_mutex_lock(&philo->left_fork_m);
        pthread_mutex_lock(&philo->right_fork_m);

        printf("Philosopher %d is eating\n", philo->id);
        // Simulate eating
        philo->last_eat_time = get_time(); // Implement this function
        philo->eat_count++;
        usleep(philo->table->time_to_eat * 1000);

        // Release forks (mutex unlock)
        pthread_mutex_unlock(&philo->left_fork_m);
        pthread_mutex_unlock(&philo->right_fork_m);

        printf("Philosopher %d is sleeping\n", philo->id);
        // Simulate sleeping
        usleep(philo->table->time_to_sleep * 1000);
    }
    return NULL;
}

int create_threads(t_table *table)
{
    int i;
    int nb_philo;

    nb_philo = get_nb_philos(table);
    i = 0;
    table ->start_time = get_time();
    while (i < table->num_philo)
    {
        if (pthread_create(&table->philo[i].thread, NULL, &philo_routine, &table->philo[i]) != 0)
        {
            write(2, "Error: Failed to create thread\n", 31);
            return (1);
        }
        i++;
    }
    return (0);
}