/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:24:23 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/15 16:02:54 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
#include "sound.h"

ALenum	init_wav_file(t_game *game, const char *filename, drwav *wav)
{
	ALenum	format;

	if (!drwav_init_file(wav, filename, NULL))
		free_exit(game, 0, NULL, E_AUDIO);
	if (wav->channels == 1)
		format = AL_FORMAT_MONO16;
	else if (wav->channels == 2)
		format = AL_FORMAT_STEREO16;
	else
	{
		drwav_uninit(wav);
		free_exit(game, 0, NULL, E_AUDIO);
	}
	return (format);
}

void	*read_wav_data(t_game *game, drwav *wav, size_t *data_size)
{
	void			*data;
	drwav_uint64	frames_read;

	*data_size = wav->totalPCMFrameCount * wav->channels * sizeof(int16_t);
	data = malloc(*data_size);
	if (!data)
	{
		drwav_uninit(wav);
		free_exit(game, 0, NULL, E_AUDIO);
	}
	frames_read = drwav_read_pcm_frames_s16(wav, wav->totalPCMFrameCount, data);
	if (frames_read == 0)
	{
		free(data);
		drwav_uninit(wav);
		free_exit(game, 0, NULL, E_AUDIO);
	}
	return (data);
}

ALuint	create_al_buffer(t_game *game, t_sound *sound)
{
	ALuint	buffer;

	alGenBuffers(1, &buffer);
	if (alGetError() != AL_NO_ERROR)
	{
		free((void *)sound->data);
		free_exit(game, 0, NULL, E_AUDIO);
	}
	alBufferData(buffer, sound->format, sound->data, sound->data_size,
		sound->freq);
	if (alGetError() != AL_NO_ERROR)
	{
		alDeleteBuffers(1, &buffer);
		free_exit(game, 0, NULL, E_AUDIO);
	}
	return (buffer);
}

ALuint	create_al_source(t_game *game, ALuint buffer)
{
	ALuint	source;

	alGenSources(1, &source);
	if (alGetError() != AL_NO_ERROR)
	{
		alDeleteBuffers(1, &buffer);
		free_exit(game, 0, NULL, E_AUDIO);
	}
	return (source);
}

t_sound	load_sound(t_game *game, const char *filename)
{
	t_sound	sound;
	drwav	wav;

	sound.format = init_wav_file(game, filename, &wav);
	sound.data = read_wav_data(game, &wav, &sound.data_size);
	sound.freq = wav.sampleRate;
	drwav_uninit(&wav);
	sound.buffer = create_al_buffer(game, &sound);
	free(sound.data);
	sound.source = create_al_source(game, sound.buffer);
	return (sound);
}
