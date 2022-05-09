/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   takingcare.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 11:29:19 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/05/09 13:44:43 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int take_care(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo.max_num)
	{
		if (!data->times.deadline[i])
			data->times.deadline[i] = get_time();
	}
	while (data->maid.state_of_prog)
	{
		i = -1;
		while (++i < data->philo.max_num && data->maid.state_of_prog)
		{	
			if ((get_time() - data->times.deadline[i]) > data->times.time_to_die)
			{
				data->maid.state_of_prog = 0;
				print_info(get_time() - data->times.start_time, i + 1, "died", 1);
			}
			if (data->maid.flag && all_ate(data))
				data->maid.state_of_prog = 0;
		}
	}
	return (0);
}

int	all_ate(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo.max_num)
	{
		if (data->maid.num_to_eat[i] != data->philo.max_eat)
			break;
	}
	return (i == data->philo.max_num);
}