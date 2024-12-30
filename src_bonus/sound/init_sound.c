/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:48:51 by kasingh           #+#    #+#             */
/*   Updated: 2024/12/30 17:24:54 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_sound(t_game *game)
{
	if (!USE_SOUND)
		return ;
	init_sound_engine(game);
	load_sound(game, "sfx/berserkbro.wav", 0.4f, true, OST);
	load_sound(game, "sfx/lasergun5.wav", 0.5f, false, GUN);
	load_sound(game, "sfx/LegoYodaDeath.wav", 0.8f, false, E_DEAD);
	load_sound(game, "sfx/mauvaisenouvelle.wav", 0.6f, false, E_TRIG);
	load_sound(game, "sfx/hurt.wav", 0.8f, false, E_HURT);
	load_sound(game, "sfx/footstep.wav", 0.8f, false, STEP);
	load_sound(game, "sfx/door.wav", 0.5f, false, DOOR);
	play_sound(game, OST);
}

void	stop_sound(t_game *game, int slot)
{
	if (slot < 0 || slot >= NUM_SOUNDS)
		return ;
	if (!game->sound[slot].used)
		return ;
	if (ma_sound_is_playing(&game->sound[slot].sound))
		ma_sound_stop(&game->sound[slot].sound);
}

void	unload_all_sounds(t_game *game)
{
	for (int i = 0; i < NUM_SOUNDS; i++)
	{
		if (game->sound[i].used)
		{
			stop_sound(game, i);
			ma_sound_uninit(&game->sound[i].sound);
			if (game->sound[i].filepath)
				free(game->sound[i].filepath);
			memset(&game->sound[i], 0, sizeof(t_sound));
		}
	}
}

void	close_sound_engine(t_game *game)
{
	ma_engine_uninit(&game->engine);
}

void	close_sounds(t_game *game)
{
	unload_all_sounds(game);
	close_sound_engine(game);
}
