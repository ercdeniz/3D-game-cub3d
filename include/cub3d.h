/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ercdeniz <ercdeniz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/17 12:12:47 by ercdeniz          #+#    #+#             */
/*   Updated: 2024/02/27 13:56:54 by ercdeniz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

// INCLUDE
# include <stdbool.h>

// DIMENSIONS
# define WIDTH 720
# define HEIGHT 550
# define TEXWIDTH 64
# define TEXHEIGHT 64

// COLORS
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define PURPLE "\033[1;35m"
# define CYAN "\033[1;36m"
# define RES "\033[0m"

// ERROR MESSAGE
# define E "%sError: %s%s"

// SIGNALS
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2

// STRUCTS
typedef struct s_error
{
	const char	*arg;
	const char	*extention;
	const char	*fd;
	const char	*empty_map;
	const char	*alloc;
	const char	*inv_char;
	const char	*inv_map;
	const char	*inv_rgb;
	const char	*inv_path;
	const char	*inv_plyr;
	const char	*int_ovflw;
	const char	*mlx;
}			t_error;

typedef struct s_image
{
	void	*image;
	int		*addr;
}			t_image;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
}			t_mlx;

typedef struct s_map
{
	int		fd;
	int		max;
	int		start;
	int		f_rgb[3];		// 0:R 1:G 2:B color
	int		c_rgb[3];		// 0:R 1:G 2:B color
	int		colors[2];		// rgb F and rgb C
	int		location[2];	// 0:x axis 1:y axis
	int		nswe_size[4];	// 0:North 1:South 2:West 3:East
	int		size;			// info size
	char	*dirs[4];		// 0:North 1:South 2:West 3:East
	char	*color;
	char	**info;
	char	**area;
	char	**temp_area;
	char	*line;
	char	*map_line;
	char	*info_line;
	char	player;
}			t_map;

typedef struct s_game
{
	t_error	err;
	t_mlx	mlx;
	t_map	map;
	t_image	*north;
	t_image	*south;
	t_image	*west;
	t_image	*east;
	t_image	*image;
	float	speed;
	float	rspeed;
	double	camera_x;
	double	wall_x;
	double	tex_pos;
	double	step_size;
	double	perp_wall_dist;
	double	pos[2];			// 0:x 1:y
	double	dir[2];			// 0:x 1:y
	double	plane[2];		// 0:x 1:y
	double	side_dist[2];	// 0:x 1:y
	double	delta_dist[2];	// 0:x 1:y
	double	raydir[2];		// 0:x 1:y
	int		map_pos[2];		// 0:x 1:y
	int		step[2];		// 0:x 1:y
	int		tex[2];			// 0:x 1:y
	int		side;
	int		line_h;
	int		draw_start;
	int		draw_end;
	bool	w;
	bool	s;
	bool	a;
	bool	d;
	bool	left;
	bool	right;
}			t_game;

// MOVE.C
int			move_press(int keyCode, t_game *game);
int			move_release(int keyCode, t_game *game);
void		movement(t_game *game);
void		rotate(t_game *g, double dir, double plane);

// RAY.C
void		calculate_ray_direction_and_distances(t_game *game, int x);
void		calculate_step(t_game *game);
void		calculate_collision_distance(t_game *game);
void		calculate_wall_properties(t_game *game);
void		render_column(t_game *game, int x, int y);

// RAY_MANAGER.C
int			gamefunc(t_game *game);

// MLX_UTILS.C
int			exit_mlx(t_game *game);
void		ft_mlx(t_game *game, int a, int b);

// UTILS.C
void		ext(t_game *game, int status, bool destroy);
char		*replace_tabs_with_spaces(const char *str, int tab, int i, int j);
void		rgb_and_path_check(t_game *game);
void		is_cub(char *file_name, t_game *game);
int			cub_atoi(t_game *game, const char *str);

// READ_MAP.C
void		map_read_and_parsing(t_game *game);

// CHECK.C
void		map_check(t_game *game);

// INIT.C
void		init_manager(t_game *game);
void		ray_and_mlx_init(t_game *game);

// EXTRA.C
int			set_rgb(t_game *game, int k, int flag);
int			ft_isplus_minus_space(char c);

#endif // CUB3D_H
