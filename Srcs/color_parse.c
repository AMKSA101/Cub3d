/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 15:44:41 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/12 09:30:42 by abamksa          ###   ########.fr       */
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

// Helper function for setting color in scene
int	set_color_in_scene(char *identifier, int *rgb, t_scene *scene)
{
	if (ft_strncmp(identifier, "F", 2) == 0)
		scene->floor_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	else if (ft_strncmp(identifier, "C", 2) == 0)
		scene->ceiling_color = (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
	else
		return (print_error("Invalid color identifier", __FILE__, __LINE__), -1);
	return (0);
}

// Helper function for color
int	parse_color_line(char *line, t_scene *scene)
{
	char	**parts;
	int		count;
	int		rgb[3];

	if (!line)
		return (print_error("color line is NULL", __FILE__, __LINE__), -1);
	parts = ft_split(line, ' ');
	if (!parts)
		return(print_error(strerror(errno), __FILE__, __LINE__), -1);
	if (check_separator(parts[1], ',') == -1)
		return(double_free(parts), -1);
	count = 0;
	while (parts[count])
		count++;
	if (count != 2)
		return (double_free(parts), print_error("Invalid color line format", __FILE__, __LINE__), -1);
	if (parse_rgb_values(parts[1], &rgb[0], &rgb[1], &rgb[2]) == -1)
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
		return (print_error("Separator string is NULL", __FILE__, __LINE__), -1);
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

// Validate RGB values are in range
int	validate_rgb_values(int r, int g, int b)
{
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (print_error("Invalid RGB value range", __FILE__, __LINE__), -1);
	return (0);
}

int	parse_rgb_values(char *str, int *r, int *g, int *b)
{
	char	**rgb_strs;
	int		count;
	int		temp_rgb[3];

	if (!str)
		return (print_error("RGB string is NULL", __FILE__, __LINE__), -1);
	rgb_strs = ft_split(str, ',');
	if (!rgb_strs)
		return (print_error(strerror(errno), __FILE__, __LINE__), -1);
	count = 0;
	while (rgb_strs[count])
		count++;
	if (count != 3)
		return(double_free(rgb_strs), print_error("Invalid RGB format", __FILE__, __LINE__), -1);
	temp_rgb[0] = ft_atoi(rgb_strs[0]);
	temp_rgb[1] = ft_atoi(rgb_strs[1]);
	temp_rgb[2] = ft_atoi(rgb_strs[2]);
	if (validate_rgb_values(temp_rgb[0], temp_rgb[1], temp_rgb[2]) == -1)
		return (double_free(rgb_strs), -1);
	*r = temp_rgb[0];
	*g = temp_rgb[1];
	*b = temp_rgb[2];
	return(double_free(rgb_strs), 0);
}
