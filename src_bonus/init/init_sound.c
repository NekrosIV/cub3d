/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sound.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 14:48:51 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/09 19:32:54 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void init_sound(t_game *game)
{
    // Initialiser OpenAL
    if (init_openal(game) != 0)
        free_exit(game, 0, NULL, "INIT_SOUND FAIL");

    game->sound[OST] = load_sound("textures/berserkbro.wav"); 

    if (!game->sound[OST].buffer) {
        free_exit(game, 0, NULL, "Erreur : impossible de charger le fichier audio");
    }

    game->sound[GUN] = load_sound("textures/lasergun4.wav");
    if (!game->sound[GUN].buffer) {
        free_exit(game, 0, NULL, "Erreur : impossible de charger le fichier audio");
    }
    play_sound(&game->sound[OST], true);
    // ALint state;
    // alGetSourcei(game->ost.source, AL_SOURCE_STATE, &state);
    // if (state != AL_PLAYING) {
    //     printf("Erreur : le son n'a pas démarré\n");
    // }
}
