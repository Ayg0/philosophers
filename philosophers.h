/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:29:43 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/05/09 13:38:56 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

/*
	- each philo
	- timing
	- maid
	- all
*/

typedef	unsigned long	ulg;

typedef struct s_timing
{
	ulg		start_time;
	ulg		time_to_eat;
	ulg		time_to_die;
	ulg		time_to_sleep;
	ulg		*deadline;
}	t_timing;

typedef struct s_maid
{
	int			state_of_prog;
	pthread_t	*maid;
	int			flag;
	int			*num_to_eat;
}	t_maid;

typedef struct s_philosopher
{
	pthread_t		*philos;
	pthread_mutex_t	*forks;
	int				max_num;
	int				max_eat;	
}	t_philo;

typedef struct s_data
{
	t_maid			maid;
	t_philo			philo;
	t_timing		times;
	int				stat_of_num;
	int				updated_num;
	pthread_mutex_t	lock;
}	t_data;



int     ft_atoi(const char *str, int *flag);
void    *ft_calloc(size_t count, size_t size);
ulg		get_time();
int		ft_sleep(ulg time);
int 	take_care(t_data *data);
int 	print_info(int time, int num, char *s, int status);
int 	take_care(t_data *data);
int		all_ate(t_data *data);
#endif
