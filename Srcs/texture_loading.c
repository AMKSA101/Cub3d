/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_loading.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 13:30:04 by abamksa           #+#    #+#             */
/*   Updated: 2025/03/18 13:30:26 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void *load_texture(t_data *data, int *width, int *height, char *path)
{
	void *texture = mlx_xpm_file_to_image(data->mlx->mlx_ptr, path, width, height);
	if (!texture)
	{
		free_scene(data->scene);
		fprintf(stderr, "Error loading texture from path: %s\n", path); // Print the path
		print_error("Error loading texture", __FILE__, __LINE__);
		exit(-1);
	}
	return texture;
}
t_texture *get_textures(t_data *data)
{
	t_texture *textures = (t_texture *)malloc(sizeof(t_texture));
	int width;
	int height;
	if (!textures)
	{
		free_scene(data->scene);
		print_error("Error allocating memory for textures", __FILE__, __LINE__);
		exit(-1);
	}
	textures->north = load_texture(data, &width, &height, data->scene->north_texture);
	textures->north_width = width;
	textures->north_height = height;
	textures->south = load_texture(data, &width, &height, data->scene->south_texture);
	textures->south_width = width;
	textures->south_height = height;
	textures->east = load_texture(data, &width, &height, data->scene->east_texture);
	textures->east_width = width;
	textures->east_height = height;
	textures->west = load_texture(data, &width, &height, data->scene->west_texture);
	textures->west_width = width;
	textures->west_height = height;
	return textures;
}
