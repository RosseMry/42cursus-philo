#include "philo.h"

static void	set_keep_iterating(t_table *table, bool set_to)
{
	pthread_mutex_lock(&table->keep_iter_m);
	table->keep_iter = set_to;
	pthread_mutex_unlock(&table->keep_iter_m);
}

static bool keep_iter(t_table *table)
{
    bool result;
    pthread_mutex_lock(&table->keep_iter_m);
    result = table->keep_iter;
    pthread_mutex_unlock(&table->keep_iter_m);
    return (result);
}

void *monitor_routine(void *arg)
{
    t_table *table = (t_table *)arg;
    t_philo *philo = table->philo;
    int i;
    int nb_philo;
    int all_full;

    nb_philo = get_nb_philos(table);
    i = -1;
    while (++i < nb_philo && keep_iter(table))
    {
        printf("Monitor: Checking philosopher %d\n", table->philo[i].id);
        if (ft_death(&philo[i]) && keep_iter(table))
        {
                pthread_mutex_lock(&table->write_lock);
                printf("Philosopher %d has died\n", table->philo[i].id);
                pthread_mutex_unlock(&table->write_lock);
                set_keep_iterating(table, false); // Cambia el estado de iteracion
                //liberar a los demas philos como muertos
                return NULL; // Termina el monitor
        }
        if (i == nb_philo - 1)
            i = -1;
        usleep(1000); // Evita un bucle ocupado
    }
    return NULL;
}