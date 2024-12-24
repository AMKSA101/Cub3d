/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 10:25:04 by abamksa           #+#    #+#             */
/*   Updated: 2023/11/30 19:49:37 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_checkchar(char const *str, const char c)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (*(str + i))
	{
		if (*(str + i) == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str_new;
	size_t	str_start;
	size_t	str_end;
	size_t	i;

	if (!s1 || !set)
		return (NULL);
	str_start = 0;
	while (*(s1 + str_start) && ft_checkchar(set, *(s1 + str_start)))
		str_start++;
	str_end = ft_strlen(s1);
	while (str_end > str_start && ft_checkchar(set, *(s1 + str_end - 1)))
		str_end--;
	str_new = malloc(sizeof(char) * (str_end - str_start + 1));
	if (!str_new)
		return (NULL);
	i = 0;
	while ((str_start + i) < str_end)
	{
		*(str_new + i) = *(s1 + str_start + i);
		i++;
	}
	*(str_new + i) = '\0';
	return (str_new);
}
