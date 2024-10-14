/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 16:08:47 by pscala            #+#    #+#             */
/*   Updated: 2024/10/14 16:51:18 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void draw_element_in_map(t_game *game, int screen_x, int screen_y)
{
	int i;

	if (game->map[game->map_y][game->map_x] == '1') 
		draw_rectangle(&game->pic, screen_x, screen_y, MINI_W);	
	else
		draw_rectangle(&game->pic, screen_x, screen_y, MINI_S);
	i = 0;
	while (i < game->nb_door)
	{
		if ((game->door[i].map_y == game->map_y
			&& game->door[i].map_x == game->map_x) && (game->door[i].state == OPEN))
		{
			draw_rectangle(&game->pic, screen_x, screen_y,
				MINI_D);
		}
		i++;
	}
}
void	draw_loop(t_game *game, int line_size, float offset_x, float offset_y)
{
	float	screen_x;
	float	screen_y;
	
	game->map_y = 0;
	while (game->map_y < game->map_max_y)
	{
		game->map_x = 0;
		line_size = (int)ft_strlen(game->map[game->map_y]);
		while (game->map_x < line_size)
		{
			screen_x = game->map_x * TILE_SIZE + offset_x;
			screen_y = game->map_y * TILE_SIZE + offset_y;
			if (screen_x + TILE_SIZE > 0 && screen_x < MIN_DIM && 
			    screen_y + TILE_SIZE > 0 && screen_y < MIN_DIM)
			{
				draw_element_in_map(game,screen_x,screen_y);
			}
			game->map_x++;
		}
		game->map_y++;
	}
}

float	find_offset(t_game *game, double playerpos, int max)
{
	if (playerpos * TILE_SIZE < MIN_DIM / 2.0f)
		return (0.0f);
		else if (playerpos * TILE_SIZE > max * TILE_SIZE - MIN_DIM / 2.0f)
		return	(MIN_DIM - max * TILE_SIZE);
	else
		return ((MIN_DIM / 2.0f) - playerpos * TILE_SIZE);
	
}

void	mini_draw_map(t_game *game, t_texture *textures)
{
	float	screen_x;
	float	screen_y;
	int		line_size;

	// Calculer l'offset par rapport à la fenêtre (float)
	float offset_x = 0.0f;
	float offset_y = 0.0f;

	// Si la carte est plus large que la fenêtre, centrer la carte autour du joueur
	if (game->map_max_x * TILE_SIZE > MIN_DIM)
		offset_x = find_offset(game, game->player.posx, game->map_max_x);
	// Si la carte est plus haute que la fenêtre, centrer la carte autour du joueur
	if (game->map_max_y * TILE_SIZE > MIN_DIM)
		offset_y = find_offset(game, game->player.posy, game->map_max_y);
	draw_loop(game, line_size, offset_x, offset_y);
	mini_draw_arrow(game, textures);
}

void	calculate_offsets(t_game *game, t_utils *u)
{
	int	map_pixel_width;
	int	map_pixel_height;

	map_pixel_width = game->map_max_x * u->tile_width;
	map_pixel_height = game->map_max_y * u->tile_height;
	if (map_pixel_width > MIN_DIM)
	{
		if (game->player.posx * u->tile_width < MIN_DIM / 2.0f)
			u->offset_x = 0.0f;
		else if (game->player.posx * u->tile_width > map_pixel_width - MIN_DIM
			/ 2.0f)
			u->offset_x = MIN_DIM - map_pixel_width;
		else
			u->offset_x = (MIN_DIM / 2.0f) - game->player.posx * u->tile_width;
	}
	if (map_pixel_height > MIN_DIM)
	{
		if (game->player.posy * u->tile_height < MIN_DIM / 2.0f)
			u->offset_y = 0.0f;
		else if (game->player.posy * u->tile_height > map_pixel_height - MIN_DIM
			/ 2.0f)
			u->offset_y = MIN_DIM - map_pixel_height;
		else
			u->offset_y = (MIN_DIM / 2.0f) - game->player.posy * u->tile_height;
	}
}


void init_utils_var_for_mini_draw_arrow(t_game *game,t_utils *u, t_ray *ray, int nb_ray)
{
	u->tile_width = TILE_SIZE;
    u->tile_height = TILE_SIZE;
    u->offset_x = 0.0f;
    u->offset_y = 0.0f;
    calculate_offsets(game,u);
    ray->posx =  game->player.posx * u->tile_width +  u->offset_x;
    ray->posy = game->player.posy *  u->tile_height +  u->offset_y;
	ray->fov = FOV;
    ray->ray = game->player.dirangle - ray->fov / 2.0;
    ray->offset = ray->fov / nb_ray;
}

void perform_dda_mini_map(t_ray *ray, t_game *game, t_utils *u)
{
	ray->ray_hit = 0;
    while (ray->ray_hit == 0)
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
        if (game->map[ray->mapy][ray->mapx] != '0')
            ray->ray_hit = 1;
        if (ray->last_hit)
            ray->length = (ray->sidedisty - ray->deltay) * u->tile_height;
        else
            ray->length = (ray->sidedistx - ray->deltax) * u->tile_width;
        if (ray->length > 50 && ray->ray_hit != 1)
            ray->ray_hit = 1;
    }
}

void draw_enemies_on_minimap(t_game *game, t_texture *textures, t_utils *u)
{
    int g = 0;
    int screen_x, screen_y;

    while (g < game->bot_nb)
    {
        screen_x = game->ennemy[g].posx * TILE_SIZE + u->offset_x;
        screen_y = game->ennemy[g].posy * TILE_SIZE + u->offset_y;

        if (game->ennemy[g].is_active == false)
        {
            g++;
            continue;
        }
        else if (screen_x > 0 && screen_x < MIN_DIM &&
                 screen_y > 0 && screen_y < MIN_DIM && game->ennemy[g].animating == 0)
            draw_filled_circle(textures, screen_x, screen_y, 0x0000FF);
        else if (screen_x > 0 && screen_x < MIN_DIM &&
                 screen_y > 0 && screen_y < MIN_DIM && game->ennemy[g].animating != 0)
            draw_filled_circle(textures, screen_x, screen_y, 0xFF0000);
        g++;
    }
}

void	draw_ray(t_ray *ray,t_game *game, t_texture *textures, int i)
{
	if (ray->length > 50)
   		ray->length = 50;

    ray->end_x = ray->posx + (int)(ray->length * cos(ray->ray));
    ray->end_y = ray->posy + (int)(ray->length * -sin(ray->ray));

    if (fabs(ray->ray - game->player.dirangle) < 0.01)
        draw_ray_in_data(game, textures, (int)ray->posx, (int)ray->posy, (int)ray->end_x, (int)ray->end_y, 0xFF0000);
    else if (i % 1 == 0)
        draw_ray_in_data(game, textures, (int)ray->posx, (int)ray->posy, (int)ray->end_x, (int)ray->end_y, 0x000000);

}

void mini_draw_arrow(t_game *game, t_texture *textures)
{
    t_ray ray;
    t_utils u;
    int nb_ray;
    int i;
    nb_ray = MIN_DIM;

    init_utils_var_for_mini_draw_arrow(game, &u, &ray, nb_ray);
	i = 0;
    while (i < nb_ray)
    {
        init_ray(&ray, game);
        calculate_step_and_sidedist(&ray, game);
        perform_dda_mini_map(&ray, game, &u);
        draw_ray(&ray, game, textures, i);
        i++;
        ray.ray += ray.offset;
    }
    draw_filled_circle(textures, ray.posx, ray.posy, CIRCLE_COLOR);
    draw_enemies_on_minimap(game, textures, &u);
}
