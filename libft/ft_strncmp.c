/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 10:33:25 by abamksa           #+#    #+#             */
/*   Updated: 2023/12/03 10:31:15 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	cs1;
	unsigned char	cs2;

	if (!n)
		return (0);
	while (n-- > 0)
	{
		cs1 = *(unsigned char *)s1++;
		cs2 = *(unsigned char *)s2++;
		if (cs1 != cs2)
			return (cs1 - cs2);
		if (!cs1)
			return (0);
	}
	return (0);
}
