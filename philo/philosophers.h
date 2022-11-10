/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:29:43 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/05/16 11:20:22 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <sys/time.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>

typedef unsigned long	t_ulg;

typedef struct s_timing
{
	t_ulg		start_time;
	t_ulg		time_to_eat;
	t_ulg		time_to_die;
	t_ulg		time_to_sleep;
	t_ulg		*last_eat;
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
	pthread_mutex_t	*lock_message;
}	t_data;

int		ft_atoi(const char *str, int *flag);
void	*ft_calloc(size_t count, size_t size);
t_ulg	get_time(void);
int		ft_sleep(t_ulg time, t_data *data);
int		take_care(t_data *data);
int		print_info(int time, int num, char *s, t_data *data);
int		take_care(t_data *data);
int		all_ate(t_data *data);
int		get_forks(t_data *data, int num, int l_fork, int r_fork);
int		put_forks(t_data *data, int l_fork, int r_fork);
int		eat(t_data *data, int num, int l_fork, int r_fork);
int		go_sleep(t_data *data, int num);
int		think(t_data *data, int num);
int		init_locks(t_data *data, int *e_flag);
int		init_num(t_data *data, char **av, int *flag);
int		ft_display(int fd, char *ms);
int		init_data(t_data *data, char **av, int *flag);
int		print_error(int err_num);
#endif
