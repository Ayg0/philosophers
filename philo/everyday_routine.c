/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   everyday_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 14:31:36 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/05/16 07:28:25 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	get_forks(t_data *data, int num, int l_fork, int r_fork)
{
	if (pthread_mutex_lock(&data->philo.forks[l_fork - 1]))
	{
		ft_display(2, "Error ! Lock or Unlock mutex Failure .\n");
		return (-5);
	}
	print_info(get_time() - data->times.start_time, num,
		"has taking a fork", data);
	while (l_fork == r_fork && data->maid.state_of_prog)
		;
	if ((l_fork != r_fork) && pthread_mutex_lock(
			&data->philo.forks[r_fork - 1]))
	{
		ft_display(2, "Error ! Lock or Unlock mutex Failure .\n");
		return (-5);
	}
	print_info(get_time() - data->times.start_time, num,
		"has taking a fork", data);
	return (0);
}

int	put_forks(t_data *data, int l_fork, int r_fork)
{
	if (pthread_mutex_unlock(&data->philo.forks[r_fork - 1]))
	{
		ft_display(2, "Error ! Lock or Unlock mutex Failure .\n");
		return (-5);
	}
	if (pthread_mutex_unlock(&data->philo.forks[l_fork - 1]))
	{
		ft_display(2, "Error ! Lock or Unlock mutex Failure .\n");
		return (-5);
	}
	return (0);
}

int	eat(t_data *data, int num, int l_fork, int r_fork)
{
	if (!data->maid.state_of_prog)
		return (1);
	if (get_forks(data, num, l_fork, r_fork))
		return (-5);
	print_info(get_time() - data->times.start_time, num,
		"is eating", data);
	data->times.last_eat[num - 1] = get_time();
	data->maid.num_to_eat[num - 1]++;
	ft_sleep(data->times.time_to_eat, data);
	if (put_forks(data, l_fork, r_fork))
		return (-5);
	return (0);
}

int	go_sleep(t_data *data, int num)
{
	if (!data->maid.state_of_prog)
		return (1);
	print_info(get_time() - data->times.start_time, num,
		"is sleeping", data);
	ft_sleep(data->times.time_to_sleep, data);
	return (0);
}

int	think(t_data *data, int num)
{
	if (!data->maid.state_of_prog)
		return (1);
	print_info(get_time() - data->times.start_time, num,
		"is thinking", data);
	return (0);
}
