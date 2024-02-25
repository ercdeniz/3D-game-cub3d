/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ercdeniz <ercdeniz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:12:08 by ercdeniz          #+#    #+#             */
/*   Updated: 2024/02/25 15:21:50 by ercdeniz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/_types/_null.h>
#include "../include/cub3d.h"

static void	error_init(t_error *error)
{
	error->arg = "Invalid number of arguments\nUsege: ./cub3d <map.cub>\n";
	error->extention = "Invalid extension, extension should be <.cub>!\n";
	error->fd = "File could not be opened\n";
	error->empty_map = "Map is empty\n";
	error->alloc = "Fatal Error!\nMemory allocation failed\n";
	error->inv_char = "Invalid character in map\n";
	error->inv_map = "Invalid map\n";
	error->inv_rgb = "Invalid RGB color code\n";
	error->inv_path = "Invalid path\n";
	error->inv_plyr = "Invalid player count\n";
	error->int_ovflw = "integer overflow\n";
	error->mlx = "mlx failed\n";
}

static void	map_init2(t_map *map)
{
	map->fd = 0;
	map->max = 0;
	map->start = 0;
	map->f_rgb[0] = -1;
	map->f_rgb[1] = -1;
	map->f_rgb[2] = -1;
	map->c_rgb[0] = -1;
	map->c_rgb[1] = -1;
	map->c_rgb[2] = -1;
	map->colors[0] = 0;
	map->colors[1] = 0;
	map->location[0] = 0;
	map->location[1] = 0;
	map->nswe_size[0] = 0;
	map->nswe_size[1] = 0;
	map->nswe_size[2] = 0;
	map->nswe_size[3] = 0;
	map->size = 0;
}

static void	map_init(t_map *map)
{
	map->dirs[0] = NULL;
	map->dirs[1] = NULL;
	map->dirs[2] = NULL;
	map->dirs[3] = NULL;
	map->color = NULL;
	map->info = NULL;
	map->area = NULL;
	map->temp_area = NULL;
	map->line = NULL;
	map->map_line = NULL;
	map->info_line = NULL;
	map->player = 0;
	map_init2(map);
}

void	init_image(t_game *game)
{
	game->north = NULL;
	game->south = NULL;
	game->west = NULL;
	game->east = NULL;
	game->image = NULL;
}

void	init_manager(t_game *game)
{
	game->mlx.ptr = NULL;
	game->mlx.win = NULL;
	init_image(game);
	error_init(&game->err);
	map_init(&game->map);
}
