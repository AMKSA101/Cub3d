/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 09:43:56 by abamksa           #+#    #+#             */
/*   Updated: 2023/12/20 17:55:26 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_wordlen(char const *s, char c)
{
	size_t	len;
	int		wlen;

	if (!s)
		return (0);
	wlen = ft_strlen((char *)s);
	len = 0;
	while (*s != c && wlen--)
	{
		len++;
		s++;
	}
	return (len);
}

static size_t	ft_word_count(char const *s, char c)
{
	size_t	count;

	if (!s)
		return (0);
	count = 0;
	while (*s && *s == c)
		s++;
	while (*s)
	{
		count++;
		while (*s && *s != c)
			s++;
		while (*s && *s == c)
			s++;
	}
	return (count);
}

static char	*ft_strndup(const char *s, size_t n)
{
	size_t	i;
	char	*res;

	res = malloc(sizeof(char) * (n + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

static void	free_buffer(int i, char **array)
{
	while (i-- > 0)
		free(*(array + i));
	free(array);
}

char	**ft_split(char const *s, char c)
{
	char	**res;
	int		count;
	int		wlen;
	int		i;

	count = ft_word_count(s, c);
	res = malloc(sizeof(char *) * (count + 1));
	if (!res || !s)
		return (NULL);
	i = -1;
	while (i < count - 1)
	{
		while (*s && *s == c)
			s++;
		wlen = ft_wordlen(s, c);
		res[++i] = ft_strndup(s, wlen);
		if (!res[i])
		{
			free_buffer(i, res);
			return (NULL);
		}
		s += wlen;
	}
	res[count] = NULL;
	return (res);
}
