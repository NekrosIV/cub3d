/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycastingbot.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/01 13:05:13 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/05 18:43:06 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

int	is_bot_collision(t_enemy *bot1, t_enemy *bot2, double threshold)
{
	double	dx;
	double	dy;
	double	distance;

	dx = bot1->posX - bot2->posX;
	dy = bot1->posY - bot2->posY;
	distance = sqrt((dx * dx) + (dy * dy));
	// Retourner 1 si la distance entre les deux bots est inférieure au seuil
	if (distance < threshold)
	{
		return (1);
	}
	return (0);
}

int	is_collision_with_others(t_game *game, t_enemy *current_bot,
		double new_posX, double new_posY)
{
	int		i;
	t_enemy	*other_bot;
	t_enemy	temp_bot;

	for (i = 0; i < game->bot_nb; i++)
	{
		other_bot = &game->ennemy[i];
		// Ignorer le bot lui-même
		if (other_bot == current_bot)
		{
			continue ;
		}
		// Créer un bot temporaire à la nouvelle position pour vérifier la collision
		temp_bot = *current_bot;
		temp_bot.posX = new_posX;
		temp_bot.posY = new_posY;
		// Vérifier la collision avec les autres bots
		if (is_bot_collision(&temp_bot, other_bot, 0.5)
			&& other_bot->action != DEATH)
		{               // 1.0 est la distance de sécurité
			return (1); // Collision détectée}
		}
	}
	return (0); // Pas de collision
}

// Fonction pour vérifier si une position est un mur
int	is_wall(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	// Assure-toi que les coordonnées sont dans les limites de la carte
	if (map_x < 0 || map_y < 0 || map_x >= game->map_max_x
		|| map_y >= game->map_max_y)
		return (1); // Si en dehors de la carte, considère comme un mur
	// Si la position sur la carte contient un mur, retourne 1 (mur)
	if (game->map[map_y][map_x] == '1')
		return (1);
	return (0);
}

bool	has_wall_between(t_game *game, t_enemy *bot)
{
	double	deltaX;
	double	deltaY;
	double	distance;
	int		steps;
	double	incrementX;
	double	incrementY;
	double	x;
	double	y;
	int		i;
	int		mapX;
	int		mapY;

	deltaX = game->player.posX - bot->posX;
	deltaY = game->player.posY - bot->posY;
	distance = sqrt(deltaX * deltaX + deltaY * deltaY);
	steps = (int)(distance * 10);
	incrementX = deltaX / steps;
	incrementY = deltaY / steps;
	x = bot->posX;
	y = bot->posY;
	i = 0;
	while (i < steps)
	{
		x += incrementX;
		y += incrementY;
		mapX = (int)floor(x);
		mapY = (int)floor(y);
		if (game->map[mapY][mapX] != '0')
			return (true);
		i++;
	}
	return (false);
}

// Fonction pour déplacer le bot vers le joueur
void	movebot(t_game *game, t_enemy *bot)
{
	double	dx;
	double	dy;
	bool	moved;
	double	current_time;
	double	new_posX;
	double	new_posY;
	double	alt_posX;
	double	alt_posY;

	if (bot->action == DAMAGE || bot->action == DEATH)
		return ;
	if (bot->distance > TRIGGERBOT)
	{
		bot->action = HALT;
		return ;
	}
	current_time = get_current_time();
	// Calcul de la direction vers le joueur
	moved = false;
	dx = game->player.posX - bot->posX;
	dy = game->player.posY - bot->posY;
	if (bot->distance < BOT_SHOOT)
	{
		if (has_wall_between(game, bot))
			bot->action = HALT;
		else if (bot->action != ATTACK && current_time - bot->last_time2 > 0.7)
		{
			bot->action = ATTACK;
			bot->frame = 1;
		}
		return ;
	}
	if (bot->distance > 0)
	{
		dx /= bot->distance;
		dy /= bot->distance;
	}
	// Vérification de collision avec les murs avant de déplacer le bot
	new_posX = bot->posX + dx * SPEED_BOT;
	new_posY = bot->posY + dy * SPEED_BOT;
	// Essayer de se déplacer vers la nouvelle position
	if (!is_wall(game, new_posX, bot->posY) && !is_collision_with_others(game,
			bot, new_posX, bot->posY))
	{
		{
			bot->posX = new_posX;
			moved = true;
		}
	}
	else
	{
		// Essayer un déplacement alternatif (vers la gauche ou la droite)
		alt_posX = bot->posX + (dx * SPEED_BOT) * cos(45.0);
		// Essayer un léger angle
		if (!is_wall(game, alt_posX, bot->posY)
			&& !is_collision_with_others(game, bot, alt_posX, bot->posY))
		{
			bot->posX = alt_posX;
			moved = true;
		}
	}
	if (!is_wall(game, bot->posX, new_posY) && !is_collision_with_others(game,
			bot, bot->posX, new_posY))
	{
		{
			bot->posY = new_posY;
			moved = true;
		}
	}
	else
	{
		// Essayer un déplacement alternatif (vers le haut ou le bas)
		alt_posY = bot->posY + (dy * SPEED_BOT) * sin(45.0);
		// Essayer un léger angle
		if (!is_wall(game, bot->posX, alt_posY)
			&& !is_collision_with_others(game, bot, bot->posX, alt_posY))
		{
			bot->posY = alt_posY;
			moved = true;
		}
	}
	if (moved == true)
		bot->action = WALK;
	else
		bot->action = HALT;
}
void	do_damage_to_bot(t_game *game)
{
	int	i;

	// t_enemy *bot;
	i = 0;
	// bot = game->ennemy;
	while (i < game->bot_nb)
	{
		dammage(game, &game->ennemy[i]);
		i++;
	}
	game->do_damage = false;
}

// Fonction pour vérifier tous les bots
void	checkbotmoves(t_game *game)
{
	t_enemy	*bot;
	int		i;

	i = 0;
	bot = game->ennemy;
	if (game->do_damage == true)
		do_damage_to_bot(game);
	while (i < game->bot_nb)
	{
		game->ennemy[i].takedmg = false;
		movebot(game, bot + i);
		i++;
	}
}

void	update_enemy_distance(t_game *game, t_enemy *enemy)
{
	double	dx;
	double	dy;

	dx = enemy->posX - game->player.posX;
	dy = enemy->posY - game->player.posY;
	enemy->distance = sqrt((dx * dx) + (dy * dy)); // Met à jour la distance
}

void	sort_enemies_by_distance(t_game *game)
{
	int		i;
	int		j;
	int		max_distance;
	t_enemy	temp;

	// Tri par sélection pour trier les ennemis par distance décroissante
	i = 0;
	while (i < game->bot_nb - 1)
	{
		// Trouver l'ennemi le plus éloigné dans le reste du tableau
		max_distance = i;
		j = i + 1;
		while (j < game->bot_nb)
		{
			if (game->ennemy[j].distance > game->ennemy[max_distance].distance)
			{
				max_distance = j;
			}
			j++;
		}
		// Échanger les ennemis si nécessaire
		if (max_distance != i)
		{
			temp = game->ennemy[i];
			game->ennemy[i] = game->ennemy[max_distance];
			game->ennemy[max_distance] = temp;
		}
		i++;
	}
}

void	drawallbot(t_game *game, char *data)
{
	int		i;
	double	current_time;

	i = 0;
	while (i < game->bot_nb)
	{
		update_enemy_distance(game, &game->ennemy[i]);
		i++;
	}
	sort_enemies_by_distance(game);
	i = 0;
	current_time = get_current_time();
	while (i < game->bot_nb)
	{
		update_enemy_animation(game, &game->ennemy[i]);
		drawEnemy(game, data, &game->ennemy[i]);
		i++;
	}
	i = 0;
}

void	drawEnemy(t_game *game, char *data, t_enemy *enemy)
{
	double	dx;
	double	dy;
	double	distance;
	double	angle;
	int		screenX;
	int		screenY;
	double	line_h;
	int		starty;
	int		endy;
	int		startx;
	int		endx;
	double	difference;
	double	pixelx;
	double	ratio;
	double	x_img;
	double	y_img;

	if (enemy->bothit < 20)
		return ;
	dx = enemy->posX - game->player.posX;
	dy = enemy->posY - game->player.posY;
	distance = sqrt((dx * dx) + (dy * dy));
	// printf("distance = %f", distance);
	line_h = WINY / distance;
	starty = (int)(WINY / 2 - line_h / 2);
	endy = (int)(WINY / 2 + line_h / 2);
	startx = (int)(WINX / 2 - line_h / 2); // Use WINX here
	endx = (int)(WINX / 2 + line_h / 2);   // Use WINX here
	angle = atan2(dy, dx);
	difference = game->player.dirangle + angle;
	// Normalize the angle difference to [-PI, PI]
	if (difference > PI)
		difference -= 2 * PI;
	if (difference < -PI)
		difference += 2 * PI;
	pixelx = sin(difference) * WINX / FOV;
	pixelx = pixelx;
	startx = startx + (int)pixelx;
	endx = endx + (int)pixelx;
	ratio = 64.0 / line_h;
	x_img = 0.0;
	y_img = 0.0;
	while (startx < endx)
	{
		if (startx < WINX && startx >= 0)
		{
			y_img = 0;
			if (game->profondeur[startx] > distance)
			{
				for (int i = starty; i < endy && i < WINY && i >= 0; i++)
				{
					if (x_img < 64 && y_img < 64
						&& *((int *)game->texturebot[enemy->action][enemy->frame].data
							+ (int)x_img + (int)y_img
							* 64) != *((int *)game->texturebot[enemy->action][enemy->frame].data))
					{
						*((int *)data + i * WINX
								+ (int)startx) = *((int *)game->texturebot[enemy->action][enemy->frame].data
								+ (int)x_img + (int)y_img * 64);
					}
					y_img += ratio;
				}
			}
		}
		x_img += ratio;
		startx++;
	}
}

void	dammage(t_game *game, t_enemy *enemy)
{
	double dx;
	double dy;
	double distance;
	double angle;
	int screenX;
	int screenY;
	double line_h;
	int starty;
	int endy;
	int startx;
	int endx;
	double difference;
	double pixelx;
	double ratio;
	double x_img;
	double y_img;

	if (enemy->animating == 0 || enemy->bothit < 20
		|| enemy->distance > SGUNRANGE)
		return ;
	dx = enemy->posX - game->player.posX;
	dy = enemy->posY - game->player.posY;
	distance = sqrt((dx * dx) + (dy * dy));
	angle = atan2(-dy, dx);
	difference = game->player.dirangle - angle + (PI / 36);
	while (difference > 2 * PI)
		difference -= 2 * PI;
	while (difference < 0)
		difference += 2 * PI;
	if (fabs(difference) > AIMBOT)
		return ;
	enemy->hp -= DAMAGE_BOT;
	enemy->action = DAMAGE;
	enemy->frame = 0;
}