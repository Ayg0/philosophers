/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:33:13 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/05/16 11:25:09 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_locks(t_data *data, int *e_flag)
{
	int	i;

	i = -1;
	while (++i < data->philo.max_num)
	{
		if (pthread_mutex_init(&data->philo.forks[i], NULL))
			return (*e_flag = 4);
	}
	data->lock_message = (pthread_mutex_t *)ft_calloc(1,
			sizeof(pthread_mutex_t));
	if (!data->lock_message)
		return (-1);
	if (pthread_mutex_init(data->lock_message, NULL))
		return (*e_flag = 4);
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

int	init_last_eat(t_data *data)
{
	int	i;

	i = -1;
	data->maid.state_of_prog = 1;
	data->times.start_time = 0;
	while (++i < data->philo.max_num)
		data->times.last_eat[i] = get_time();
	data->stat_of_num = 0;
	return (0);
}

int	init_data(t_data *data, char **av, int *flag)
{
	if (init_num(data, av, flag) == -1)
		return (*flag);
	data->philo.philos = (pthread_t *)ft_calloc(data->philo.max_num,
			sizeof(pthread_t));
	if (!data->philo.philos)
		return (-2);
	data->times.last_eat = (t_ulg *)ft_calloc(data->philo.max_num,
			sizeof(t_ulg));
	if (!data->times.last_eat)
		return (-2);
	data->maid.num_to_eat = (int *)ft_calloc(data->philo.max_num,
			sizeof(int));
	if (!data->maid.num_to_eat)
		return (-2);
	data->philo.forks = (pthread_mutex_t *)ft_calloc(data->philo.max_num,
			sizeof(pthread_mutex_t));
	if (!data->philo.forks)
		return (-2);
	data->maid.maid = (pthread_t *)ft_calloc(1, sizeof(pthread_t));
	if (!data->maid.maid)
		return (-2);
	init_locks(data, flag);
	init_last_eat(data);
	return (*flag);
}
