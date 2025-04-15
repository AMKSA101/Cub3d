/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse_help.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 10:38:31 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/15 16:27:32 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	find_map_start(char **content, int size)
{
	int		i;
	int		map_start;
	int		j;

	i = 0;
	map_start = -1;
	while (i < size)
	{
		j = 0;
		while (content[i][j] && (content[i][j] == ' ' || content[i][j] == '\t'))
			j++;
		if (content[i][j] == '1' || content[i][j] == '0')
		{
			map_start = i;
			break ;
		}
		i++;
	}
	if (map_start == -1)
		return (print_error("No valid map found", __FILE__, __LINE__), -1);
	return (map_start);
}

static int	is_texture_identifier(char *line, int j)
{
	return ((line[j] == 'N' && line[j + 1] == 'O'
			&& (line[j + 2] == ' ' || line[j + 2] == '\t'))
		|| (line[j] == 'S' && line[j + 1] == 'O'
			&& (line[j + 2] == ' ' || line[j + 2] == '\t'))
		|| (line[j] == 'W' && line[j + 1] == 'E'
			&& (line[j + 2] == ' ' || line[j + 2] == '\t'))
		|| (line[j] == 'E' && line[j + 1] == 'A'
			&& (line[j + 2] == ' ' || line[j + 2] == '\t')));
}

static int	is_color_identifier(char *line, int j)
{
	return ((line[j] == 'F' && (line[j + 1] == ' ' || line[j + 1] == '\t'))
		|| (line[j] == 'C' && (line[j + 1] == ' ' || line[j + 1] == '\t')));
}

static int	process_line(t_parse_data *data, int i)
{
	int	j;

	j = 0;
	while (data->content[i][j] && (data->content[i][j] == ' ' ||
			data->content[i][j] == '\t'))
		j++;
	if (data->content[i][j] == '\0')
		return (0);
	if (data->indices[0] < 4 && is_texture_identifier(data->content[i], j))
	{
		data->texture[data->indices[0]++] = ft_strdup(data->content[i]);
		return (1);
	}
	else if (data->indices[1] < 2 && is_color_identifier(data->content[i], j))
	{
		data->color[data->indices[1]++] = ft_strdup(data->content[i]);
		return (1);
	}
	return (0);
}

int	extract_textures_and_colors(char **content, int map_start,
		char **texture, char **color)
{
	int				i;
	t_parse_data	data;

	data.content = content;
	data.texture = texture;
	data.color = color;
	data.indices[0] = 0;
	data.indices[1] = 0;
	i = 0;
	while (i < map_start)
	{
		if (!process_line(&data, i))
		{
			i++;
			continue ;
		}
		i++;
	}
	if (data.indices[0] != 4 || data.indices[1] != 2)
		return (print_error("Missing texture or color definitions",
				__FILE__, __LINE__), -1);
	return (0);
}
