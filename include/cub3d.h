/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:09:44 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/19 18:22:53 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include "../mlx/mlx.h"
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define BLACK "\1\e[1;90m\2"
# define RED "\1\e[1;91m\2"
# define GREEN "\1\e[1;92m\2"
# define YELLOW "\1\e[1;93m\2"
# define BLUE "\1\033[38;5;117m\2"
# define PURPLE "\1\033[38;5;164m\2"
# define CYAN "\1\033[38;5;51m\2"
# define WHITE "\1\e[1;97m\2"
# define RESET "\1\e[0m\2"
# define BOLD "\1\e[1m\2"
# define GREY "\033[90m\2"
# define LILA "\1\033[38;5;147m\2"
# define O_BLUE "\1\033[38;5;24m\2"
# define TEAL "\1\033[38;5;44m\2"
# define LIGHT_GREEN "\1\033[38;5;120m\2"

# define E_MALLOC "Malloc failure!"
# define E_DIR "Wrong argument: Directory"
# define E_TNFOND "Texture path not found"
# define E_TMULTI "Multiple definition for textutre path : "
# define E_SPACE "Invalid whitespace characters"
# define E_FILE "Invalid file extension"
# define E_RGB "Invalid RGB value"
# define E_TEXTURE "Invalid texture"
# define E_EMPTY "Empty file"
# define E_NLAST "Map is not the last element"
# define E_T_EXTS "Invalid texture file extension"
# define E_HITORMISS "Missing texture or is after the map"
# define E_MAPCHAR "Invalid map character"
# define E_MULTIPOS "Multiple starting position for the player"
# define E_MISSPOS "Missing player starting position"
# define E_CLOSE "Map is not closed"
# define E_NOMAP "No map found bg"
# define E_INITMLX "Could not iniate the mlx pointer"
# define E_MLXWIN "Could not creat the mlx window"

# define WINAME "GOAT3D"
# define WINX 1400
# define WINY 1000
# define MIN_X_OR_Y ((WINX) < (WINY) ? (WINX) : (WINY))
# define MIN_DIM MIN_X_OR_Y / 4
# define PI 3.14159265358979323846
# define NO 1.57079632679489661923
# define SO (3 * PI) / 2
# define WE PI * 1
# define TILE_SIZE 21
# define BIG_TILE_SIZE 50
# define EA 0
// # define SPEED_M 0.1
// # define SPEED_C 0.04
# define SPEED_M 0.01
# define SPEED_C 0.005
# define WALL_TEXT_CARRE 64
# define FLOOR 0x000000
# define SKY 0x000000
# define HALT 1
# define WALK 0
# define ATTACK 2
# define DEATH 3
# define DAMAGE 4
# define FOV 1
# define CIRCLE_COLOR 0x000000
# define MINI_W 0x000000
# define MINI_S 0xFFFFFF

typedef struct s_mlx
{
	void		*mlx_ptr;
	void		*mlx_win;
}				t_mlx;

typedef struct s_textures
{
	void		*img;
	int			h;
	int			w;
	int			bpp;
	char		*data;
	int			frame;
	int			animating;
	double		last_time;
	double		frame_delay;
	int			size_line;
	int			endian;
}				t_texture;

typedef struct s_enemy
{
	int			hp;
	char		name[10];
	t_texture	texture[5][4];
	int			pixel;
	int			mapX;
	int			mapY;
	int			i_count;
	double		posX;
	double		posY;
}				t_enemy;

typedef struct s_ray
{
	double		posX;
	double		posY;
	int			mapX;
	int			mapY;
	double		dirangle;
	double		dirX;
	double		diry;
	double		dist;
	double		deltaX;
	double		deltaY;
	double		hit;
	int			stepX;
	int			stepY;

}				t_ray;

typedef struct s_player
{
	double		posX;
	double		posY;
	double		dirangle;
	double		playerdirX;
	double		playerdirY;
	double		new_x;
	double		new_y;
	double		new_dir;
	int			stepx;
	int			stepy;
	int			flag;
	double		safetyx;
	double		safetyy;
	bool		up;
	bool		down;
	bool		right;
	bool		left;
	bool		side_r;
	bool		side_l;
}				t_player;

typedef struct s_game
{
	char		**map;
	char		**cpy_map;
	int			map_max_x;
	int			map_max_y;
	int			map_pos;
	int			map_rows;
	int			map_column;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			ceiling[3];
	int			floor[3];
	int			fd;
	char		player_dir;
	double		playerdirX;
	double		playerdirY;
	int			map_x;
	int			map_y;
	t_texture	pic;
	t_mlx		*mlx;
	t_texture	gun[4];
	t_texture	wall[4];
	t_player	player;
	t_enemy		ennemy;
}				t_game;

t_game			*parsing(char *file);
void			read_file(char *file, t_game *game);
void			free_exit(t_game *game, int line, char *file, char *error);
t_game			*init_game(void);
char			*get_texture_path(char *line, t_game *game);
void			print_struct(t_game *game);
void			print_tabsquare(char **tab);
void			free_taboftab(char **tab);
bool			look_like_a_map_line(char *line);
void			print_tabint(int *tab, int len);
void			init_mlx(t_game *game);
void			init_mlx2(t_mlx *mlx);
int				key_hook(int keycode, t_game *game);
void			draw_rectangle(t_texture *textures, int x, int y, int color);
void			draw_gun(t_game *game, char *data, int bpp);
void			movements(t_game *game, double angle_shift);
void			direction(t_game *game, char side);
void			check_moves(t_game *game);
double			get_current_time(void);
void			update_gun_animation(t_game *game);
void			mini_draw_map(t_game *game, t_texture *texture);
void			mini_draw_arrow(t_game *game, t_texture *texture);
void			draw_filled_circle(t_texture *textures, int start_x,
					int start_y, int radius);
void			draw_ray_in_data(t_game *game, t_texture *textures, int x0,
					int y0, int x1, int y1, int color);
void			draw_loop(t_game *game, int line_size, float offset_x,
					float offset_y);
float			find_offset(t_game *game, double playerpos, int max);
t_player		init_player_struct(void);
int				init_player(t_game *game);
int				india(t_game *game);
double			get_current_time(void);
void			draw_arrow(t_game *game, t_texture *textures);
int				key_release(int keycode, t_game *game);
void			draw_crosshair(t_game *game, char *data, int size_line, int bpp,
					int color);

#endif