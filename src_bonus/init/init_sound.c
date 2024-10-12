/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:48:51 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/12 13:13:59 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void    init_sounds_struct(t_game *game)
{
    int i;

    i = 0;
    while (i < 7)
    {
        game->sound[i].buffer = 0;
        game->sound[i].source = 0;
        i++;
    }
}

void	init_sound(t_game *game)
{
	if (USE_SOUND == false)
		return;
	if (init_openal(game) != 0)
		free_exit(game, 0, NULL, "INIT_SOUND FAIL");
	game->sound[OST] = load_sound(game, "textures/berserkbro.wav");
	game->sound[GUN] = load_sound(game, "textures/lasergun5.wav");
	game->sound[E_DEAD] = load_sound(game, "textures/LegoYodaDeath.wav");
	game->sound[E_TRIG] = load_sound(game, "textures/mauvaisenouvelle.wav");
	game->sound[E_HURT] = load_sound(game, "textures/hurt.wav");
	game->sound[STEP] = load_sound(game, "textures/footstep.wav");
	game->sound[DOOR] = load_sound(game, "textures/door.wav");
	play_sound(&game->sound[OST], true);
}
