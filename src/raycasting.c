/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:05:13 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/01 13:12:10 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	pre_init_ray(t_player *player, t_ray *ray)
{
	ray->mapX = player->mapX;
	ray->mapY = player->mapY;
	ray->posX = player->posX;
	ray->posY = player->posY;
	ray->hit = 0;
	ray->dist = 0;
}

void	shift_ray(t_player *player, t_ray *ray,int nb)
{
    if (x == 0)
}

void	init_ray(t_game *game, t_player *player, t_ray *ray, int nb)
{
	pre_init_ray(player, ray);
}