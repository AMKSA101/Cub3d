/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:25:41 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/15 16:25:02 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

static int	clean_rgb_string(char *str, char **cleaned)
{
	int	i;
	int	j;

	*cleaned = malloc(ft_strlen(str) + 1);
	if (!*cleaned)
		return (print_error("Memory allocation failed",
				__FILE__, __LINE__), -1);
	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == ' ' || str[i] == '\t')
		{
			if (i > 0 && str[i - 1] == ',')
				i++;
			else if (str[i + 1] && str[i + 1] == ',')
				i++;
			else
				(*cleaned)[j++] = str[i++];
		}
		else
			(*cleaned)[j++] = str[i++];
	}
	(*cleaned)[j] = '\0';
	return (0);
}

static int	check_digit_chars(char *start, int *val)
{
	int	j;

	j = 0;
	while (start[j])
	{
		if (j == 0 && start[j] == '+')
			j++;
		else if (!ft_isdigit(start[j]))
			return (print_error("Invalid character in RGB",
					__FILE__, __LINE__), -1);
		else
			j++;
	}
	*val = ft_atoi(start);
	return (0);
}

static int	count_and_validate_rgb(char **rgb_strs, int *rgb)
{
	int		count;
	int		i;
	char	*start;

	count = 0;
	while (rgb_strs[count])
		count++;
	if (count != 3)
		return (print_error("Invalid RGB format", __FILE__, __LINE__), -1);
	i = 0;
	while (i < 3)
	{
		start = rgb_strs[i];
		while (*start && (*start == ' ' || *start == '\t'))
			start++;
		if (check_digit_chars(start, &rgb[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	parse_rgb_values(char *str, int *r, int *g, int *b)
{
	char	**rgb_strs;
	char	*cleaned_str;
	int		temp_rgb[3];

	if (!str)
		return (print_error("RGB string is NULL", __FILE__, __LINE__), -1);
	if (clean_rgb_string(str, &cleaned_str) == -1)
		return (-1);
	rgb_strs = ft_split(cleaned_str, ',');
	free(cleaned_str);
	if (!rgb_strs)
		return (print_error(strerror(errno), __FILE__, __LINE__), -1);
	if (count_and_validate_rgb(rgb_strs, temp_rgb) == -1)
		return (double_free(rgb_strs), -1);
	if (validate_rgb_values(temp_rgb[0], temp_rgb[1], temp_rgb[2]) == -1)
		return (double_free(rgb_strs), -1);
	*r = temp_rgb[0];
	*g = temp_rgb[1];
	*b = temp_rgb[2];
	return (double_free(rgb_strs), 0);
}

int	check_map_valid(char **map, t_scene *scene)
{
	size_t	i;
	size_t	player_count;

	if (!map)
		return (print_error("Map array is NULL", __FILE__, __LINE__), -1);
	player_count = 0;
	i = 0;
	if (check_borders(map, scene) == -1)
		return (print_error("Invalid map border", __FILE__, __LINE__), -1);
	while (map[i])
	{
		if (process_map_line(map, i, &player_count, scene) == -1)
			return (-1);
		i++;
	}
	if (player_count != 1)
		return (print_error("Wrong player count", __FILE__, __LINE__), -1);
	return (0);
}
