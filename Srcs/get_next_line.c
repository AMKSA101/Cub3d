/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:12:38 by abamksa           #+#    #+#             */
/*   Updated: 2024/12/28 12:13:18 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	get_next_line(int fd, char **str)
{
	char buffer[BUFFER_SIZE];
	static char *buffer_stock = NULL;
	char *ptr_n;
	ssize_t bytes_read;
	int stock_len;

	*str = NULL;
	if (buffer_stock)
	{
		if ((ptr_n = strchr(buffer_stock, '\n')) != NULL)
		{
			*str = strndup(buffer_stock, ptr_n - buffer_stock);
			stock_len = ft_strlen(ptr_n + 1);
			char *aux = strdup(ptr_n + 1);
			free(buffer_stock);
			if (stock_len > 0)
			{
				buffer_stock = aux;
			}
			else
			{
				free(aux);
				buffer_stock = NULL;
			}
			return (ft_strlen(*str));
		}
		else
		{
			*str = strdup(buffer_stock);
			free(buffer_stock);
			buffer_stock = NULL;
		}
	}
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	while (bytes_read > 0)
	{
		buffer[bytes_read] = '\0';
		if ((ptr_n = strchr(buffer, '\n')) != NULL)
		{
			*str = strndup(buffer, ptr_n - buffer);
			if (ptr_n[1] != '\0')
			{
				buffer_stock = strdup(ptr_n + 1);
			}
			return (ft_strlen(*str));
		}
		else
		{
			char *aux = *str;
			*str = (char *)malloc(ft_strlen(aux) + ft_strlen(buffer) + 1);
			if (*str == NULL)
			{
				free(aux);
				return (-1);
			}
			if(aux) {
				ft_memcpy(*str, aux, ft_strlen(aux));
				ft_memcpy(*str + ft_strlen(aux), buffer, ft_strlen(buffer));
				free(aux);
			}
			else {
				ft_memcpy(*str, buffer, ft_strlen(buffer));
			}
			(*str)[ft_strlen(*str) + ft_strlen(buffer)] = '\0';
		}
			bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (bytes_read < 0)
		return (-1);
	if (*str == NULL && buffer_stock == NULL)
		return (-1);
	if (*str == NULL && buffer_stock != NULL)
	{
		*str = strdup(buffer_stock);
		free(buffer_stock);
		buffer_stock = NULL;
	}
	return(ft_strlen(*str));
}
