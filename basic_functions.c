/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ted-dafi <ted-dafi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:31:06 by ted-dafi          #+#    #+#             */
/*   Updated: 2022/05/05 11:31:54 by ted-dafi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void    *ft_calloc(size_t count, size_t size)
{
        void    *b;
        int             i;

        i = count * size;
        b = malloc(i);
        if (b == NULL)
                exit (write(2, "Error, allocation Error.\n", 26));
        while (i)
                ((char *)b)[--i] = 0;
        return (b);
}

int     ft_atoi(const char *str)
{
        int                             i;
        int                             sign;
        unsigned long   num;

        i = 0;
        sign = 1;
        num = 0;
        while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
        {
                i++;
        }
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
        return (num * sign);
}
