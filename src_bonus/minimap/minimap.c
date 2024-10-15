/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:08:47 by pscala            #+#    #+#             */
/*   Updated: 2024/10/15 17:59:05 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_element_in_map(t_game *game, int screen_x, int screen_y)
{
	int	i;

	if (game->map[game->map_y][game->map_x] == '1')
		draw_rectangle(&game->pic, screen_x, screen_y, MINI_W);
	else
		draw_rectangle(&game->pic, screen_x, screen_y, MINI_S);
	i = 0;
	while (i < game->nb_door)
	{
		if ((game->door[i].map_y == game->map_y
				&& game->door[i].map_x == game->map_x)
			&& (game->door[i].state == IS_OPEN))
		{
			draw_rectangle(&game->pic, screen_x, screen_y, MINI_D);
		}
		i++;
	}
}

void	draw_loop(t_game *game, int line_size, float offset_x, float offset_y)
{
	float	screen_x;
	float	screen_y;

	game->map_y = 0;
	while (game->map_y < game->map_max_y)
	{
		game->map_x = 0;
		line_size = (int)ft_strlen(game->map[game->map_y]);
		while (game->map_x < line_size)
		{
			screen_x = game->map_x * TILE_SIZE + offset_x;
			screen_y = game->map_y * TILE_SIZE + offset_y;
			if (screen_x + TILE_SIZE > 0 && screen_x < MIN_DIM && screen_y
				+ TILE_SIZE > 0 && screen_y < MIN_DIM)
			{
				draw_element_in_map(game, screen_x, screen_y);
			}
			game->map_x++;
		}
		game->map_y++;
	}
}

float	find_offset(t_game *game, double playerpos, int max)
{
	if (playerpos * TILE_SIZE < MIN_DIM / 2.0f)
		return (0.0f);
	else if (playerpos * TILE_SIZE > max * TILE_SIZE - MIN_DIM / 2.0f)
		return (MIN_DIM - max * TILE_SIZE);
	else
		return ((MIN_DIM / 2.0f) - playerpos * TILE_SIZE);
}

void	mini_draw_map(t_game *game, t_texture *textures)
{
	float	screen_x;
	float	screen_y;
	int		line_size;
	float	offset_x;
	float	offset_y;

	offset_x = 0.0f;
	offset_y = 0.0f;
	if (game->map_max_x * TILE_SIZE > MIN_DIM)
		offset_x = find_offset(game, game->player.posx, game->map_max_x);
	if (game->map_max_y * TILE_SIZE > MIN_DIM)
		offset_y = find_offset(game, game->player.posy, game->map_max_y);
	draw_loop(game, line_size, offset_x, offset_y);
	mini_draw_arrow(game, textures);
}

void	draw_enemies_on_minimap(t_game *game, t_texture *textures, t_utils *u)
{
	int	g;
	int	screen_x;
	int	screen_y;

	g = 0;
	while (g < game->bot_nb)
	{
		screen_x = game->ennemy[g].posx * TILE_SIZE + u->offset_x;
		screen_y = game->ennemy[g].posy * TILE_SIZE + u->offset_y;
		if (game->ennemy[g].is_active == false)
		{
			g++;
			continue ;
		}
		else if (screen_x > 0 && screen_x < MIN_DIM && screen_y > 0
			&& screen_y < MIN_DIM && game->ennemy[g].animating == 0)
			draw_filled_circle(textures, screen_x, screen_y, 0x0000FF);
		else if (screen_x > 0 && screen_x < MIN_DIM && screen_y > 0
			&& screen_y < MIN_DIM && game->ennemy[g].animating != 0)
			draw_filled_circle(textures, screen_x, screen_y, 0xFF0000);
		g++;
	}
}
