/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:24:23 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/12 13:17:10 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"

int	init_openal(t_game *game)
{
	ALCenum	error;

	if (USE_SOUND == false)
		return (0);
	// Ouvrir le dispositif audio
	game->device = alcOpenDevice(NULL);
	if (!game->device)
		return (-1);
	// Créer un contexte audio
	game->context = alcCreateContext(game->device, NULL);
	if (!game->context || alcMakeContextCurrent(game->context) == ALC_FALSE)
	{
		if (game->context)
			alcDestroyContext(game->context);
		alcCloseDevice(game->device);
		return (-1);
	}
	// Vérification des erreurs après création du contexte
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

t_sound	load_sound(t_game *game, const char *filename)
{
	t_sound			sound;
	ALenum			format;
	ALsizei			size;
	ALsizei			freq;
	ALvoid			*data;
	drwav			wav;
	size_t			data_size;
	drwav_uint64	frames_read;

	data = NULL;
	// Ouvrir le fichier audio avec dr_wav
	if (!drwav_init_file(&wav, filename, NULL))
		free_exit(game, 0, NULL, E_AUDIO);
	// Déterminer le format audio
	if (wav.channels == 1)
		format = AL_FORMAT_MONO16;
	else if (wav.channels == 2)
		format = AL_FORMAT_STEREO16;
	else
		(drwav_uninit(&wav), free_exit(game, 0, NULL, E_AUDIO));
	// Lire les données audio
	data_size = wav.totalPCMFrameCount * wav.channels * sizeof(int16_t);
	data = malloc(data_size);
	if (!data)
		(drwav_uninit(&wav), free_exit(game, 0, NULL, E_AUDIO));
	frames_read = drwav_read_pcm_frames_s16(&wav, wav.totalPCMFrameCount, data);
	if (frames_read == 0)
		(free(data), drwav_uninit(&wav), free_exit(game, 0, NULL, E_AUDIO));
	freq = wav.sampleRate;
	drwav_uninit(&wav);
	// Générer le buffer OpenAL
	alGenBuffers(1, &sound.buffer);
	if (alGetError() != AL_NO_ERROR)
		(free(data), free_exit(game, 0, NULL, E_AUDIO));
	// Charger les données dans le buffer
	alBufferData(sound.buffer, format, data, data_size, freq);
	free(data);
	if (alGetError() != AL_NO_ERROR)
		(alDeleteBuffers(1, &sound.buffer), free_exit(game, 0, NULL, E_AUDIO));
	// Générer la source audio
	alGenSources(1, &sound.source);
	if (alGetError() != AL_NO_ERROR)
		(alDeleteBuffers(1, &sound.buffer), free_exit(game, 0, NULL, E_AUDIO));
	return (sound);
}

void	play_sound(t_sound *sound, int loop)
{
	if (USE_SOUND == false)
		return ;
	alSourcei(sound->source, AL_BUFFER, sound->buffer);
	if (loop)
		alSourcei(sound->source, AL_LOOPING, AL_TRUE); // Activer la boucle
	else
		alSourcei(sound->source, AL_LOOPING, AL_FALSE); // Désactiver la boucle
	alSourcePlay(sound->source);
}
