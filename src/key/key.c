/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:05:19 by pscala            #+#    #+#             */
/*   Updated: 2024/09/28 14:04:12 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
