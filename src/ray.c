/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ercdeniz <ercdeniz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:01:43 by ercdeniz          #+#    #+#             */
/*   Updated: 2024/02/27 17:17:50 by ercdeniz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../include/cub3d.h"

/* 
	(perspective normalization)
	camera_x: -1 to 1 based on game window, represents left/right screen edge.
	
	raydir: according to plane, a vector representing the direction
	the camera is facing.
	
	map_pos: holds the integer position in the map.
	
	delta_dist: determines how many units ray needs to travel to the next 
	x and y location.
	dir[1] is set to 0.001f and delta_dist[1] is set to 1e30 to prevent 
	division by zero.
*/
void	calculate_ray_direction_and_distances(t_game *game, int x)
{
	game->camera_x = 2 * x / (double)WIDTH - 1;
	game->raydir[0] = game->dir[0] + game->plane[0] * game->camera_x;
	game->raydir[1] = game->dir[1] + game->plane[1] * game->camera_x;
	game->map_pos[0] = (int)game->pos[0];
	game->map_pos[1] = (int)game->pos[1];
	if (game->raydir[0] == 0)
		game->delta_dist[0] = 1e30;
	else
		game->delta_dist[0] = fabs(1 / game->raydir[0]);
	if (game->raydir[1] == 0)
	{
		game->dir[1] = 0.001f;
		game->delta_dist[1] = 1e30;
	}
	else
		game->delta_dist[1] = fabs(1 / game->raydir[1]);
}

/*
	step: -1 if (left dir) raydir is negative, 1 if (right dir) is positive.
	side_dist: distance to the next x or y side.
*/
void	calculate_step(t_game *g)
{
	if (g->raydir[0] < 0)
	{
		g->step[0] = -1;
		g->side_dist[0] = (g->pos[0] - g->map_pos[0]) * g->delta_dist[0];
	}
	else
	{
		g->step[0] = 1;
		g->side_dist[0] = (g->map_pos[0] + 1.0 - g->pos[0]) * g->delta_dist[0];
	}
	if (g->raydir[1] < 0)
	{
		g->step[1] = -1;
		g->side_dist[1] = (g->pos[1] - g->map_pos[1]) * g->delta_dist[1];
	}
	else
	{
		g->step[1] = 1;
		g->side_dist[1] = (g->map_pos[1] + 1.0 - g->pos[1]) * g->delta_dist[1];
	}
}

/*
	nearest_wall: 0 if side_dist[0] is smaller, 1 if side_dist[1] is smaller.
	side_dist[nearest_wall]: distance to the next x or y side.
	map_pos[nearest_wall]: integer position in the map.
	side: 0 if x side, 1 if y side.	
*/
void	calculate_collision_distance(t_game *game)
{
	int	nearest_wall;

	while (true)
	{
		if (game->side_dist[0] < game->side_dist[1])
			nearest_wall = 0;
		else
			nearest_wall = 1;
		if (nearest_wall == 0)
		{
			game->side_dist[0] += game->delta_dist[0];
			game->map_pos[0] += game->step[0];
		}
		else
		{
			game->side_dist[1] += game->delta_dist[1];
			game->map_pos[1] += game->step[1];
		}
		game->side = nearest_wall;
		if ((game->map.area[game->map_pos[1]][game->map_pos[0]]) == '1')
			break ;
	}
}

/*
	perp_wall_dist: perpendicular distance to the wall.
	line_h: height of the wall.
	draw_start: starting point of the wall.
	draw_end: ending point of the wall.
	wall_x: exact value of the wall.
	tex[0]: x coordinate of the wall.
	step_size: size of the step to increase the texture coordinate.
	tex_pos: texture coordinate.
*/
void	calculate_wall_properties(t_game *game)
{
	game->perp_wall_dist = game->side_dist[game->side]
		- game->delta_dist[game->side];
	game->line_h = (int)(HEIGHT / game->perp_wall_dist);
	game->draw_start = (HEIGHT - game->line_h) / 2;
	game->draw_start = (game->draw_start >= 0) * game->draw_start;
	game->draw_end = (HEIGHT + game->line_h) / 2;
	if (game->draw_end >= HEIGHT)
		game->draw_end = HEIGHT - 1;
	game->wall_x = game->pos[!game->side] + game->perp_wall_dist
		* game->raydir[!game->side];
	game->wall_x = game->wall_x - (int)game->wall_x;
	game->tex[0] = (int)(game->wall_x * TEXWIDTH);
	if (game->side == 0 && game->raydir[0] < 0)
		game->tex[0] = TEXWIDTH - game->tex[0] - 1;
	if (game->side == 1 && game->raydir[1] > 0)
		game->tex[0] = TEXWIDTH - game->tex[0] - 1;
	game->step_size = (double)TEXHEIGHT / game->line_h;
	game->tex_pos = (game->draw_start - HEIGHT / 2 + game->line_h / 2)
		* game->step_size;
}

/*
	Rendering the wall.
	First, the ceiling and the floor are rendered.
	Then, the wall is rendered according to the side and
	the direction of the ray.
*/
void	render_column(t_game *game, int x, int y)
{
	while (++y < HEIGHT)
	{
		game->tex[1] = (int)game->tex_pos;
		if (y < game->draw_start)
			game->image->addr[y * WIDTH + x] = game->map.colors[1];
		else if (y > game->draw_end)
			game->image->addr[y * WIDTH + x] = game->map.colors[0];
		else
		{
			if (game->side == 1 && game->raydir[1] < 0)
				game->image->addr[y * WIDTH + x] = game->north->addr[TEXHEIGHT
					* game->tex[1] + game->tex[0]];
			else if (game->side == 1 && game->raydir[1] >= 0)
				game->image->addr[y * WIDTH + x] = game->south->addr[TEXHEIGHT
					* game->tex[1] + game->tex[0]];
			if (game->side == 0 && game->raydir[0] < 0)
				game->image->addr[y * WIDTH + x] = game->west->addr[TEXHEIGHT
					* game->tex[1] + game->tex[0]];
			else if (game->side == 0 && game->raydir[0] >= 0)
				game->image->addr[y * WIDTH + x] = game->east->addr[TEXHEIGHT
					* game->tex[1] + game->tex[0]];
			game->tex_pos += game->step_size;
		}
	}
}
