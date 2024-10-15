/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 12:41:01 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/15 12:41:13 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	stop_and_cleanup_sound(t_sound *sound)
{
	ALint	state;

	if (sound->buffer && sound->source)
	{
		alGetSourcei(sound->source, AL_SOURCE_STATE, &state);
		if (state == AL_PLAYING)
			alSourceStop(sound->source);
		alDeleteSources(1, &sound->source);
		alDeleteBuffers(1, &sound->buffer);
	}
}

void	delete_audios(t_game *game)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		stop_and_cleanup_sound(&game->sound[i]);
		i++;
	}
	close_openal(game);
}
