/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:44:41 by abamksa           #+#             */
/*   Updated: 2025/04/15 10:53:09 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

int	parse_color(char **color, t_scene *scene)
{
	int	i;

	if (!color)
		return (print_error("color array is NULL", __FILE__, __LINE__), -1);
	i = 0;
	while (i < 2 && color[i])
	{
		if (parse_color_line(color[i], scene) == -1)
			return (-1);
		i++;
	}
	if (i != 2)
		return (print_error("Invalid color amount", __FILE__, __LINE__), -1);
	return (0);
}

int	set_color_in_scene(char *identifier, int *rgb, t_scene *scene)
{
	if (ft_strncmp(identifier, "F", 2) == 0)
	{
		if (scene->floor_color != 0)
			return (print_error("Duplicate floor color definition", __FILE__, __LINE__), -1);
		scene->floor_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	}
	else if (ft_strncmp(identifier, "C", 2) == 0)
	{
		if (scene->ceiling_color != 0)
			return (print_error("Duplicate ceiling color definition", __FILE__, __LINE__), -1);
		scene->ceiling_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	}
	else
		return (print_error("Invalid color identifier", __FILE__, __LINE__),
			-1);
	return (0);
}

static char	*get_trimmed_color_str(char **parts)
{
	char	*trimmed_line;

	if (!parts[1])
	{
		trimmed_line = parts[0] + 1;
		while (*trimmed_line && (*trimmed_line == ' ' || *trimmed_line == '\t'))
			trimmed_line++;
	}
	else
		trimmed_line = parts[1];
	return (trimmed_line);
}

int	parse_color_line(char *line, t_scene *scene)
{
	char	**parts;
	int		rgb[3];
	int		i;
	char	*trimmed_line;

	if (!line)
		return (print_error("color line is NULL", __FILE__, __LINE__), -1);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t'))
		i++;
	parts = ft_split(line + i, ' ');
	if (!parts)
		return (print_error(strerror(errno), __FILE__, __LINE__), -1);
	if (!parts[0] || (parts[0][0] != 'F' && parts[0][0] != 'C'))
		return (double_free(parts), print_error(
				"Invalid color identifier", __FILE__, __LINE__), -1);
	trimmed_line = get_trimmed_color_str(parts);
	if (check_separator(trimmed_line, ',') == -1)
		return (double_free(parts), -1);
	if (parse_rgb_values(trimmed_line, &rgb[0], &rgb[1], &rgb[2]) == -1)
		return (double_free(parts), -1);
	if (set_color_in_scene(parts[0], rgb, scene) == -1)
		return (double_free(parts), -1);
	return (double_free(parts), 0);
}

int	check_separator(char *str, char c)
{
	int	i;
	int	count;

	if (!str)
		return (print_error("Separator string is NULL",
				__FILE__, __LINE__), -1);
	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == c)
			count++;
		i++;
	}
	if (count != 2)
		return (print_error("Invalid separator count", __FILE__, __LINE__), -1);
	return (0);
}
