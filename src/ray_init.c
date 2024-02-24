/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ercdeniz <ercdeniz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/24 15:30:41 by ercdeniz          #+#    #+#             */
/*   Updated: 2024/02/24 15:35:46 by ercdeniz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../include/cub3d.h"

static bool	east_west(t_game *game)
{
	if (game->map.player == 'W')
	{
		game->dir[0] = -1.0;
		game->dir[1] = 0.0;
		game->plane[0] = 0.0;
		game->plane[1] = -0.66;
		return (true);
	}
	else if (game->map.player == 'E')
	{
		game->dir[0] = 1.0;
		game->dir[1] = 0.0;
		game->plane[0] = 0.0;
		game->plane[1] = 0.66;
		return (true);
	}
	return (false);
}

static bool	south_north(t_game *game)
{
	if (game->map.player == 'S')
	{
		game->dir[0] = 0;
		game->dir[1] = 1;
		game->plane[0] = -0.66;
		game->plane[1] = 0;
		return (true);
	}
	else if (game->map.player == 'N')
	{
		game->dir[0] = 0;
		game->dir[1] = -1.00;
		game->plane[0] = 0.66;
		game->plane[1] = 0;
		return (true);
	}
	return (false);
}

bool	check_player(t_game *game)
{
	if (east_west(game))
		return (true);
	if (south_north(game))
		return (true);
	return (false);
}

void	ray_init(t_game *game)
{
	if (!check_player(game))
		return (printf(E, RED, game->err.inv_plyr, RES), ext(game, 1, 1));
	game->pos[0] = game->map.location[1] + 0.5;
	game->pos[1] = game->map.location[0] + 0.5;
	game->speed = 0.07;
	game->rspeed = 0.035;
	game->w = false;
	game->a = false;
	game->s = false;
	game->d = false;
	game->left = false;
	game->right = false;
}
