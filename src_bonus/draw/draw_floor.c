/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 16:10:14 by kasingh           #+#    #+#             */
/*   Updated: 2024/12/20 14:39:13 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Exemple de fonction pour dessiner le sol après avoir dessiné les murs
// textures: le buffer image final dans lequel on dessine (comme dans draw_pixels)
// On suppose que la caméra est située à game->player.posx, game->player.posy
// et pointe dans la direction game->player.dirangle.
// On utilise rayDirX0, rayDirY0, rayDirX1, rayDirY1 pour définir le plan du floor casting.
// WINX, WINY : résolution écran, définie par vos macros.

#include "cub3d_bonus.h"    

// void draw_floor(t_game *game, t_texture *textures)
// {
//     double a = game->player.dirangle;
//     double dirX = cos(a);
//     double dirY = -sin(a);

//     double f = tan(FOV / 2.0);
//     double planeX = -sin(a) * f;
//     double planeY = -cos(a) * f;

//     // Position de la caméra
//     double posX = game->player.posx;
//     double posY = game->player.posy;

//     // Hauteur virtuelle de la caméra (moitié de l'écran)
//     double posZ =  WINY / 2.0;

//     t_texture *floor_tex = &game->sol; 
//     int floor_w = floor_tex->w;
//     int floor_h = floor_tex->h;
//     int floor_sl = floor_tex->size_line / 4;

//     for (int y = WINY / 2 + 1; y < WINY; y++)
//     {
//         int p = y - (WINY / 2);
//         double rowDistance = posZ / (double)p;

//         double rayDirX0 = dirX + planeX;
//         double rayDirY0 = dirY + planeY;
//         double rayDirX1 = dirX - planeX;
//         double rayDirY1 = dirY - planeY;

//         double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / (double)WINX;
//         double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / (double)WINX;

//         double floorX = posX + rowDistance * rayDirX0;
//         double floorY = posY + rowDistance * rayDirY0;

//         for (int x = 0; x < WINX; x++)
//         {
//             int cellX = (int)floorX;
//             int cellY = (int)floorY;

//             double fracX = floorX - cellX;
//             double fracY = floorY - cellY;

//             int texX = (int)(fracX * floor_w) & (floor_w - 1);
//             int texY = (int)(fracY * floor_h) & (floor_h - 1);

//             int color = *((int *)floor_tex->data + texX + texY * floor_sl);
//             *((int *)textures->data + x + y * WINX) = color;

//             floorX += floorStepX;
//             floorY += floorStepY;
//         }
//     }
// }
void draw_floor(t_game *game, t_texture *textures)
{
    double a = game->player.dirangle;
    double dirX = cos(a);
    double dirY = -sin(a);

    // Champ de vision
    double f = tan(FOV / 2.0);
    double planeX = -sin(a) * f;
    double planeY = -cos(a) * f;

    // Position du joueur
    double posX = game->player.posx;
    double posY = game->player.posy;

    // Hauteur virtuelle de la caméra
    double posZ = 0.5 * WINY;

    t_texture *floor_tex = &game->sol; 
    int floor_w = floor_tex->w;
    int floor_h = floor_tex->h;
    int floor_sl = floor_tex->size_line / 4;

    // On dessine le sol à partir de la ligne du milieu de l'écran jusqu'en bas
    for (int y = WINY / 2 + 1; y < WINY; y++)
    {
        int p = y - (WINY / 2);
        double rowDistance = posZ / (double)p;

        // Rayons gauche (rayDirX0, rayDirY0) et droit (rayDirX1, rayDirY1) du FOV pour cette ligne
        double rayDirX0 = dirX + planeX;
        double rayDirY0 = dirY + planeY;
        double rayDirX1 = dirX - planeX;
        double rayDirY1 = dirY - planeY;

        // Calcul du pas entre chaque pixel en X
        double floorStepX = rowDistance * (rayDirX1 - rayDirX0) / (double)WINX;
        double floorStepY = rowDistance * (rayDirY1 - rayDirY0) / (double)WINX;

        // Position de départ (côté gauche de l'écran)
        double floorX = posX + rowDistance * rayDirX0;
        double floorY = posY + rowDistance * rayDirY0;

        for (int x = 0; x < WINX; x++)
        {
            int cellX = (int)floorX;
            int cellY = (int)floorY;

            double fracX = floorX - cellX;
            double fracY = floorY - cellY;

            int texX = (int)(fracX * floor_w) % floor_w;
            int texY = (int)(fracY * floor_h) % floor_h;
            if (texX < 0) texX += floor_w;
            if (texY < 0) texY += floor_h;

            int color = *((int *)floor_tex->data + texX + texY * floor_sl);
            *((int *)textures->data + x + y * WINX) = color;

            floorX += floorStepX;
            floorY += floorStepY;
        }
    }
}

