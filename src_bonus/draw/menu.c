/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 16:30:40 by kasingh           #+#    #+#             */
/*   Updated: 2024/12/28 13:10:16 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_menu(t_game *game, t_texture *texture, int state, int frame)
{
	t_utils	u;
	int		x;
	int		y;
	int		img_index;
	int		screen_index;

	u.x_ratio = (double)game->menu_texture[state][frame].w / (double)WINX;
	u.y_ratio = (double)game->menu_texture[state][frame].h / (double)WINY;
	x = -1;
	while (++x < WINX)
	{
		y = -1;
		while (++y < WINY)
		{
			u.x_img = x * u.x_ratio;
			u.y_img = y * u.y_ratio;
			img_index = ((int)u.y_img) * game->menu_texture[state][frame].w
				+ (int)u.x_img;
			screen_index = y * WINX + x;
			*((int *)game->pic.data
					+ screen_index) = *((int *)game->menu_texture[state][frame].data
					+ img_index);
		}
	}
}
void draw_menu_with_zoom(t_game *game, t_texture *texture, int state, int frame, double scale)
{
    t_utils u;
    int     x, y;
    int     img_index;
    int     screen_index;

    // Largeur / hauteur de l'image source à dessiner
    int src_w = game->menu_texture[state][frame].w;
    int src_h = game->menu_texture[state][frame].h;

    // On calcule un ratio tenant compte du 'scale'
    // L'image va être "étirée" ou "réduite".
    // + On veut centrer l'image sur l'écran.
    u.x_ratio = ((double)src_w / (double)WINX) * scale;
    u.y_ratio = ((double)src_h / (double)WINY) * scale;

    // Coordonnées du centre de l'écran
    double half_scr_w = WINX / 2.0;
    double half_scr_h = WINY / 2.0;

    // Coordonnées du centre de l'image
    double half_img_w = src_w / 2.0;
    double half_img_h = src_h / 2.0;

    // On parcourt chaque pixel de l'écran (0..WINX-1, 0..WINY-1)
    for (x = 0; x < WINX; x++)
    {
        for (y = 0; y < WINY; y++)
        {
            // On calcule la coordonnée correspondante dans l'image source
            // "Départ" : le centre de l'écran pointe sur le centre de l'image
            // Puis on applique le ratio (zoom)
            u.x_img = half_img_w + (x - half_scr_w) * u.x_ratio;
            u.y_img = half_img_h + (y - half_scr_h) * u.y_ratio;

            // On vérifie que la coordonnée reste dans l'image
            if (u.x_img >= 0 && u.x_img < src_w &&
                u.y_img >= 0 && u.y_img < src_h)
            {
                // Index dans l'image source
                img_index = ((int)u.y_img) * src_w + (int)u.x_img;
                // Index dans le buffer de destination
                screen_index = y * WINX + x;

                // Copie du pixel
                *((int *)game->pic.data + screen_index) =
                    *((int *)game->menu_texture[state][frame].data + img_index);
            }
        }
    }
}


// void	draw_good_state_menu(t_game *game, t_texture *texture)
// {
// 	double		current_time;
// 	static int	frame = 0;

// 	current_time = get_current_time();
// 	if (current_time
// 		- game->menu_texture[0]->last_time >= game->menu_texture[0]->frame_delay)
// 	{
// 		if (frame == 0)
// 			frame = 1;
// 		else
// 			frame = 0;
// 		game->menu_texture[0]->last_time = current_time;
// 	}
	
// 	draw_menu(game, texture, game->state_menu, frame);
// }

void draw_good_state_menu(t_game *game, t_texture *texture)
{
    static double scale = 0.2;      // part de 20% 
    static bool zoom_done = false;
    static double last_time = 0.0;
    static bool init_time = false;

    double current_time = get_current_time();
    if (!init_time)
    {
        // Première fois qu’on entre ici
        last_time = current_time;
        init_time = true;
    }

    // Calcul du deltaTime
    double deltaTime = current_time - last_time;
    last_time = current_time;

    // On met à jour le frame d’animation du menu (si vous avez un flip-flop frame)
    static int frame = 1;
    if (zoom_done && current_time - game->menu_texture[0]->last_time >= game->menu_texture[0]->frame_delay)
    {
        frame = (frame == 0) ? 1 : 0;
        game->menu_texture[0]->last_time = current_time;
    }

    // Gestion du zoom si pas encore terminé
    if (!zoom_done)
    {
        double speed = 1.5; // vitesse de zoom (ajustez à volonté)
        scale += speed * deltaTime; 
        if (scale >= 1.0)
        {
            scale = 1.0;
            zoom_done = true;
        }
    }

    // On dessine le menu avec le zoom (voir plus bas la fonction draw_menu_with_zoom)
    draw_menu_with_zoom(game, texture, game->state_menu, frame, scale);
}
