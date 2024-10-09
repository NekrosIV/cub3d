/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:24:23 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/09 17:44:08 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"
# define DR_WAV_IMPLEMENTATION
# include "dr_wav.h"

int init_openal(t_game *game)
{
    // Ouvrir le dispositif audio
    game->device = alcOpenDevice(NULL);
    if (!game->device)
    {
        printf("Erreur : Impossible d'ouvrir le dispositif audio\n");
        return (-1);
    }

    // Créer un contexte audio
    game->context = alcCreateContext(game->device, NULL);
    if (!game->context || alcMakeContextCurrent(game->context) == ALC_FALSE)
    {
        printf("Erreur : Impossible de créer le contexte OpenAL\n");
        if (game->context)
            alcDestroyContext(game->context);
        alcCloseDevice(game->device);
        return (-1);
    }

    // Vérification des erreurs après création du contexte
    ALCenum error = alcGetError(game->device);
    if (error != ALC_NO_ERROR)
    {
        printf("Erreur OpenAL (contexte) : %s\n", alcGetString(game->device, error));
        return (-1);
    }

    return (0);
}


void close_openal(t_game *game)
{
    if (game->context)
    {
        alcMakeContextCurrent(NULL);
        alcDestroyContext(game->context);
    }
    if (game->device)
        alcCloseDevice(game->device);
}

t_sound load_sound(const char *filename)
{
    t_sound sound ;
    ALenum format;
    ALsizei size;
    ALsizei freq;
    ALvoid *data = NULL;
    drwav wav;

    // Ouvrir le fichier audio avec dr_wav
    if (!drwav_init_file(&wav, filename, NULL))
    {
        printf("Erreur : Impossible d'ouvrir le fichier audio %s\n", filename);
        return sound;
    }

    // Déterminer le format audio
    if (wav.channels == 1)
        format = AL_FORMAT_MONO16;
    else if (wav.channels == 2)
        format = AL_FORMAT_STEREO16;
    else
    {
        printf("Erreur : Nombre de canaux audio non supporté (%d)\n", wav.channels);
        drwav_uninit(&wav);
        return sound;
    }

    // Lire les données audio
    size_t data_size = wav.totalPCMFrameCount * wav.channels * sizeof(int16_t);
    data = malloc(data_size);
    if (!data)
    {
        printf("Erreur : Allocation de mémoire pour les données audio\n");
        drwav_uninit(&wav);
        return sound;
    }

    drwav_uint64 frames_read = drwav_read_pcm_frames_s16(&wav, wav.totalPCMFrameCount, data);
    if (frames_read == 0)
    {
        printf("Erreur : Impossible de lire les données audio\n");
        free(data);
        drwav_uninit(&wav);
        return sound;
    }

    freq = wav.sampleRate;
    drwav_uninit(&wav);

    // Générer le buffer OpenAL
    alGenBuffers(1, &sound.buffer);
    if (alGetError() != AL_NO_ERROR)
    {
        printf("Erreur : Impossible de générer un buffer OpenAL\n");
        free(data);
        return sound;
    }

    // Charger les données dans le buffer
    alBufferData(sound.buffer, format, data, data_size, freq);
    free(data);

    if (alGetError() != AL_NO_ERROR)
    {
        printf("Erreur : Impossible de charger les données dans le buffer OpenAL\n");
        alDeleteBuffers(1, &sound.buffer);
        sound.buffer = 0;
        return sound;
    }

    // Générer la source audio
    alGenSources(1, &sound.source);
    if (alGetError() != AL_NO_ERROR)
    {
        printf("Erreur : Impossible de générer une source OpenAL\n");
        alDeleteBuffers(1, &sound.buffer);
        sound.source = 0;
        return sound;
    }

    return sound;
}




void play_sound(t_sound *sound, int loop)
{
    if (!sound || sound->source == 0 || sound->buffer == 0)
    {
        printf("Erreur : Le son ou la source n'est pas valide\n");
        return;
    }

    alSourcei(sound->source, AL_BUFFER, sound->buffer);
    if (loop)
        alSourcei(sound->source, AL_LOOPING, AL_TRUE);  // Activer la boucle
    else
        alSourcei(sound->source, AL_LOOPING, AL_FALSE); // Désactiver la boucle

    alSourcePlay(sound->source);

    // Vérification si le son a démarré
    ALenum error = alGetError();
    if (error != AL_NO_ERROR)
    {
        printf("Erreur OpenAL lors de la lecture du son : %s\n", alGetString(error));
    }
}


void stop_sound(t_sound *sound)
{
    if (!sound || sound->source == 0)
    {
        printf("Erreur : Le son ou la source n'est pas valide\n");
        return;
    }

    alSourceStop(sound->source);
    ALenum error = alGetError();
    if (error != AL_NO_ERROR)
    {
        printf("Erreur OpenAL lors de l'arrêt du son : %s\n", alGetString(error));
    }
}


void delete_sound(t_sound *sound)
{
    if (!sound)
        return;

    if (sound->source != 0)
        alDeleteSources(1, &sound->source);

    if (sound->buffer != 0)
        alDeleteBuffers(1, &sound->buffer);

    ALenum error = alGetError();
    if (error != AL_NO_ERROR)
    {
        printf("Erreur OpenAL lors de la suppression du son : %s\n", alGetString(error));
    }
}

