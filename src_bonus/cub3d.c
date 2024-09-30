/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:09:12 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/30 14:27:22 by kasingh          ###   ########.fr       */
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
		speed_cam = fabs(delta_x) * 0.0005;
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

int	loop_hook(t_game *game)
{
	void		*img_ptr;
	char		*datax;
	t_texture	*texture;

	texture = &game->pic;
	int bpp, size_line, endian;
	check_moves(game);
	draw_arrow(game, texture);
	mini_draw_map(game, texture);
	drawallbot(game, texture->data);
	checkbotmoves(game);
	draw_crosshair(game, texture->data, texture->size_line, texture->bpp,
		CROSSHAIR);
	update_gun_animation(game);
	draw_gun(game, texture->data, texture->bpp);
	draw_health(game, texture);
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
	if (mlx_hook(game->mlx->mlx_win, 6, (1L << 6), mouse_move, game) == 0)
	{
		printf("Failed to set mouse move hook\n");
	}
	else
	{
		printf("Mouse move hook set successfully\n");
	}
	mlx_hook(game->mlx->mlx_win, 04, (1L << 2), mouse_press, game);
	mlx_loop(game->mlx->mlx_ptr);
	// ft_calloc(1,sizeof(t_game));
	// print_struct(game);
	return (0);
}
