/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:28:03 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/05/16 11:21:22 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	life(t_data *data)
{
	int	num;
	int	err;
	int	forks[2];

	num = data->updated_num;
	data->stat_of_num = 1;
	forks[0] = ((num == 1) * data->philo.max_num) + ((num != 1) * (num - 1));
	forks[1] = num;
	err = 0;
	while (data->maid.state_of_prog && !err)
	{
		err = eat(data, num, forks[0], forks[1]);
		!err && go_sleep(data, num);
		!err && think(data, num);
		if (err)
			return (err);
	}
	return (0);
}

int	launch_thread(t_data *data)
{
	while (data->updated_num <= data->philo.max_num)
	{
		if (pthread_create(&data->philo.philos[data->updated_num - 1],
				NULL, (void *) life, data))
			return (-3);
		while (data->stat_of_num == 0)
			;
		data->stat_of_num = 0;
		data->updated_num += 2;
	}
	return (0);
}

int	create_threads(t_data *data)
{
	data->times.start_time = get_time();
	data->updated_num = 1;
	launch_thread(data);
	usleep(100);
	data->updated_num = 2;
	launch_thread(data);
	if (pthread_create(data->maid.maid, NULL, (void *) take_care, data))
		return (-3);
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo.max_num)
		pthread_join(data->philo.philos[i], NULL);
		i = -1;
	pthread_join(*data->maid.maid, NULL);
	while (++i < data->philo.max_num)
		pthread_mutex_destroy(&data->philo.forks[i]);
	pthread_mutex_destroy(data->lock_message);
	return (0);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		e_flag;

	e_flag = 0;
	data = ft_calloc(1, sizeof(t_data));
	if (ac != 5 && ac != 6)
		return (write(2, "Error, Wrong number of arguments !\n", 36));
	if (ac == 6)
		data->maid.flag = 1;
	print_error(init_data(data, av, &e_flag));
	print_error(!e_flag && create_threads(data));
	print_error(!e_flag && join_threads(data));
	return (0);
}
