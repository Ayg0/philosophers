/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 08:53:42 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/05/11 13:55:32 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

typedef unsigned long ulg;

typedef struct s_maid
{
	pthread_t	maid;
	int			*num_to_eat;
	int			state_of_prog;
}	t_maid;

typedef struct s_timing
{
	ulg	start_time;
	ulg	time_to_eat;
	ulg	time_to_die;
	ulg	time_to_sleep;
}	t_timing;

typedef struct s_data
{
	int				max_philo;
	int				max_eat;
	t_timing		times;
	t_maid			maid;
	pthread_mutex_t	*forks;
}	t_data;


typedef struct s_philosophers
{
	t_data		*data;
	pthread_t	philo;
	ulg			last_eat;
	int			num;
}	t_philo;

void    *ft_calloc(size_t count, size_t size);
int     ft_atoi(const char *str, int *flag);
int		ft_sleep(ulg time);
ulg		get_time();
int		print_info(int time, int num, char *s, int status);
#endif