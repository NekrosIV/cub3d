/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:09:12 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/08 16:21:24 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	mouse_move(int x, int y, t_game *game)
{
	int			center_x;
	int			center_y;
	static int	ignore_event = 0;
	int			delta_x;
	char		side;
	double		speed_cam;

	center_x = WINX / 2;
	center_y = WINY / 2;
	if (ignore_event)
	{
		ignore_event = 0;
		return (0);
	}
	delta_x = x - center_x;
	if (delta_x != 0)
	{
		if (delta_x > 0)
			side = 'd';
		else
			side = 'g';
		speed_cam = fabs((delta_x)*0.0005);
		direction(game, side, speed_cam);
	}
	ignore_event = 1;
	mlx_mouse_move(game->mlx->mlx_ptr, game->mlx->mlx_win, center_x, center_y);
	return (0);
}

int	mouse_press(int button, int x, int y, t_game *game)
{
	if (button == 1)
	{
		if (game->gun->animating == 0)
		{
			game->gun->animating = 1;
			game->do_damage = 1;
		}
	}
	return (0);
}

void	draw_health(t_game *game, t_texture *texture)
{
	int		lenght;
	int		height;
	double	hp;
	int		color;
	int		x;
	int		y;
	int		reset;

	lenght = WINX / 5;
	height = WINY / 50;
	hp = (double)game->player.hp;
	hp = hp / HPP;
	if (hp > 0.5)
		color = GREENHP;
	else if (hp > 0.2)
		color = ORANGEHP;
	else
		color = BRIGHTRED;
	lenght = (int)((double)lenght * hp);
	x = 0;
	y = WINY - height;
	reset = y;
	while (x < WINX / 5)
	{
		while (y < reset + height)
		{
			*((int *)texture->data + x + y * WINX) = REDHP;
			y++;
		}
		x++;
		y = reset;
	}
	x = 0;
	y = reset;
	while (x < lenght)
	{
		while (y < reset + height)
		{
			*((int *)texture->data + x + y * WINX) = color;
			y++;
		}
		x++;
		y = reset;
	}
}

void	bot_attack(t_game *game, t_texture *texture)
{
	int		i;
	double	current_time;

	current_time = get_current_time();
	i = 0;
	while (i < game->bot_nb)
	{
		if (current_time - game->ennemy[i].last_time_hit <= 0.5)
			draw_dammage(game, &game->ennemy[i], &game->player);
		i++;
	}
}
void	check_door(t_game *game)
{
	double	delta_x;
	double	delta_y;
	int		i;

	if (game->check_door == 0)
		return ;
	i = 0;
	while (i < game->nb_door)
	{
		delta_y = game->player.posY - ((double)game->door[i].map_y + 0.5);
		delta_x = game->player.posX - ((double)game->door[i].map_x + 0.5);
		game->door[i].distance = sqrt(delta_x * delta_x + delta_y * delta_y);
		printf("d = %f\n", game->door[i].distance);
		if ((game->door[i].map_y != (int)game->player.posY
				|| game->door[i].map_x != (int)game->player.posX))
		{
			if (game->door[i].distance <= 1.5 && game->door[i].door_hit >= WINX
				/ 2)
			{
				if (game->door[i].state == OPEN)
				{
					game->map[game->door[i].map_y][game->door[i].map_x] = '1';
					game->door[i].state = CLOSE;
				}
				else
				{
					game->map[game->door[i].map_y][game->door[i].map_x] = '0';
					game->door[i].state = OPEN;
				}
			}
		}
		i++;
	}
	game->check_door = 0;
}
void	draw_menu(t_game *game, t_texture *texture,int state, int frame)
{
	double	x_ratio;
	double	y_ratio;
	int		x;
	int		y;
	double	x_img;
	double	y_img;
	int		img_index;
	int		screen_index;
	int		ignore;


	x_ratio = (double)game->menu_texture[state][frame].w / (double)WINX;
	y_ratio = (double)game->menu_texture[state][frame].h / (double)WINY;
	ignore = *((int *)game->menu_texture[state][frame].data);
	for (x = 0; x < WINX; x++)
	{
		for (y = 0; y < WINY; y++)
		{
			x_img = x * x_ratio;
			y_img = y * y_ratio;
			img_index = ((int)y_img) * game->menu_texture[state][frame].w + (int)x_img;
			screen_index = y * WINX + x;
			// if (frame != 5 && frame != 4)
				*((int *)game->pic.data
						+ screen_index) = *((int *)game->menu_texture[state][frame].data
						+ img_index);
			// else if (*((int *)game->menu_texture[state][frame].data + img_index) != ignore)
			// 	*((int *)game->pic.data
			// 			+ screen_index) = *((int *)game->menu_texture[state][frame].data
			// 			+ img_index);
		}
	}
}

void draw_good_state_menu(t_game *game, t_texture *texture)
{
	double	current_time;
	static int frame = 0;

	current_time = get_current_time();
	if (current_time - game->menu_texture[0]->last_time >= game->menu_texture[0]->frame_delay)
	{
		if(frame == 0)
			frame = 1;
		else 
			frame = 0;
		game->menu_texture[0]->last_time = current_time;
	}
	draw_menu(game,texture,game->state_menu,frame);
}

int	loop_hook(t_game *game)
{
	void		*img_ptr;
	char		*datax;
	t_texture	*texture;

	texture = &game->pic;
	int bpp, size_line, endian;
	if (game->menu == false)
	{
		(check_moves(game));
		check_door(game);
		draw_arrow(game, texture);
		mini_draw_map(game, texture);
		drawallbot(game, texture->data);
		checkbotmoves(game);
		draw_crosshair(game, texture->data, texture->size_line, texture->bpp,
			CROSSHAIR);
		update_gun_animation(game);
		draw_gun(game, texture->data, texture->bpp);
		bot_attack(game, texture);
		draw_health(game, texture);
	}
	else
		draw_good_state_menu(game, texture);
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->mlx_win,
		texture->img, 0, 0);
	if (game->player.hp <= 0)
	{
		ft_printf(RED "YOU DIED *rip*\n" RESET);
		free_exit(game, 0, NULL, "EOG");
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		return (1);
	game = parsing(av[1]);
	init_player(game);
	init_mlx(game);
	mlx_loop_hook(game->mlx->mlx_ptr, loop_hook, game);
	mlx_hook(game->mlx->mlx_win, 17, 0, india, game);
	mlx_hook(game->mlx->mlx_win, 02, (1L << 0), key_hook, game);
	mlx_hook(game->mlx->mlx_win, 03, (1L << 1), key_release, game);
	mlx_hook(game->mlx->mlx_win, 6, (1L << 6), mouse_move, game);
	mlx_hook(game->mlx->mlx_win, 04, (1L << 2), mouse_press, game);
	mlx_loop(game->mlx->mlx_ptr);
	// ft_calloc(1,sizeof(t_game));
	// print_struct(game);
	return (0);
}
