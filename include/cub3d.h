/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:09:44 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/16 13:33:59 by kasingh          ###   ########.fr       */
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
# define E_MLXIMG "Failed to load image"
# define E_MLXDATA "Failed to get data address for image"

# define WINAME "GOAT3D"
# define N 0
# define S 1
# define W 2
# define E 3
# define WINX 1200
# define WINY 900
# define PI 3.14159265358979323846
# define NO 1.57079632679489661923
# define WE PI
# define TILE_SIZE 21
# define BIG_TILE_SIZE 50
# define EA 0
# define SPEED_BOT 0.005
// # define SPEED_M 0.01
// # define SPEED_C 0.008
# define SPEED_M 0.1
# define SPEED_C 0.02
# define FLOOR 0xFF7300
# define SKY 0x4B0082
# define FOV 1
# define CIRCLE_COLOR 0xFF7300
# define MINI_W 0x4B0082
# define MINI_S 0x00FFFF
# define CROSSHAIR 0xFF7300

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
	int			size_line;
	int			endian;
}				t_texture;

typedef struct s_ray
{
	double		posx;
	double		posy;
	int			mapx;
	int			mapy;
	double		dirangle;
	double		dirx;
	double		diry;
	double		dist;
	double		deltax;
	double		deltay;
	double		hit;
	int			stepx;
	int			stepy;
	double		start_y;
	double		length;
	double		end_x;
	double		end_y;
	double		ray;
	double		offset;
	double		fov;
	double		sidedistx;
	double		sidedisty;
	double		ray_dx;
	double		ray_dy;
	int			ray_hit;
	int			last_hit;
	double		perp_length;
	double		y_wall;
	double		line_h;
	double		ratio;
	int			wall;
	double		pos_texture;
}				t_ray;

typedef struct s_player
{
	double		posx;
	double		posy;
	double		dirangle;
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
	int			hp;
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
	char		*wall_path[4];
	int			ceiling[3];
	int			floor[3];
	int			floor_hexa;
	int			ceiling_hexa;
	int			fd;
	char		player_dir;
	int			map_x;
	int			map_y;
	int			line_thickness;
	int			crosshair_size;
	int			center_x;
	int			center_y;
	t_texture	pic;
	t_mlx		*mlx;
	t_texture	wall[4];
	t_player	player;
	double		profondeur[WINX];
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
void			movements(t_game *game, double angle_shift);
void			direction(t_game *game, char side, double speed_cam);
void			check_moves(t_game *game);
double			get_current_time(void);
void			update_gun_animation(t_game *game);
void			draw_loop(t_game *game, int line_size, float offset_x,
					float offset_y);
float			find_offset(t_game *game, double playerpos, int max);
t_player		init_player_struct(void);
int				init_player(t_game *game);
int				india(t_game *game);
double			get_current_time(void);
void			draw_arrow(t_game *game, t_texture *textures);
int				key_release(int keycode, t_game *game);
void			draw_crosshair(t_texture *textures,t_game *game, int color);
void			calculate_wall_height(t_ray *ray, t_game *game, int i);
void			determine_wall_and_pos_texture(t_ray *ray, t_game *game);
void			adjust_texture_coordinates(t_ray *ray, t_game *game);
void			draw_pixels(t_ray *ray, t_game *game, t_texture *textures,
					int i);
void			init_ray(t_ray *ray, t_game *game);
void			calculate_step_and_sidedist(t_ray *ray, t_game *game);
void			perform_dda(t_ray *ray, t_game *game);
void			free_texture_path(t_game *game);
void			free_mlx(t_game *game, t_mlx *mlx);
void			free_wall_texture(t_game *game);
void			free_everything(t_game *game);
int				rgb_to_hexa(int rgb[3]);
int				is_good_int(char *str, char *int_limit);
int				is_positive_digit(char *str);
int				number_of_value(char *str);
void			fill_tab_rgb(t_game *game, char *line, char flag);
bool			multi_def(t_game *game, char *line, char flag);
void			trime_line(t_game *game, char *line);
bool			textures_filled(t_game *game);
int				skip_e_space(char *str, bool flag);
void			count_tab_len(t_game *game, char *line, char **tab);
int				check_if_dir(char *file);
int				check_file(char *file, t_game *game);
bool			check_if_its_map(t_game *game, char *line);
void			check_line(t_game *game, char *line);
void			fill_map(t_game *game, char *line);
void			pre_pars_map(t_game *game);
void			pars_map(t_game *game);
void			replace_space_in_map(t_game *game);
void			init_map(t_game *game, char *file);
bool			check_valid_char(char c);
bool			check_play_pos(char c);
void			cpy_map(t_game *game);
void			flood_fill(t_game *game, char **map, int x, int y);
void			pre_flood_fill(t_game *game);
void			get_max_x_y(t_game *game);
void			initialize_safety_offsets(t_player *player);
void			calculate_new_position(t_player *player);
void			determine_grid_steps(t_player *player);
void			check_diagonal_collision(t_game *game, t_player *player);
void			adjust_player_posx(t_player *player);
void			adjust_player_posy(t_player *player);
void			attempt_move_player(t_game *game, t_player *player);

#endif