/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 10:07:59 by abamksa           #+#    #+#             */
/*   Updated: 2023/12/22 16:02:39 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	dst_len;
	size_t	result;
	size_t	i;
	size_t	j;

	if (!size)
		return (ft_strlen(src));
	src_len = ft_strlen((char *)src);
	dst_len = ft_strlen(dst);
	if (size < dst_len)
		result = src_len + size;
	else
		result = src_len + dst_len;
	i = 0;
	while (dst[i])
		i++;
	j = 0;
	while (src[j] && i + 1 < size)
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (result);
}
