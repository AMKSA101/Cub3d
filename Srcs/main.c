/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abamksa <abamksa@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 11:18:49 by abamksa           #+#    #+#             */
/*   Updated: 2024/12/28 12:14:23 by abamksa          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Headers/cub3d.h"

void free_scene(t_scene *scene);

int	parse_cub(int fd, t_scene *scene)
{
    char *line;
	int map_start = 0;
    while (get_next_line(fd, &line) > 0)
	{
		// skip spaces
		int i = 0;
		while (line[i] == ' ' || line[i] == '\t')
			i++;
		//skip empty lines
		if (line[i] == '\0') {
			free(line);
			continue;
		}
		if (ft_strncmp(line + i, "NO", 2) == 0)
		{
			scene->north = ft_strdup(line + i + 2);
		}
		else if (ft_strncmp(line + i, "SO", 2) == 0)
		{
			scene->south = ft_strdup(line + i + 2);
		}
		else if (ft_strncmp(line + i, "WE", 2) == 0)
		{
			scene->west = ft_strdup(line + i + 2);
		}
		else if (ft_strncmp(line + i, "EA", 2) == 0)
		{
			scene->east = ft_strdup(line + i + 2);
		}
		else if (ft_strncmp(line + i, "F", 1) == 0)
		{
			char **split = ft_split(line + i + 1, ',');
            if(!split || split[0] == NULL || split[1] == NULL || split[2] == NULL){
                  free(line);
				  free(split);
			     exit(printf("Error\nInvalid F identifier\n"));
            }
			scene->floor[0] = ft_atoi(split[0]);
			scene->floor[1] = ft_atoi(split[1]);
			scene->floor[2] = ft_atoi(split[2]);
			int j = 0;
			while (split[j])
				free(split[j++]);
			free(split);

		}
		else if (ft_strncmp(line + i, "C", 1) == 0)
		{
			char **split = ft_split(line + i + 1, ',');
              if(!split || split[0] == NULL || split[1] == NULL || split[2] == NULL){
                 free(line);
				 free(split);
			     exit(printf("Error\nInvalid C identifier\n"));
            }
			scene->ceiling[0] = ft_atoi(split[0]);
			scene->ceiling[1] = ft_atoi(split[1]);
			scene->ceiling[2] = ft_atoi(split[2]);
            int j = 0;
			while (split[j])
				free(split[j++]);
			free(split);
		}
         else
		{
             map_start = 1;
         }
         if (map_start){
             //  Extract the Map (You'll need to refine this to handle the map correctly)
             int i = 0;
              scene->map = NULL; // just to make sure it starts as null
             char *map_line = strtok(line, "\n");
             while(map_line)
             {
                scene->map_width = strlen(map_line) > scene->map_width ? strlen(map_line) : scene->map_width;
                char **temp = (char**)realloc(scene->map, sizeof(char*) * (i + 1));
                if(!temp)
                {
                    free(line);
					free_scene(scene);
					exit(printf("Error\nProblem with realloc map\n"));
                }
                scene->map = temp;
                scene->map[i] = strdup(map_line);
                map_line = strtok(NULL, "\n");
                i++;
             }
             scene->map_height = i;
			 free(line);
             break;
        }
		free(line);
	}
	return (0);
}
void free_scene(t_scene *scene)
{
	if (scene->north)
		free(scene->north);
	if (scene->south)
		free(scene->south);
	if (scene->west)
		free(scene->west);
	if (scene->east)
		free(scene->east);
    if (scene->map) {
		for(size_t i = 0; i < scene->map_height; i++)
			free(scene->map[i]);
		free(scene->map);
	}
}
int	main(int ac, char **av)
{
	if (ac == 2)
	{
		int fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			exit(printf("Error\nCan't open file\n"));
		}
		t_scene scene;
		memset(&scene, 0, sizeof(t_scene)); // sets everything to null
		if (parse_cub(fd, &scene) == -1)
		{
			free_scene(&scene);
			exit(printf("Error\nInvalid file\n"));
		}
		else
		{
			for (size_t i = 0; i < scene.map_height; i++)
			{
				ft_putstr_fd(scene.map[i], 1);
				ft_putstr_fd("\n", 1);
			}
		}
		free_scene(&scene);
	}
	else
	{
		exit(printf("Error\nInvalid number of arguments\n"));
	}
	return (0);
}
