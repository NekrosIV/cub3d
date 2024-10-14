/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 18:39:36 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/14 18:40:46 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	init_openal(t_game *game)
{
	ALCenum	error;

	if (USE_SOUND == false)
		return (0);
	game->device = alcOpenDevice(NULL);
	if (!game->device)
		return (-1);
	game->context = alcCreateContext(game->device, NULL);
	if (!game->context || alcMakeContextCurrent(game->context) == ALC_FALSE)
	{
		if (game->context)
			alcDestroyContext(game->context);
		alcCloseDevice(game->device);
		return (-1);
	}
	error = alcGetError(game->device);
	if (error != ALC_NO_ERROR)
		return (-1);
	return (0);
}

void	close_openal(t_game *game)
{
	if (USE_SOUND == false)
		return ;
	if (game->context)
	{
		alcMakeContextCurrent(NULL);
		alcDestroyContext(game->context);
	}
	if (game->device)
		alcCloseDevice(game->device);
}

void	play_sound(t_sound *sound, int loop)
{
	if (USE_SOUND == false)
		return ;
	alSourcei(sound->source, AL_BUFFER, sound->buffer);
	if (loop)
		alSourcei(sound->source, AL_LOOPING, AL_TRUE);
	else
		alSourcei(sound->source, AL_LOOPING, AL_FALSE);
	alSourcePlay(sound->source);
}
