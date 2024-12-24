/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 09:58:08 by abamksa           #+#    #+#             */
/*   Updated: 2023/12/18 15:44:36 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	void	*ptr;

	ptr = dest;
	if (dest == src)
		return (dest);
	while (n--)
		*(unsigned char *)dest++ = *(unsigned char *)src++;
	return (ptr);
}
