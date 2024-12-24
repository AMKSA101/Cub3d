/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 10:46:45 by abamksa           #+#    #+#             */
/*   Updated: 2023/11/21 10:24:15 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *str, int c, size_t n)
{
	void	*ptr;

	ptr = str;
	while (n--)
		*(unsigned char *)str++ = (unsigned char) c;
	return (ptr);
}
