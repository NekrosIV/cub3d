/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastingbot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:05:13 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/13 14:25:52 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void calculate_enemy_parameters(t_game *game, t_enemy *enemy, t_utils *u)
{
    u->dx = enemy->posX - game->player.posX;
    u->dy = enemy->posY - game->player.posY;
    u->distance = sqrt((u->dx * u->dx) + (u->dy * u->dy));
    u->line_h = WINY / u->distance;
    u->starty = (int)(WINY / 2 - u->line_h / 2);
    u->endy = (int)(WINY / 2 + u->line_h / 2);
    u->startx = (int)(WINX / 2 - u->line_h / 2);
    u->endx = (int)(WINX / 2 + u->line_h / 2);
    u->angle = atan2(u->dy, u->dx);
    u->difference = game->player.dirangle + u->angle;
    if (u->difference > PI)
        u->difference -= 2 * PI;
    if (u->difference < -PI)
        u->difference += 2 * PI;
    u->pixelx = sin(u->difference) * WINX / FOV;
    u->startx = u->startx + (int)u->pixelx;
    u->endx = u->endx + (int)u->pixelx;
    u->ratio = 64.0 / u->line_h;
}

void draw_enemy_column(t_game *game, char *data, t_enemy *enemy, t_utils *u)
{
    if (u->startx < WINX && u->startx >= 0)
    {
        u->y_img = 0;
        if (game->profondeur[u->startx] > u->distance)
        {
            u->i = u->starty;
            while (u->i < u->endy && u->i < WINY && u->i >= 0)
            {
                if (u->x_img < 64 && u->y_img < 64 &&
                    *((int *)game->texturebot[enemy->action][enemy->frame].data +
                      (int)u->x_img + (int)u->y_img * 64) !=
                    *((int *)game->texturebot[enemy->action][enemy->frame].data))
                {
                    *((int *)data + u->i * WINX + (int)u->startx) =
                        *((int *)game->texturebot[enemy->action][enemy->frame].data +
                          (int)u->x_img + (int)u->y_img * 64);
                }
                u->y_img += u->ratio;
                u->i++;
            }
        }
    }
}

void drawEnemy(t_game *game, char *data, t_enemy *enemy)
{
    t_utils u;

    if (enemy->bothit < 20)
        return;

    calculate_enemy_parameters(game, enemy, &u);

    u.x_img = 0.0;
    u.y_img = 0.0;

    while (u.startx < u.endx)
    {
        draw_enemy_column(game, data, enemy, &u);
        u.x_img += u.ratio;
        u.startx++;
    }
}

