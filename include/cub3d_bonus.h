/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:09:44 by kasingh           #+#    #+#             */
/*   Updated: 2024/12/27 19:05:59 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../libft/include/libft.h"
# include "../mlx/mlx.h"
# include "../vendor/lib/openal/include/AL/al.h"
# include "../vendor/lib/openal/include/AL/alc.h"
# include <X11/keysym.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdint.h>
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
# define E_DIR "Wrong argument: Is a directory"
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
# define E_AUDIO "Couldnt load audio file"

# define DR_WAV_IMPLEMENTATION
# define WINAME "GOAT3D"
# define N 0
# define S 1
# define W 2
# define E 3
# define F 4
# define D 5
# define WINX 1520
# define WINY 1080
# if WINX < WINY
#  define M WINX
# else
#  define M WINY
# endif
# define PI 3.14159265358979323846
# define NO 1.57079632679489661923
# define WE PI
# define EA 0
# define TILE_SIZE 21
# define BIG_TILE_SIZE 50
// # define SPEED_BOT 0.005
// # define SPEED_M 0.01
// # define SPEED_C 0.0001
# define SPEED_BOT 0.05
# define SPEED_M 0.1
# define SPEED_C 0.002
# define WALL_TEXT_CARRE 64
# define FLOOR 0xFF7300
# define SKY 0x4B0082
# define HALT 0
# define WALK 1
# define ATTACK 2
# define DEATH 3
# define DAMAGE 4
# define NEW_GAME 0
# define N_EXIT 1
# define PAUSE 2
# define P_EXIT 3
# define F_MENU 4
# define OST 0
# define GUN 1
# define STEP 2
# define DOOR 3
# define E_HURT 4
# define E_DEAD 5
# define E_TRIG 6
# define DAMAGE_BOT 50
# define FOV 1
# define CIRCLE_COLOR 0xFF7300
# define CROSSHAIR 0xFF7300
# define MINI_W 0xFF7300
# define MINI_F 0x121336
# define MINI_D 0x00FF00
# define RADIUS 4
# define SGUNRANGE 5
# define BOT_SHOOT 5
# define TRIGGERBOT 15
# define CROSSHAIR 0xFF7300
# define REDHP 0x8A0707
# define BRIGHTRED 0xFF6666
# define ORANGEHP 0xFFB347
# define GREENHP 0x39FF14
# define HPP 100

# define USE_SOUND 0

typedef enum e_door_state
{
	IS_CLOSE,
	IS_OPEN,
	IS_OPENING,
	IS_CLOSING
}				t_door_state;

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
	int			pixel;
	int			mapx;
	int			mapy;
	int			i_count;
	double		posx;
	double		posy;
	double		distance;
	int			bothit;
	int			frame;
	int			action;
	double		last_time;
	double		last_time_hit;
	int			animating;
	double		last_time2;
	double		frame_delay;
	bool		takedmg;
	bool		hit_player;
	bool		is_active;
}				t_enemy;

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
	double		distance;
	double		y_wall;
	double		line_h;
	double		ratio;
	int			door_index;
	double		sky_ratio;
	double		y_sky;
	double		skyx;
	int			wall;
	double		pos_texture;
	int			ignore;
	int			two_time;
	bool		store_door;
	int			stored_door_index;
	bool		stored_last_hit;
	double		stored_perp_length;
	double		stored_sidedistx;
	double		stored_sidedisty;
}				t_ray;

typedef struct s_player
{
	double		posx;
	double		posy;
	double		dirangle;
	double		playerdirx;
	double		playerdiry;
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

typedef struct s_door
{
	int			map_y;
	int			map_x;
	int			frame;
	int			state;
	double		open_state;
	double		last_time;
	double		distance;
	int			door_hit;
}				t_door;

typedef struct s_sound
{
	ALuint		buffer;
	ALuint		source;
	ALenum		format;
	ALsizei		size;
	ALsizei		freq;
	ALvoid		*data;
	size_t		data_size;
}				t_sound;

typedef struct s_utils
{
	double		dx;
	double		dy;
	double		distance;
	double		distancesquared;
	double		angle;
	int			screenx;
	int			screeny;
	double		line_h;
	int			starty;
	int			endy;
	int			startx;
	int			endx;
	int			xi;
	int			yi;
	double		difference;
	double		pixelx;
	double		ratio;
	double		x_ratio;
	double		y_ratio;
	double		x_img;
	double		y_img;
	int			i;
	int			j;
	int			ignore;
	double		posx;
	double		posy;
	double		deltax;
	double		deltay;
	int			min_map_x;
	int			max_map_x;
	int			min_map_y;
	int			max_map_y;
	int			map_x;
	int			map_y;
	int			steps;
	double		radius;
	float		tile_width;
	float		tile_height;
	float		offset_x;
	float		offset_y;
	int			lenght;
	int			height;
	double		hp;
	int			reset;
	int			color;
	int			center_x;
	int			center_y;
	char		side;
	int			img_index;
	int			screen_index;
}				t_utils;

typedef struct s_game
{
	char		**map;
	char		**cpy_map;
	int			map_max_x;
	int			map_max_y;
	int			map_pos;
	int			map_rows;
	int			map_column;
	char		*wall_path[5];
	int			floor[3];
	int			floor_hexa;
	int			ceiling_hexa;
	int			fd;
	char		player_dir;
	double		playerdirx;
	double		playerdiry;
	int			map_x;
	int			map_y;
	int			line_thickness;
	int			crosshair_size;
	int			center_x;
	int			center_y;
	int			bot_nb;
	int			m_d;
	bool		do_damage;
	bool		loading_page;
	t_texture	pic;
	t_mlx		*mlx;
	t_texture	gun[39];
	t_texture	loading[56];
	t_texture	ceiling[64];
	t_texture	wall[25];
	t_texture	sol;
	t_texture	botext[5][4];
	t_player	player;
	t_enemy		*ennemy;
	t_texture	dammage;
	t_texture	menu_texture[4][2];
	int			state_menu;
	bool		is_game_start;
	int			mouse_x;
	int			mouse_y;
	float		mouse_cam;
	double		profondeur[WINX];
	bool		hit_player;
	int			nb_door;
	t_door		*door;
	int			check_door;
	bool		menu;
	t_sound		sound[7];
	ALCdevice	*device;
	ALCcontext	*context;
}				t_game;

void			parsing(char *file, t_game *game);
void			read_file(char *file, t_game *game);
void			free_exit(t_game *game, int line, char *file, char *error);
void			free_mlx(t_game *game, t_mlx *mlx);
void			delete_audios(t_game *game);
int				india(t_game *game);
void			init_game(t_game *game);
char			*get_texture_path(char *line, t_game *game);
void			print_struct(t_game *game);
void			print_tabsquare(char **tab);
void			free_taboftab(char **tab);
bool			look_like_a_map_line(char *line);
void			print_tabint(int *tab, int len);
void			init_mlx(t_game *game);
void			build_enemy_texture_path(char *texture_path, size_t path_size,
					int state, int frame);
void			load_texture_into_game(t_game *game, char *texture_path,
					int state, int frame);
bool			should_break_enemy_loop(int state, int frame);
void			build_menu_texture_path(char *texture_path, size_t path_size,
					int state, int frame);
void			load_menu_texture_into_game(t_game *game, char *texture_path,
					int state, int frame);
int				key_hook(int keycode, t_game *game);
void			draw_rectangle(t_texture *textures, int x, int y, int color);
void			draw_filled_circle(t_texture *textures, int x, int y,
					int color);
void			draw_gun(t_game *game, char *data);
void			movements(t_game *game, double angle_shift);
void			direction(t_game *game, char side, double speed_cam);
void			check_moves(t_game *game);
double			get_current_time(void);
void			update_gun_animation(t_game *game);
void			mini_draw_map(t_game *game, t_texture *texture);
void			mini_draw_arrow(t_game *game, t_texture *texture);
void			draw_filled_circle(t_texture *textures, int start_x,
					int start_y, int color);
void			draw_enemies_on_minimap(t_game *game, t_texture *textures,
					t_utils *u);
void			draw_ray_in_data(t_texture *textures, t_utils *ut);
void			draw_loop(t_game *game, int line_size, float offset_x,
					float offset_y);
float			find_offset(t_game *game, double playerpos, int max);
t_player		init_player_struct(void);
int				init_player(t_game *game);
double			get_current_time(void);
void			draw_arrow(t_game *game, t_texture *textures);
void			draw_floor(t_game *game, t_texture *textures);
void			init_ray(t_ray *ray, t_game *game);
void			calculate_step_and_sidedist(t_ray *ray, t_game *game);
void			calculate_wall_height(t_ray *ray, t_game *game, int i);
void			determine_wall_and_pos_texture(t_ray *ray, t_game *game);
void			adjust_texture_coordinates(t_ray *ray, t_game *game);
int				key_release(int keycode, t_game *game);
void			draw_crosshair(t_texture *texture, t_game *game, int color);
void			drawenemy(t_game *game, char *data, t_enemy *enemy);
void			dammage(t_game *game, t_enemy *enemy);
int				mouse_move(int x, int y, t_game *game);
int				is_bot_collision(t_enemy *bot1, t_enemy *bot2,
					double threshold);
int				is_collision_with_others(t_game *game, t_enemy *current_bot,
					double new_posX, double new_posY);
int				is_wall(t_game *game, double x, double y, double radius);
bool			has_wall_between(t_game *game, t_enemy *bot);
void			update_enemy_animation(t_game *game, t_enemy *bot);
bool			try_move_bot(t_game *game, t_enemy *bot, double dx, double dy);
void			movebot(t_game *game, t_enemy *bot);
void			drawallbot(t_game *game, char *data);
void			checkbotmoves(t_game *game);
void			bot_attack(t_game *game, t_texture *texture);
void			draw_dammage(t_game *game, t_enemy *bot, t_player *player);
int				check_collision_in_cell(t_game *game, double x, double y,
					t_utils *u);
bool			is_out_of_bounds_or_wall(t_game *game, int map_x, int map_y);
int				init_openal(t_game *game);
void			close_openal(t_game *game);
t_sound			load_sound(t_game *game, const char *filename);
void			play_sound(t_sound *sound, int loop);
void			init_sound(t_game *game);
void			update_enemy_distance(t_game *game, t_enemy *enemy);
void			sort_enemies_by_distance(t_game *game);
void			check_door(t_game *game);
void			draw_good_state_menu(t_game *game, t_texture *texture);
void			draw_health(t_game *game, t_texture *texture);
int				mouse_press(int button, int x, int y, t_game *game);
int				mouse_move(int x, int y, t_game *game);
void			perform_dda(t_ray *ray, t_game *game);
void			get_max_x_y(t_game *game);
void			pre_flood_fill(t_game *game);
void			cpy_map(t_game *game);
void			flood_fill(t_game *game, char **map, int x, int y);
bool			look_like_a_map_line(char *line);
bool			check_if_its_map(t_game *game, char *line);
void			check_line(t_game *game, char *line);
void			check_player(t_game *game, int x, int y);
void			fill_map(t_game *game, char *line);
void			pre_pars_map(t_game *game);
void			pars_map(t_game *game);
void			replace_space_in_map(t_game *game);
void			init_map(t_game *game, char *file);
void			fill_map(t_game *game, char *line);
void			pre_pars_map(t_game *game);
void			pars_map(t_game *game);
void			replace_space_in_map(t_game *game);
void			init_map(t_game *game, char *file);
int				check_if_dir(char *file);
int				check_file(char *file, t_game *game);
int				rgb_to_hexa(int rgb[3]);
int				is_good_int(char *str, char *int_limit);
int				is_positive_digit(char *str);
int				number_of_value(char *str);
void			fill_tab_rgb(t_game *game, char *line, char flag);
void			init_bot(t_game *game, int i, int x, int y);
void			init_door(t_game *game, int i, int x, int y);
void			search_bot(t_game *game, int x, int y, int *i);
void			search_door(t_game *game, int x, int y, int *j);
void			search_things(t_game *game);
bool			multi_def(t_game *game, char *line, char flag);
void			trime_line(t_game *game, char *line);
char			*get_texture_path(char *line, t_game *game);
bool			textures_filled(t_game *game);
void			count_tab_len(t_game *game, char *line, char **tab);
void			put_door(t_game *game);
bool			check_valid_char(char c);
bool			check_play_pos(char c);
int				skip_e_space(char *str, bool flag);
void			determine_grid_steps(t_player *player);
void			check_diagonal_collision(t_game *game, t_player *player);
void			attempt_move_player(t_game *game, t_player *player);
void			int_enemy_texture(t_game *game);
void			init_menu_texture(t_game *game);
void			init_wall(t_game *game);
void			init_gun_texture(t_game *game);
void			load_image_to_game(t_game *game, t_texture *texture);
void			init_ceiling_texture(t_game *game);
void			init_loading_texture(t_game *game);

#endif