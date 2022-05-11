/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:31:06 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/05/11 14:48:34 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    *ft_calloc(size_t count, size_t size)
{
        void	*b;
        int		i;

        i = count * size;
        b = malloc(i);
        if (!b)
                return (b);
        while (i)
                ((char *)b)[--i] = 0;
        return (b);
}

int     ft_atoi(const char *str, int *flag)
{
    int		i;
    int		sign;
    long	num;
    i = 0;
    sign = 1;
    num = 0;
    while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
            i++;
    if (str[i] == '+' || str[i] == '-')
    {
            if (str[i] == '-')
                    sign *= -1;
			i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
			num *= 10;
        	num += str[i] - '0';
            i++;
    }
    if (num * sign <= 0)
		*flag = -2;
	return (num * sign);
}

int	ft_sleep(ulg time)
{
	ulg	first;

	first = get_time();
	usleep((time * 1000) * 90 / 100);
	while (get_time() - first < time)
		usleep(100);
	return (0);
}

ulg get_time()
{
  struct timeval tv;

  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int print_info(int time, int num, char *s, int status)
{
	if (status)
		printf("%d %d %s\n", time, num, s);
	return (0);
}