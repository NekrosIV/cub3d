/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:05:19 by pscala            #+#    #+#             */
/*   Updated: 2024/10/15 12:31:11 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	check_bouton_prese(t_game *game)
{
	if (game->menu == true && (game->state_menu == P_EXIT
			|| game->state_menu == N_EXIT))
		india(game);
	else if (game->menu == true && (game->state_menu == PAUSE
			|| game->state_menu == NEW_GAME))
	{
		game->menu = false;
		game->is_game_start = true;
	}
}

void	choose_state_menu(t_game *game, int keycode)
{
	if (keycode == XK_Up)
	{
		if (game->is_game_start == false)
			game->state_menu = NEW_GAME;
		else
			game->state_menu = PAUSE;
	}
	else if (keycode == XK_Down)
	{
		if (game->is_game_start == false)
			game->state_menu = N_EXIT;
		else
			game->state_menu = P_EXIT;
	}
	if (keycode == XK_p)
	{
		if (game->is_game_start == true)
		{
			game->menu = true;
			game->state_menu = PAUSE;
		}
	}
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		free_exit(game, 0, NULL, "EOG");
	else if (keycode == XK_w)
		game->player.up = true;
	else if (keycode == XK_s)
		game->player.down = true;
	else if (keycode == XK_d)
		game->player.right = true;
	else if (keycode == XK_a)
		game->player.left = true;
	else if (keycode == XK_Left)
		game->player.side_l = true;
	else if (keycode == XK_Right)
		game->player.side_r = true;
	else if (keycode == XK_Up || keycode == XK_Down || keycode == XK_p)
		choose_state_menu(game, keycode);
	else if (keycode == XK_Return)
		check_bouton_prese(game);
	if (keycode == XK_e)
		game->check_door = 1;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == XK_w)
		game->player.up = false;
	else if (keycode == XK_s)
		game->player.down = false;
	else if (keycode == XK_d)
		game->player.right = false;
	else if (keycode == XK_a)
		game->player.left = false;
	else if (keycode == XK_Left)
		game->player.side_l = false;
	else if (keycode == XK_Right)
		game->player.side_r = false;
	return (0);
}
