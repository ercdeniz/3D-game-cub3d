/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ercdeniz <ercdeniz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 17:19:31 by ercdeniz          #+#    #+#             */
/*   Updated: 2024/02/23 18:24:01 by ercdeniz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "../include/cub3d.h"
#include "../minilibx/mlx.h"
#include "../libft/libft.h"

int	main(int ac, char **av)
{
	t_game	*game;

	game = (t_game *)ft_calloc(1, sizeof(t_game));
	if (!game)
		return (printf(E, RED, "alloc error!", RES), free(game), 1);
	init_manager(game);
	if (ac == 2)
	{
		is_cub(av[1], game);
		map_read_and_parsing(game);
		map_check(game);
		ray_init(game);
		game->mlx.ptr = mlx_init();
		game->mlx.win = mlx_new_window(game->mlx.ptr, WIDTH, HEIGHT, "cub3D");
		ft_mlx(game, 0, 0);
		mlx_hook(game->mlx.win, 2, 1L << 0, move_press, game);
		mlx_hook(game->mlx.win, 3, 1L << 1, move_release, game);
		mlx_hook(game->mlx.win, 17, 1L << 17, exit_mlx, game);
		mlx_loop_hook(game->mlx.ptr, &gamefunc, game);
		mlx_loop(game->mlx.ptr);
		ext(game, 0, 1);
	}
	else
		return (printf(E, RED, game->err.arg, RES), 1);
	return (0);
}
