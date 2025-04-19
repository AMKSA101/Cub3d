/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:12:38 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/12 19:12:25 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

static char	*get_line_from_stock(char **buffer_stock);
static char	*read_and_process_buffer(int fd, char **buffer_stock);
static char	*append_buffer(char *str, char *buffer);

int	get_next_line(int fd, char **str)
{
	static char	*buffer_stock = NULL;

	*str = get_line_from_stock(&buffer_stock);
	if (*str)
		return (ft_strlen(*str));
	*str = read_and_process_buffer(fd, &buffer_stock);
	if (*str)
		return (ft_strlen(*str));
	return (-1);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*new_s;

	new_s = (char *)malloc(n + 1);
	if (!new_s)
		return (NULL);
	ft_memcpy(new_s, s, n);
	new_s[n] = '\0';
	return (new_s);
}

static char	*get_line_from_stock(char **buffer_stock)
{
	char	*ptr_n;
	char	*line;
	char	*aux;

	line = NULL;
	ptr_n = ft_strchr(*buffer_stock, '\n');
	if (*buffer_stock && ptr_n)
	{
		line = ft_strndup(*buffer_stock, ptr_n - *buffer_stock);
		aux = ft_strdup(ptr_n + 1);
		free(*buffer_stock);
		*buffer_stock = aux;
	}
	else if (*buffer_stock)
	{
		line = ft_strdup(*buffer_stock);
		free(*buffer_stock);
		*buffer_stock = NULL;
	}
	return (line);
}

static char	*read_and_process_buffer(int fd, char **buffer_stock)
{
	char	buffer[BUFFER_SIZE + 1];
	ssize_t	bytes_read;
	char	*str;
	char	*ptr_n;

	str = NULL;
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		ptr_n = ft_strchr(buffer, '\n');
		if (ptr_n)
		{
			str = ft_strndup(buffer, ptr_n - buffer);
			*buffer_stock = ft_strdup(ptr_n + 1);
			break ;
		}
		str = append_buffer(str, buffer);
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (str);
}

static char	*append_buffer(char *str, char *buffer)
{
	char	*new_str;
	size_t	len;

	len = 0;
	if (str)
		len = ft_strlen(str);
	new_str = (char *)malloc(len + ft_strlen(buffer) + 1);
	if (!new_str)
	{
		if (str)
			free(str);
		return (NULL);
	}
	if (str)
	{
		ft_memcpy(new_str, str, len);
		free(str);
	}
	ft_memcpy(new_str + len, buffer, ft_strlen(buffer) + 1);
	return (new_str);
}
