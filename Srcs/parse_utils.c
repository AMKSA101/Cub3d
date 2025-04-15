/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 16:10:15 by abamksa           #+#    #+#             */
/*   Updated: 2025/04/15 16:14:15 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	allocate_components(char ***texture, char ***color, char ***map, int *vars)
{
	int	size;
	int	map_start;

	size = vars[0];
	map_start = vars[1];
	if (ft_alloc(texture, 4) == -1)
		return (print_error("Memory allocation failed",
				__FILE__, __LINE__), -1);
	if (ft_alloc(color, 2) == -1)
		return (double_free(*texture),
			print_error("Memory allocation failed", __FILE__, __LINE__), -1);
	if (ft_alloc(map, size - map_start) == -1)
		return (double_free(*texture), double_free(*color),
			print_error("Memory allocation failed", __FILE__, __LINE__), -1);
	return (0);
}
