/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ercdeniz <ercdeniz@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 14:31:21 by ercdeniz          #+#    #+#             */
/*   Updated: 2024/05/04 14:47:55 by ercdeniz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <malloc/_malloc.h>
#include "../include/cub3d.h"
#include "../libft/libft.h"

static int	set_path(t_game *game, int i, char *temp, int flag)
{
	int	j;

	while (temp[i] && temp[i] == ' ')
		i++;
	j = i;
	while (temp[j] != '\n' && temp[j] != '\0')
		j++;
	if (flag == 1 && !game->map.dirs[0])
		game->map.dirs[0] = ft_substr(temp, i, j - i);
	else if (flag == 2 && !game->map.dirs[1])
		game->map.dirs[1] = ft_substr(temp, i, j - i);
	else if (flag == 3 && !game->map.dirs[2])
		game->map.dirs[2] = ft_substr(temp, i, j - i);
	else if (flag == 4 && !game->map.dirs[3])
		game->map.dirs[3] = ft_substr(temp, i, j - i);
	if ((!game->map.dirs[0] && flag == 1) || (!game->map.dirs[1] && flag == 2) \
	|| (!game->map.dirs[2] && flag == 3) || (!game->map.dirs[3] && flag == 4))
		return (printf(E, RED, game->err.alloc, RES), ext(game, 0, 1), 1);
	game->map.size++;
	return (2);
}

static int	set_color(t_game *g, int i, char *temp, int flag)
{
	int		arr[2];

	arr[0] = 0;
	arr[1] = 0;
	if (word_count(temp + i + 1, ',', 1) != 3)
		return (printf(E, RED, g->err.inv_rgb, RES), ext(g, 1, 1), 1);
	while (temp[i])
	{
		arr[0] = i;
		while (temp[i] && temp[i] != ',')
		{
			if (!ft_isdigit(temp[i]) && !ft_isplus_minus_space(temp[i]))
				return (printf(E, RED, g->err.inv_rgb, RES), ext(g, 1, 1), 1);
			i++;
		}
		g->map.color = ft_substr(temp, arr[0], (i++) - arr[0]);
		if (!g->map.color)
			return (printf(E, RED, g->err.inv_rgb, RES), ext(g, 1, 1), 1);
		arr[1] += set_rgb(g, arr[1], flag);
		free(g->map.color);
		g->map.color = NULL;
		if (arr[1] == 3)
			break ;
	}
	return (1);
}

static void	map_info_pars(t_game *game, char **temp, int i, int j)
{
	while (temp[++i])
	{
		j = -1;
		while (temp[i][++j])
		{
			if ((temp[i][j] == 'N' && temp[i][j + 1] == 'O'))
				j += set_path(game, j + 2, temp[i], 1) - 1;
			else if ((temp[i][j] == 'S' && temp[i][j + 1] == 'O'))
				j += set_path(game, j + 2, temp[i], 2) - 1;
			else if ((temp[i][j] == 'W' && temp[i][j + 1] == 'E'))
				j += set_path(game, j + 2, temp[i], 3) - 1;
			else if ((temp[i][j] == 'E' && temp[i][j + 1] == 'A'))
				j += set_path(game, j + 2, temp[i], 4) - 1;
			else if (temp[i][j] == 'F')
			{
				j += set_color(game, j + 1, temp[i], 1) - 1;
				game->map.size++;
			}
			else if (temp[i][j] == 'C')
			{
				j += set_color(game, j + 1, temp[i], 2) - 1;
				game->map.size++;
			}
		}
	}
}

static void	cut_map(t_game *game)
{
	int		start;

	game->map.max = ft_strlen(game->map.line) - 1;
	start = game->map.max;
	while (start != 0 && game->map.line[--start])
		if (game->map.line[start] == '\n' && game->map.line[start - 1] == '\n')
			break ;
	game->map.start = start;
	game->map.map_line = ft_substr(game->map.line, start + 1, game->map.max);
	game->map.info_line = ft_substr(game->map.line, 0, start);
	if (!game->map.info_line || !game->map.map_line)
		return (printf(E, RED, game->err.alloc, RES), ext(game, 1, 1));
	game->map.info = ft_split(game->map.info_line, '\n');
	map_info_pars(game, game->map.info, -1, 0);
}

void	map_read_and_parsing(t_game *game)
{
	char	*temp;
	char	*line;

	temp = NULL;
	while (true)
	{
		line = get_next_line(game->map.fd);
		if (!line)
			break ;
		game->map.line = ft_strjoin(temp, line);
		free(line);
		free(temp);
		temp = game->map.line;
	}
	if (!game->map.line)
		return (printf(E, RED, game->err.empty_map, RES), ext(game, 1, 1));
	temp = ft_trim(game->map.line, " \t\v\f\r\n");
	if (!temp)
		return (printf(E, RED, game->err.alloc, RES), ext(game, 1, 1));
	line = replace_tabs_with_spaces(temp, game, -1, 0);
	free(game->map.line);
	free(temp);
	game->map.line = line;
	cut_map(game);
}
