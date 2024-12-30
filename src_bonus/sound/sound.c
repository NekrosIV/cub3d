/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:24:23 by kasingh           #+#    #+#             */
/*   Updated: 2024/12/30 17:18:45 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MINIAUDIO_IMPLEMENTATION
#include "cub3d_bonus.h"

void init_sound_engine(t_game *game)
{
    ma_result result = ma_engine_init(NULL, &game->engine);
    if (result != MA_SUCCESS)
    {
        fprintf(stderr, "Failed to initialize miniAudio engine. Error code: %d\n", result);
        free_exit(game, __LINE__, __FILE__, "Failed to initialize audio engine");
    }
    memset(game->sound, 0, sizeof(game->sound));
}


/*
** Charge un fichier audio dans un "slot" précis du tableau de sons.
** - 'filepath' : chemin vers le WAV/MP3/OGG...
** - 'volume'   : volume [0.0 -> 1.0].
** - 'loop'     : true => lecture en boucle, false => lecture unique.
** - 'slot'     : index dans le tableau (0 <= slot < NUM_SOUNDS).
** Retour : l'index du slot si tout va bien (ou déclenche free_exit en cas d'erreur).
*/
int load_sound(t_game *game, const char *filepath, float volume, bool loop, int slot)
{
    // Vérifie la validité du slot
    if (slot < 0 || slot >= NUM_SOUNDS)
        free_exit(game, __LINE__, __FILE__, "Invalid sound slot index");

    // Vérifie qu'on n'écrase pas un slot déjà utilisé
    if (game->sound[slot].used)
        free_exit(game, __LINE__, __FILE__, "Sound slot already in use");

    // Prépare la structure
    game->sound[slot].volume   = volume;
    game->sound[slot].used     = false;  // On mettra à true après le init
    game->sound[slot].filepath = strdup(filepath); // Copie le chemin

    // Charge le son via miniAudio
    ma_result result = ma_sound_init_from_file(
        &game->engine,
        filepath,
        MA_SOUND_FLAG_STREAM,  // Ou 0 si vous voulez charger entièrement en RAM
        NULL,
        NULL,
        &game->sound[slot].sound
    );
    if (result != MA_SUCCESS)
    {
        fprintf(stderr, "Failed to load sound '%s' (code=%d)\n", filepath, result);
        free(game->sound[slot].filepath);
        free_exit(game, __LINE__, __FILE__, "ma_sound_init_from_file failed");
    }

    // Configure volume et boucle
    ma_sound_set_volume(&game->sound[slot].sound, volume);
    ma_sound_set_looping(&game->sound[slot].sound, loop ? MA_TRUE : MA_FALSE);

    game->sound[slot].used = true;
    return slot;
}

void play_sound(t_game *game, int slot)
{
    if (slot < 0 || slot >= NUM_SOUNDS)
    if (!game->sound[slot].used)
        return;

    ma_result r = ma_sound_start(&game->sound[slot].sound);
    if (r != MA_SUCCESS)
        free_exit(game, __LINE__, __FILE__, "Failed to start sound");
}


