/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ercdeniz < ercdeniz@student.42kocaeli.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:29:08 by ercdeniz          #+#    #+#             */
/*   Updated: 2024/02/18 15:29:38 by ercdeniz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../minilibx/mlx.h"

static void	raycast(t_game *g)
{
	int	x;

	x = -1;
	while (++x < WIDTH)
	{
		calculate_ray(g, x);
		calculate_step(g);
		calculate_hit_distance(g);
		calculate_wall_height(g);
		render_column(g, x, -1);
	}
	mlx_put_image_to_window(g->mlx.ptr, g->mlx.win, g->image->image, 0, 0);
}

int	gamefunc(t_game *game)
{
	movement(game);
	rotate(game, 0, 0);
	raycast(game);
	return (0);
}
