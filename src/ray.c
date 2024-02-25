/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ercdeniz <ercdeniz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 12:01:43 by ercdeniz          #+#    #+#             */
/*   Updated: 2024/02/25 17:51:41 by ercdeniz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "../include/cub3d.h"

void	calculate_ray(t_game *game, int x)
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

void	calculate_hit_distance(t_game *game)
{
	int	a;

	while (1)
	{
		a = !(game->side_dist[0] < game->side_dist[1]);
		game->side_dist[a] += game->delta_dist[a];
		game->map_pos[a] += game->step[a];
		game->side = a;
		if (game->map.area[game->map_pos[1]][game->map_pos[0]] == '1')
			break ;
	}
}

void	calculate_wall_height(t_game *game)
{
	game->perp_wall_dist = game->side_dist[game->side]
		- game->delta_dist[game->side];
	game->line_h = (int)(HEIGHT / game->perp_wall_dist);
	game->draw_start = -game->line_h / 2 + HEIGHT / 2;
	game->draw_start = (game->draw_start >= 0) * game->draw_start;
	game->draw_end = game->line_h / 2 + HEIGHT / 2;
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
