/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ercdeniz <ercdeniz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:12:08 by ercdeniz          #+#    #+#             */
/*   Updated: 2024/02/23 17:43:09 by ercdeniz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdlib.h>

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

static void	map_init(t_map *map)
{
	map->f_rgb[0] = -1;
	map->f_rgb[1] = -1;
	map->f_rgb[2] = -1;
	map->c_rgb[0] = -1;
	map->c_rgb[1] = -1;
	map->c_rgb[2] = -1;
}

void	init_manager(t_game *game)
{
	error_init(&game->err);
	map_init(&game->map);
}

void	ray_init(t_game *game)
{
	game->pos[0] = game->map.location[1] + 0.5;
	game->pos[1] = game->map.location[0] + 0.5;
	game->dir[0] = 0;
	game->dir[1] = -1;
	game->plane[0] = 0.66;
	game->plane[1] = 0;
	game->speed = 0.08;
	game->rspeed = 0.04;
	game->w = false;
	game->a = false;
	game->s = false;
	game->d = false;
	game->left = false;
	game->right = false;
}
