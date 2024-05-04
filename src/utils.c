/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ercdeniz <ercdeniz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:16:42 by ercdeniz          #+#    #+#             */
/*   Updated: 2024/05/04 14:51:16 by ercdeniz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <fcntl.h>
#include <malloc/_malloc.h>
#include "../include/cub3d.h"
#include "../libft/libft.h"

char	*replace_tabs_with_spaces(const char *str, t_game *game, int i, int j)
{
	int		tab_count;
	char	*new_str;

	tab_count = 0;
	while (str[++i] != '\0')
		if (str[i] == '\t')
			tab_count++;
	new_str = malloc(sizeof(char) * (i + (tab_count * 3) + 1));
	if (!new_str)
		return (printf(E, RED, game->err.alloc, RES), ext(game, 0, 1), NULL);
	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] == '\t')
		{
			new_str[j++] = ' ';
			new_str[j++] = ' ';
			new_str[j++] = ' ';
			new_str[j++] = ' ';
		}
		else
			new_str[j++] = str[i];
	}
	return (new_str[j] = '\0', new_str);
}

void	rgb_and_path_check(t_game *game)
{
	int	i;

	i = -1;
	if (game->map.size != 6)
		return (printf(E, RED, game->err.inv_map, RES), ext(game, 1, 1));
	while (++i < 4)
		if (game->map.dirs[i] && ft_strlen(game->map.dirs[i]) <= 1)
			return (printf(E, RED, game->err.inv_path, RES), ext(game, 1, 1));
	i = -1;
	while (++i < 3)
		if (!(game->map.f_rgb[i] >= 0 && game->map.f_rgb[i] <= 255)
			|| !(game->map.c_rgb[i] >= 0 && game->map.c_rgb[i] <= 255))
			return (printf(E, RED, game->err.inv_rgb, RES), ext(game, 1, 1));
	game->map.colors[0] = (game->map.f_rgb[0] << 16) + (game->map.f_rgb[1] << 8)
		+ game->map.f_rgb[2];
	game->map.colors[1] = (game->map.c_rgb[0] << 16) + (game->map.c_rgb[1] << 8)
		+ game->map.c_rgb[2];
}

void	is_cub(char *file_name, t_game *game)
{
	int	len;

	len = ft_strlen(file_name);
	if (file_name[len - 1] == 'b' && file_name[len - 2] == 'u'
		&& file_name[len - 3] == 'c' && file_name[len - 4] == '.')
	{
		game->map.fd = open(file_name, O_RDONLY);
		if (game->map.fd == -1)
			return (printf(E, RED, game->err.fd, RES), ext(game, 1, 1));
	}
	else
		return (printf(E, RED, game->err.extention, RES), ext(game, 1, 1));
}

int	cub_atoi(t_game *game, const char *str)
{
	int		sign;
	long	res;

	sign = 1;
	res = 0;
	while ((9 <= *str && *str <= 13) || *str == 32)
		str++;
	if (*str == 43 || *str == 45)
	{
		if (*str == 45)
			sign *= -1;
		str++;
	}
	while (48 <= *str && *str <= 57)
		res = (res * 10) + (*str++ & 15);
	if (res * sign < -2147483648 || res * sign > 2147483647)
		return (printf(E, RED, game->err.int_ovflw, RES), ext(game, 1, 1), 0);
	return (res * sign);
}
