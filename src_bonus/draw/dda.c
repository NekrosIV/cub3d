/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 17:44:33 by kasingh           #+#    #+#             */
/*   Updated: 2024/12/28 16:04:44 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	step_ray(t_ray *ray)
{
	if (ray->sidedistx < ray->sidedisty)
	{
		ray->mapx += ray->stepx;
		ray->sidedistx += ray->deltax;
		ray->last_hit = 0;
	}
	else
	{
		ray->mapy += ray->stepy;
		ray->sidedisty += ray->deltay;
		ray->last_hit = 1;
	}
}

void	check_bot_collision(t_ray *ray, t_game *game)
{
	int	i;

	i = 0;
	while (i < game->bot_nb)
	{
		if (ray->mapx == (int)game->ennemy[i].posx
			&& ray->mapy == (int)game->ennemy[i].posy)
			game->ennemy[i].bothit += 1;
		i++;
	}
}

void	check_door_collision(t_ray *ray, t_game *game)
{
	int	i;

	i = 0;
	while (i < game->nb_door)
	{
		if (game->door[i].map_y == ray->mapy
			&& game->door[i].map_x == ray->mapx)
			game->door[i].door_hit++;
		i++;
	}
}

bool	is_a_door(t_ray *ray, t_game *game)
{
	int	i;

	i = 0;
	while (i < game->nb_door)
	{
		if (game->door[i].map_y == ray->mapy
			&& game->door[i].map_x == ray->mapx)
			return(true);
		i++;
	}
	return(false);
}

// void	check_wall_hit(t_ray *ray, t_game *game)
// {
// 	int	i;

// 	i = 0;
// 	if (game->map[ray->mapy][ray->mapx] != '0' || is_a_door(ray,game))
// 	{
// 		ray->ray_hit = 1;
// 		while (i < game->nb_door && ray->ray_hit == 1)
// 		{
// 			if (game->door[i].map_y == ray->mapy
// 				&& game->door[i].map_x == ray->mapx)
// 			{
// 				if(ray->two_time == 0)
// 				{
// 					ray->ray_hit = 0;
// 					return;
// 				}
// 				ray->ray_hit = 2;
// 				ray->door_index = i;
// 				game->door[i].door_hit++;
// 			}
// 			i++;
// 		}
// 	}
// }
void check_wall_hit(t_ray *ray, t_game *game)
{
    // On considère le mur (ou porte) s’il n’est pas '0'
    if (game->map[ray->mapy][ray->mapx] != '0' || is_a_door(ray, game))
    {
        ray->ray_hit = 1; // par défaut mur
        for (int i = 0; i < game->nb_door && ray->ray_hit == 1; i++)
        {
            if (game->door[i].map_y == ray->mapy && game->door[i].map_x == ray->mapx)
            {
				// if(!ray->store_door)
				{	ray->store_door = true;
					ray->stored_door_index = i;
					ray->stored_last_hit = ray->last_hit;
					ray->stored_sidedistx = ray->sidedistx;
					ray->stored_sidedisty = ray->sidedisty;
					ray->ray_hit = 0; 
					game->door[i].door_hit++;
				}
				// else
				// {
					// ray->ray_hit = 2;
					// ray->door_index = i; 
					// game->door[i].door_hit++;
				// }
                return;
            }
        }
    }
}


// // void	check_wall_hit(t_ray *ray, t_game *game)
// {
// 	int	i;
// 	i = 0;
// 	if (game->map[ray->mapy][ray->mapx] != '0')
// 	{
// 		ray->ray_hit = 1;
// 		while (i < game->nb_door && ray->ray_hit == 1)
// 		{
// 			if (game->door[i].map_y == ray->mapy
// 				&& game->door[i].map_x == ray->mapx)
// 			{
// 				// On a touché une porte
// 				ray->ray_hit = 2;
// 				ray->door_index = i;
// 				game->door[i].door_hit++;

// 				// --- Début de la logique de porte partiellement ouverte --- //
// 				t_door *door = &game->door[i];
// 				double open = door->open_state; // entre 0.0 et 1.0

// 				// Calcul de la distance parcourue (perp_length)
// 				// Selon last_hit, on sait quelle direction a été frappée
// 				double perp_length;
// 				if (ray->last_hit == 0)
// 					perp_length = ray->sidedistx - ray->deltax;
// 				else
// 					perp_length = ray->sidedisty - ray->deltay;

// 				// Point d’impact exact
// 				double hitX = game->player.posx + perp_length * ray->ray_dx;
// 				double hitY = game->player.posy + perp_length * ray->ray_dy;

// 				// Supposons que la porte coulisse horizontalement. 
// 				// Quand open=0.0, la porte occupe [mapx, mapx+1].
// 				// Quand open=1.0, elle n'occupe plus rien.
// 				// On dit que la partie occupée est [mapx, mapx+(1-open)].
// 				if (ray->last_hit == 0)
// 				{
// 					// face verticale frappée, test sur hitX
// 					double occupied_end = ray->mapx + (1.0 - open);
// 					if (hitX >= occupied_end)
// 					{
// 						// Le rayon est dans la partie ouverte de la porte
// 						// Donc on ne s'arrête pas : on considère cette case comme vide
// 						ray->ray_hit = 0; 
// 						// Pas de break, on continue DDA dans perform_dda
// 					}
// 					// Sinon, on a vraiment heurté la porte, on garde ray_hit = 2
// 				}
// 				else
// 				{
// 					// face horizontale frappée, test sur hitY
// 					// Adaptez la logique si la porte coulisse verticalement.
// 					// Par exemple, si la porte coulisse verticalement, 
// 					// la partie occupée pourrait être [mapy, mapy+(1-open)].
					
// 					// Exemple si elle coulisse aussi horizontalement (même logique)
// 					// A adapter selon votre orientation réelle.
// 					double occupied_end = ray->mapy + (1.0 - open);
// 					if (hitY >= occupied_end)
// 					{
// 						// Partie ouverte
// 						ray->ray_hit = 0; 
// 					}
// 					// Sinon, partie occupée, on reste à ray_hit = 2
// 				}
// 				// --- Fin de la logique de porte partiellement ouverte --- //
// 			}
// 			i++;
// 		}
// 	}
// }


void	perform_dda(t_ray *ray, t_game *game)
{
	ray->ray_hit = 0;
	while (ray->ray_hit == 0)
	{
		step_ray(ray);
		check_bot_collision(ray, game);
		check_door_collision(ray, game);
		check_wall_hit(ray, game);
	}
}
