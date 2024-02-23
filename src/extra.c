/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ercdeniz < ercdeniz@student.42kocaeli.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 17:55:22 by ercdeniz          #+#    #+#             */
/*   Updated: 2024/02/13 13:50:41 by ercdeniz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

/*
Everything is for the NORM
*/
int	set_rgb(t_game *game, int k, int flag)
{
	if (flag == 1)
		game->map.f_rgb[k] = cub_atoi(game, game->map.color);
	else if (flag == 2)
		game->map.c_rgb[k] = cub_atoi(game, game->map.color);
	return (1);
}

/*
Everything is for the NORM
*/
int	ft_isplus_minus_space(char c)
{
	if (c == '+' || c == '-' || c == ' ')
		return (1);
	return (0);
}
