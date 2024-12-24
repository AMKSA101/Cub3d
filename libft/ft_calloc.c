/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 16:14:51 by abamksa           #+#    #+#             */
/*   Updated: 2023/12/22 18:29:51 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t n)
{
	void	*buf;

	if (count == 0 || n == 0)
	{
		count = n;
		n = 1;
	}
	buf = malloc(count * n);
	if (!buf)
		return (NULL);
	ft_bzero(buf, count * n);
	return (buf);
}
