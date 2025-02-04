/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:12:57 by abamksa           #+#    #+#             */
/*   Updated: 2023/12/18 15:22:45 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *nptr)
{
	int	n;
	int	res;

	n = 0;
	res = 0;
	while ((*nptr >= '\t' && *nptr <= '\r') || (*nptr == ' '))
		++nptr;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			n++;
		++nptr;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		res *= 10;
		res += *nptr - 48;
		++nptr;
	}
	if (!(n % 2))
		return (res);
	return (-res);
}
