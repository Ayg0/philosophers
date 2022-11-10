/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   takingcare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:29:19 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/05/16 11:23:49 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	take_care(t_data *data)
{
	int		i;
	t_ulg	tmp;
	t_ulg	tmp2;

	i = -1;
	while (data->maid.state_of_prog)
	{
		i = -1;
		while (++i < data->philo.max_num && data->maid.state_of_prog)
		{	
			tmp2 = data->times.last_eat[i];
			tmp = get_time();
			if (tmp - tmp2 > data->times.time_to_die)
			{
				print_info(get_time() - data->times.start_time,
					i + 1, "died", data);
				data->maid.state_of_prog = 0;
			}
			if (data->maid.flag && all_ate(data))
				data->maid.state_of_prog = 0;
		}
		usleep(500);
	}
	return (0);
}

int	all_ate(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo.max_num)
	{
		if (data->maid.num_to_eat[i] < data->philo.max_eat)
			break ;
	}
	return (i == data->philo.max_num);
}

int	ft_display(int fd, char *ms)
{
	int	i;

	i = 0;
	while (ms[i++])
		;
	write(fd, ms, --i);
	return (1);
}

int	print_error(int err_num)
{
	if (err_num == -1)
		return (ft_display(2,
				"Error ! Wrong Values Were Passed As Arguments.\n"));
	if (err_num == -2)
		return (ft_display(2, "Error ! Allocation Failure.\n"));
	if (err_num == -3)
		return (ft_display(2, "Error ! Thread Creation Failure.\n"));
	if (err_num == 4)
		return (ft_display(2, "Error ! Mutex Initialization Failure.\n"));
	return (0);
}
