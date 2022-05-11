/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 08:53:39 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/05/11 15:19:44 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


int     init_locks(t_philo *philo)
{
        int     i;

        i = 0;
        while (++i < philo->data->max_philo)
                pthread_mutex_init(&philo->data->forks[i], NULL);
        return (0);
}

int	init_data(t_philo **philo, int ac, char **av)
{
	int	flag;
	int	tmp;

	tmp = ft_atoi(av[1], &flag);
	if (tmp <= 0)
		return (write(2, "Error !\n",9));
	(*philo) = ft_calloc(tmp + 1, sizeof(t_philo));
	(*philo)->data = ft_calloc(1, sizeof(t_data));
	(*philo)->data->maid.state_of_prog = 1;
	(*philo)->data->forks = ft_calloc(tmp, sizeof(pthread_mutex_t));
	init_locks(*philo);
	(*philo)->data->maid.num_to_eat = ft_calloc(tmp, sizeof(int));
	(*philo)->data->max_eat = -1;
	(*philo)->data->max_philo = tmp;
	(*philo)->data->times.time_to_die = ft_atoi(av[2], &flag);
	(*philo)->data->times.time_to_eat = ft_atoi(av[3], &flag);
	(*philo)->data->times.time_to_sleep = ft_atoi(av[4], &flag);
	if (ac == 6)
		(*philo)->data->max_eat = ft_atoi(av[5], &flag);
	tmp = 0;
	while (++tmp < (*philo)->data->max_philo + 1)
	{
		(*philo)[tmp].data = (*philo)->data;
		(*philo)[tmp].last_eat = 0;
	}
	return (0);
}

int get_forks(t_philo *philo, int l_fork, int r_fork)
{
    pthread_mutex_lock(&philo->data->forks[l_fork]);
    print_info(get_time() - philo->data->times.start_time, philo->num, "has taking a fork", philo->data->maid.state_of_prog);
    while(l_fork == r_fork);
    pthread_mutex_lock(&philo->data->forks[r_fork]);
	print_info(get_time() - philo->data->times.start_time, philo->num, "has taking a fork", philo->data->maid.state_of_prog);
    return (0);
}

int put_forks(t_philo *philo, int l_fork, int r_fork)
{
    pthread_mutex_unlock(&philo->data->forks[l_fork]);
    pthread_mutex_unlock(&philo->data->forks[r_fork]);
    return (0);
}

int	eat(t_philo *philo, int l_fork, int r_fork)
{
    if (!philo->data->maid.state_of_prog)
    	return (1);
    get_forks(philo, l_fork - 1, r_fork - 1);
    print_info(get_time() - philo->data->times.start_time, philo->num, "is eating", philo->data->maid.state_of_prog);
    philo->data->maid.num_to_eat[philo->num - 1]++;
    philo->last_eat = get_time();
    ft_sleep(philo->data->times.time_to_eat);
    put_forks(philo, l_fork - 1, r_fork - 1);
    return (0);
}

int go_sleep(t_philo *philo)
{
    if (!philo->data->maid.state_of_prog)
            return (1);
    print_info(get_time() - philo->data->times.start_time, philo->num, "is sleeping", philo->data->maid.state_of_prog);
    ft_sleep(philo->data->times.time_to_sleep);
    return (0);
}

int think(t_philo *philo)
{
    if (!philo->data->maid.state_of_prog)
            return (1);
    print_info(get_time() - philo->data->times.start_time, philo->num, "is thinking", philo->data->maid.state_of_prog);
    return (0);
}

int	life(t_philo *philo)
{
	int	forks[2];

    forks[0] = ((philo->num == 1) * philo->data->max_philo) + ((philo->num != 1) * (philo->num - 1));
    forks[1] = philo->num;
    while(philo->data->maid.state_of_prog)
    {
        eat(philo, forks[0], forks[1]);
        go_sleep(philo);
        think(philo);
    }
    return (0);
}

int     all_ate(t_philo *philo)
{
    int     i;

    i = -1;
    while (++i < philo->data->max_philo)
    {
    	if (philo->data->maid.num_to_eat[i] !=  philo->data->max_eat)
            break;
    }
    return (i == philo->data->max_philo);
}

int	take_care(t_philo *philo)
{
	int	i;
	//ulg	tmp;

	i = 0;
	while (++i < philo->data->max_philo + 1)
	{
		if (!philo[i].last_eat)
			philo[i].last_eat = get_time();	
	}
	while (philo->data->maid.state_of_prog)
	{
		i = 0;
		while ((++i < philo->data->max_philo + 1) && philo->data->maid.state_of_prog)
        {
			//tmp = get_time() - philo[i].last_eat;
            if (get_time() - philo[i].last_eat > philo->data->times.time_to_die)
            {
                philo->data->maid.state_of_prog = 0;
                print_info(get_time() - philo[i].last_eat, i, "died", 1);
				break ;
            }
            if (philo->data->max_eat > 0 && all_ate(philo))
                philo->data->maid.state_of_prog = 0;
		}
	}
	
	return (0);
}

int	create_threads(t_philo *philo)
{
	int	i;

	i = 1;
	philo->data->times.start_time = get_time();
	while(i < philo->data->max_philo + 1)
	{
		philo[i].num = i;
		pthread_create(&philo[i].philo, NULL, (void *) life, &philo[i]);
		i += 2;
	}
	i = 2;
	while(i < philo->data->max_philo + 1)
	{
		philo[i].num = i;
		pthread_create(&philo[i].philo, NULL, (void *) life, &philo[i]);
		i += 2;
	}
	pthread_create(&philo->data->maid.maid, NULL, (void *) take_care, philo);
	return (0);
}

int	join_threads(t_philo *philo)
{
	int	i;

	i = 0;
	while (++i < philo->data->max_philo)
		pthread_join(philo[i].philo, NULL);
	pthread_join(philo->data->maid.maid, NULL);
	return (0);
}

int clear_data(t_philo *philo)
{
    int	i;

    i = -1;
    while (++i < philo->data->max_philo)
        pthread_mutex_destroy(&philo->data->forks[i]);
    return (0);
}

int	main(int ac, char **av)
{
	t_philo	*philo;

	if (ac != 5 && ac != 6)
		return (write(2, "Error !\n", 9));
	philo = NULL;
	init_data(&philo, ac, av);
	create_threads(philo);
	join_threads(philo);
	clear_data(philo);
}