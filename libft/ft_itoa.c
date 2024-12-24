/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 13:06:30 by abamksa           #+#    #+#             */
/*   Updated: 2023/11/25 10:51:27 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nblen(int nb)
{
	int	len;

	len = 0;
	if (nb < 1)
		len++;
	while (nb)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

static long	ft_abs(long n)
{
	long	nb;

	nb = 1;
	if (n < 0)
		nb *= -n;
	else
		nb *= n;
	return (nb);
}

char	*ft_itoa(int n)
{
	unsigned int	number;
	int				sign;
	int				len;
	char			*str;

	if (n < 0)
		sign = 1;
	else
		sign = 0;
	len = ft_nblen(n);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	*(str + len) = '\0';
	number = ft_abs(n);
	while (len--)
	{
		*(str + len) = 48 + number % 10;
		number /= 10;
	}
	if (sign)
		*str = 45;
	return (str);
}
