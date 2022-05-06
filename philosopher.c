/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:28:03 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/05/06 11:03:17 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_data(t_data *data, char **av)
{
	data->philo.max_num = ft_atoi(av[1]);
	data->philo.philos = (pthread_t *)ft_calloc(data->philo.max_num, sizeof(pthread_t));
	data->philo.forks = (int *)ft_calloc(data->philo.max_num, sizeof(int));
	data->maid.maid = (pthread_t *)ft_calloc(1, sizeof(pthread_t));
	data->maid.state_of_prog = 1;
	pthread_mutex_init(&data->lock, NULL);
	data->times.time_to_die = ft_atoi(av[2]);
	data->times.time_to_eat = ft_atoi(av[3]);
	data->times.time_to_sleep = ft_atoi(av[4]);
	data->updated_num = 1;
	data->stat_of_num = 0;
	return (0);
}

int	check_forks(t_data *data, int l_fork, int r_fork)
{
	if (data->philo.forks[l_fork] == 0 && data->philo.forks[r_fork] == 0)
	{
		data->philo.forks[l_fork] = 1;
		data->philo.forks[r_fork] = 1;
		return (0);
	}
	return (1);
}

ulg get_time()
{
  struct timeval tv;

  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int print_info(ulg time, int num, char *s)
{
  printf("%lu %d %s\n", time, num, s);
  return (0);
}

int eat(t_data *data,int num, int l_fork, int r_fork)
{
  print_info(get_time(), num, "has taking a fork");
  print_info(get_time(), num, "has taking a fork");
  print_info(get_time(), num, "is eating");
  usleep(data->times.time_to_eat * 1000);
  data->philo.forks[l_fork] = 0;
  data->philo.forks[r_fork] = 0;
  return (0);
}

int go_sleep(t_data *data, int num)
{
  print_info(get_time(), num, "is sleeping");
  usleep(data->times.time_to_sleep);
  return (0);
}

int think(int num)
{
  print_info(get_time(), num, "is thinking");
  return (0);
}

int	life(t_data *data)
{
	int	num;
	int	can_eat;
	int	forks[2];

	/*
		- get_info
		- eat
		- sleep
		- think
	*/
	int d = 0;
	num = data->updated_num;
	data->stat_of_num = 1;
    forks[0] = ((num == 1) * data->philo.max_num) + ((num != 1) * (num - 1));
    forks[1] = ((num == data->philo.max_num) * 1) + ((num != data->philo.max_num) * num);
	//while(data->updated_num != -1);
	while(data->maid.state_of_prog == 1)
	{
		can_eat = 0;
		while(!can_eat)
		{
			pthread_mutex_lock(&data->lock);
			can_eat = !check_forks(data, forks[0], forks[1]);
			pthread_mutex_unlock(&data->lock);
		}
		eat(data, num, forks[0], forks[1]);
  		go_sleep(data, num);
  		think(num);
		if (++d == 15)
			data->maid.state_of_prog = 0;
	}
	return (0);
}

int	create_threads(t_data *data)
{
	while(data->updated_num < data->philo.max_num + 1)
	{
		pthread_create(&data->philo.philos[data->updated_num - 1], NULL, (void *) life, data);
		while(data->stat_of_num == 0);
		data->stat_of_num = 0;
		data->updated_num++;
	}
	//pthread_create(data->maid.maid, NULL, (void *) take_care, data);
	data->updated_num = -1;
	return (0);
}

int	join_threads(t_data *data)
{
  while(++data->updated_num < data->philo.max_num)
    pthread_join(data->philo.philos[data->updated_num], NULL);
	return (0);
}

int	clear_data()
{
	
	return (0);
}

int	main(int ac, char **av)
{
	t_data	data;
	/*
		- init data.
		- create threads.
		- join threads.
		- clear data.
	*/
  	(void)ac;
	init_data(&data, av);
	create_threads(&data);
	join_threads(&data);
	clear_data();
}
