/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:28:20 by kasingh           #+#    #+#             */
/*   Updated: 2024/12/24 12:41:04 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"


void	update_door_distance(t_game *game, t_door *door)
{
	double	delta_x;
	double	delta_y;

	delta_x = game->player.posx - ((double)door->map_x + 0.5);
	delta_y = game->player.posy - ((double)door->map_y + 0.5);
	door->distance = sqrt(delta_x * delta_x + delta_y * delta_y);
}

bool	is_player_near_door(t_game *game, t_door *door)
{
	if (door->map_y != (int)game->player.posy
		|| door->map_x != (int)game->player.posx)
	{
		if (door->distance <= 2 && door->door_hit >= WINX / 2)
			return (true);
	}
	return (false);
}

void	play_door_sound(t_game *game)
{
	ALint	state;

	if (USE_SOUND == true)
	{
		alGetSourcei(game->sound[DOOR].source, AL_SOURCE_STATE, &state);
		if (state != AL_PLAYING)
			play_sound(&game->sound[DOOR], false);
	}
}

void	toggle_door_state(t_game *game, t_door *door)
{
	// if (door->state == IS_OPEN)
	// {
	// 	game->map[door->map_y][door->map_x] = '1';
	// 	door->state = IS_CLOSE;
	// }
	// else
	// {
	// 	game->map[door->map_y][door->map_x] = '0';
	// 	door->state = IS_OPEN;
	// }
	if (door->state == IS_CLOSE)
        door->state = IS_OPENING;
    else if (door->state == IS_OPEN)
 	{       
		door->state = IS_CLOSING;
		game->map[door->map_y][door->map_x] = '1';
	}
}

void	check_door(t_game *game)
{
	int		i;
	t_door	*door;

	if (game->check_door == 0)
		return ;
	i = 0;
	while (i < game->nb_door)
	{
		door = &game->door[i];
		update_door_distance(game, door);
		if (is_player_near_door(game, door))
		{
			play_door_sound(game);
			toggle_door_state(game, door);
		}
		i++;
	}
	game->check_door = 0;
}
