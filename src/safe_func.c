#include "../includes/philo.h"

void	*safe_malloc(size_t bytes)
{
	void *ptr;

	ptr = malloc(bytes);
	if (ptr == NULL)
	{
		error_exit("Error: Memory allocation failed\n");
		exit(MALLOC_ERROR);
	}
	return (ptr);
}

static void	handle_mutex_error(int status, t_opcode opcode)
{
	if (status != 0)
	{
		if (opcode == LOCK)
			error_exit("Error: Failed to lock mutex\n");
		else if (EINVAL == status && (LOCK == opcode || opcode == UNLOCK))
			error_exit("Error: Invalid mutex operation\n");
		else if (EINVAL == status && opcode == INIT)
			error_exit("Error: Failed to initialize mutex\n");
		else if (EDEADLK == status)
			error_exit("Error: Failed to destroy mutex\n");
		else if (EPERM == status)
			error_exit("Error: Failed to unlock mutex\n");
		else if (ENOMEM == status)
			error_exit("Error: Insufficient memory for mutex\n");
		else if (EBUSY == status)
			error_exit("Error: Mutex is already locked\n");

		exit(MALLOC_ERROR);
	}
}
void	safe_mutex_handle(t_mtx *mutex, t_opcode opcode)
{
	if(LOCK == opcode)
		handle_mutex_error(pthread_mutex_lock(mutex), opcode);
	else if(UNLOCK == opcode)
		handle_mutex_error(pthread_mutex_unlock(mutex), opcode);
	else if(INIT == opcode)
		handle_mutex_error(pthread_mutex_init(mutex, NULL), opcode);
	else if(DESTROY == opcode)
		handle_mutex_error(pthread_mutex_destroy(mutex), opcode);
	else if(DETACH == opcode)
		error_exit("Error: Failed to detach thread\n");
}



static void	handle_thread_error(int status, t_opcode opcode)
{
	if (status == 0)
		return;
	if (EAGAIN == status)
		error_exit("Error: Failed to create thread\n");
	else if (EINVAL == status && opcode == CREATE)
		error_exit("Error: Invalid thread attributes\n");
	else if (EINVAL == status && (opcode == JOIN || opcode == DETACH)) 
		error_exit("Error: Invalid thread attributes\n");
	else if (ESRCH == status) 
		error_exit("Error: No thread with the specified ID\n");
	else if (EDEADLK == status)
		error_exit("Error: Deadlock detected\n");
	else if (EPERM == status)
		error_exit("Error: No permission to join thread\n");
}

void	safe_thread_handle(pthread_t *thread, void *(*foo)(void *), void *table, t_opcode opcode)
{
	if (CREATE == opcode)
		handle_thread_error(pthread_create(thread, NULL, foo, table), opcode);
	else if (JOIN == opcode)
		handle_thread_error(pthread_join(*thread, NULL), opcode);
	else if (DETACH == opcode)
		handle_thread_error(pthread_detach(*thread), opcode);
	else
		error_exit("Error: Invalid thread operation\n");

}


