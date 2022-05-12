/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:28:03 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/05/12 13:25:46 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_locks(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo.max_num)
		pthread_mutex_init(&data->philo.forks[i], NULL);
	return (0);
}

int	init_num(t_data *data, char **av, int *flag)
{
	data->philo.max_num = ft_atoi(av[1], flag);
	data->times.time_to_die = ft_atoi(av[2], flag);
	data->times.time_to_eat = ft_atoi(av[3], flag);
	data->times.time_to_sleep = ft_atoi(av[4], flag);
	if (av[5])
		data->philo.max_eat = ft_atoi(av[5], flag);
	return (*flag);
}

int	init_data(t_data *data, char **av, int *flag)
{
	int	i;
	data->times.start_time = 0;
	if (init_num(data, av, flag) == -2)
		return (*flag);
	data->philo.philos = (pthread_t *)ft_calloc(data->philo.max_num, sizeof(pthread_t));
	data->times.deadline = (ulg *)ft_calloc(data->philo.max_num, sizeof(ulg));
	data->maid.num_to_eat = (int *)ft_calloc(data->philo.max_num, sizeof(int));
	data->philo.forks = (pthread_mutex_t *)ft_calloc(data->philo.max_num, sizeof(pthread_mutex_t));
	data->maid.maid = (pthread_t *)ft_calloc(1, sizeof(pthread_t));
	data->maid.state_of_prog = 1;
	init_locks(data);
	//printf("%lu\n", get_time());
	i = -1;
	while (++i < data->philo.max_num)
		data->times.deadline[i] = get_time();
	data->stat_of_num = 0;
	return (0);
}

int get_forks(t_data *data,int num, int l_fork, int r_fork)
{
	(void) num;
	pthread_mutex_lock(&data->philo.forks[l_fork - 1]);
	print_info(get_time() - data->times.start_time, num, "has taking a fork", data->maid.state_of_prog);
	while(l_fork == r_fork && data->maid.state_of_prog);
	(l_fork != r_fork) && pthread_mutex_lock(&data->philo.forks[r_fork - 1]);
	print_info(get_time() - data->times.start_time, num, "has taking a fork", data->maid.state_of_prog);
	return (0);
}

int put_forks(t_data *data, int l_fork, int r_fork)
{
	pthread_mutex_unlock(&data->philo.forks[r_fork - 1]);
	pthread_mutex_unlock(&data->philo.forks[l_fork - 1]);
	return (0);
}

int eat(t_data *data,int num, int l_fork, int r_fork)
{
	if (!data->maid.state_of_prog)
		return (1);
	get_forks(data, num, l_fork, r_fork);
	print_info(get_time() - data->times.start_time, num, "is eating", data->maid.state_of_prog);
	data->times.deadline[num - 1] = get_time();
	data->maid.num_to_eat[num - 1]++;
	ft_sleep(data->times.time_to_eat);
	put_forks(data, l_fork, r_fork);
	return (0);
}

int go_sleep(t_data *data, int num)
{
	if (!data->maid.state_of_prog)
		return (1);
  	print_info(get_time() - data->times.start_time, num, "is sleeping", data->maid.state_of_prog);
  	ft_sleep(data->times.time_to_sleep);
  	return (0);
}

int think(t_data *data, int num)
{
	if (!data->maid.state_of_prog)
		return (1);
  	print_info(get_time() - data->times.start_time, num, "is thinking", data->maid.state_of_prog);
  	return (0);
}

int	life(t_data *data)
{
	int	num;
	int	forks[2];

	/*
		- get_info
		- eat
		- sleep
		- think
	*/
	num = data->updated_num;
	data->stat_of_num = 1;
	forks[0] = ((num == 1) * data->philo.max_num) + ((num != 1) * (num - 1));
	forks[1] = num;
	while(data->maid.state_of_prog)
	{
		eat(data, num, forks[0], forks[1]);
  		go_sleep(data, num);
  		think(data, num);
	}
	return (0);
}

int	create_threads(t_data *data)
{
	data->times.start_time = get_time();
	data->updated_num = 1;
	while(data->updated_num <= data->philo.max_num)
	{
		pthread_create(&data->philo.philos[data->updated_num - 1], NULL, (void *) life, data);
		while(data->stat_of_num == 0);
		data->stat_of_num = 0;
		data->updated_num += 2;
	}
	ft_sleep(100);
	data->updated_num = 2;
	while(data->updated_num <= data->philo.max_num)
	{
		pthread_create(&data->philo.philos[data->updated_num - 1], NULL, (void *) life, data);
		while(data->stat_of_num == 0);
		data->stat_of_num = 0;
		data->updated_num += 2;
	}
	pthread_create(data->maid.maid, NULL, (void *) take_care, data);
	return (0);
}

int	join_threads(t_data *data)
{
  int i;

	i = -1;
	while(++i < data->philo.max_num)
		pthread_join(data->philo.philos[i], NULL);
	pthread_join(*data->maid.maid, NULL);
	return (0);
}

int	clear_data(t_data *data, int e_flag)
{
	int	i;

	i = -1;
	(void) e_flag;
	while (++i < data->philo.max_num)
		pthread_mutex_destroy(&data->philo.forks[i]);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		e_flag;

	e_flag = 0;
	data = ft_calloc(1 , sizeof(t_data));
	/*
		- init data.
		- create threads.
		- join threads.
		- clear data.
	*/
	if (ac != 5 && ac != 6)
		return (write(2, "Error, Wrong number of arguments !\n", 36));
	if (ac == 6)
		data->maid.flag = 1;
	if (init_data(data, av, &e_flag))
		return (write(2, "Error, bad parameters !\n", 24));
	!e_flag && create_threads(data);
	!e_flag && join_threads(data);
	clear_data(data, e_flag);
}
