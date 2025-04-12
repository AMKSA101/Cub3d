/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_parse_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 19:25:41 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/12 19:22:48 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

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
		return (double_free(rgb_strs),
			print_error("Invalid RGB format", __FILE__, __LINE__), -1);
	temp_rgb[0] = ft_atoi(rgb_strs[0]);
	temp_rgb[1] = ft_atoi(rgb_strs[1]);
	temp_rgb[2] = ft_atoi(rgb_strs[2]);
	if (validate_rgb_values(temp_rgb[0], temp_rgb[1], temp_rgb[2]) == -1)
		return (double_free(rgb_strs), -1);
	*r = temp_rgb[0];
	*g = temp_rgb[1];
	*b = temp_rgb[2];
	return (double_free(rgb_strs), 0);
}
