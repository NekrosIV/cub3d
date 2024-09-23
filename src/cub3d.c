/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:09:12 by kasingh           #+#    #+#             */
/*   Updated: 2024/09/23 18:07:07 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	loop_hook(t_game *game)
{
	void	*img_ptr;
	char	*datax;
	t_texture *texture;

	texture = &game->pic;
	int bpp, size_line, endian;
	check_moves(game);
	draw_arrow(game, texture);
	mini_draw_map(game, texture);
	drawallbot(game, texture->data);
	checkbotmoves(game);
	draw_crosshair(game, texture->data, texture->size_line, texture->bpp,0xFF1493);
	update_gun_animation(game);
	draw_gun(game, texture->data, texture->bpp);
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->mlx_win, texture->img, 0,
		0);
	if (game->player.hp <= 0)
	{
		ft_printf(RED"YOU DIED *rip*\n"RESET);
		free_exit(game, 0, NULL, "EOG");
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_game	*game;

	if (ac != 2)
		return (1);
	game = parsing(av[1]);
	init_player(game);
	init_mlx(game);
	mlx_loop_hook(game->mlx->mlx_ptr, loop_hook, game);
	mlx_hook(game->mlx->mlx_win, 17, 0, india, game);
	mlx_hook(game->mlx->mlx_win, 02, (1L << 0), key_hook, game);
	mlx_hook(game->mlx->mlx_win, 03, (1L << 1), key_release, game);
	mlx_loop(game->mlx->mlx_ptr);
	// ft_calloc(1,sizeof(t_game));
	// print_struct(game);
	
	return (0);
}



// void draw_bot(t_game *game, int bpp, int size_line, char *data)
// {
//     (void)bpp;
//     (void)size_line;

//     t_enemy *enemy = &game->ennemy; // Corrected spelling of 'enemy'
//     if (!enemy->i_count)
//         return;

//     // Calculate distance to enemy
//     double deltax = enemy->posX - game->player.posX;
//     double deltay = enemy->posY - game->player.posY;
//     double delta = sqrt(deltax * deltax + deltay * deltay);

//     // Calculate sprite dimensions on screen
//     double sprite_height = WINY / delta;
//     double sprite_TILE_SIZE = sprite_height; // Assuming square sprite; adjust if necessary

//     // Calculate sprite screen position
//     double start_x = enemy->pixel;
//     double end_x = start_x + sprite_width;
//     double start_y = (WINY / 2.0) - (sprite_height / 2.0);
//     double end_y = (WINY / 2.0) + (sprite_height / 2.0);

//     // Clamp positions to screen bounds
//     if (start_x < 0) start_x = 0;
//     if (end_x > WINX) end_x = WINX;
//     if (start_y < 0) start_y = 0;
//     if (end_y > WINY) end_y = WINY;

//     // Calculate scaling ratios
//     double x_ratio = 64.0 / sprite_width;
//     double y_ratio = 64.0 / sprite_height;

//     int texture_width = 64; // Texture width
//     int texture_height = 64; // Texture height

//     // Loop variables
//     int current_pixel = (int)start_x;
//     int end_pixel = (int)end_x;
//     double x_enemy = 0.0;

//     while (current_pixel < end_pixel && x_enemy < texture_width)
//     {
//         double y_img = 0.0;
//         int y = (int)start_y;

//         while (y < (int)end_y && y < WINY)
//         {
//             int texture_x = (int)x_enemy % texture_width;
//             int texture_y = (int)y_img % texture_height;
//             int texture_index = (texture_y * texture_width) + texture_x;

//             // Ensure texture index is within bounds
//             if (texture_index >= 0 && texture_index < (texture_width * texture_height))
//             {
//                 // Set pixel color
//                 *((int *)data + current_pixel + y * WINX) = *((int *)enemy->texture[0][0].data + texture_index);
//             }

//             y_img += y_ratio;
//             y++;
//         }

//         current_pixel++;
//         x_enemy += x_ratio;
//     }
// }



// void	draw_bot(t_game *game, int bpp, int size_line, char *data)
// {
// 	double deltax;
// 	double deltay;
// 	t_enemy *enemy;

// 	enemy = &game->ennemy;
// 	deltax = enemy->posX - game->player.posX;
// 	deltay = enemy->posY - game->player.posY;
// 	int			x;
// 	int			y;
// 	int			resetx;
// 	double			x_img;
// 	double			y_img;
// 	int ignore = *((int *)enemy[0][0]->data);
// 	x_img = 0;
// 	y_img = 0;
// 	(void)bpp;
// 	resetx = WINX/2;
// 	y = WINY - WINY/2;
// 	double ratiox =  (gun->w)/(double)WINX * 2;
// 	double ratioy = (gun->h)/(double)(WINY/2.0);
// 	x = resetx;
// 	// printf("%d %d %d %d\n",x,y,x_img,y_img);
// 	while (y < WINY)
// 	{
// 		while (x < WINX)
// 		{
// 			if (x_img < gun->w && y_img < gun->h && *((int *)gun->data + (int)x_img + (int)y_img*(gun->w)) != ignore)
// 				*((int *)data + x + y*WINX) = *((int *)gun->data + (int)x_img + (int)y_img*(gun->w));
// 			x_img += ratiox;
// 			x++;
// 		}
// 		y_img +=ratioy;
// 		x_img = 0;
// 		x = resetx;
// 		y++;
// 	}
// }


// void	draw_map(t_game *game, int bpp, int size_line, char *data)
// {
// 	int	tile_width;
// 	int	tile_height;
// 	int	map_x;
// 	int	map_y;
// 	int	screen_x;
// 	int	screen_y;
// 	int	color;

// 	map_y = 0;
// 	tile_width = WINX / game->map_max_x;
// 	tile_height = WINY / game->map_max_y;
// 	while (map_y < game->map_max_y)
// 	{
// 		map_x = 0;
// 		while (game->map[map_y][map_x] && map_x < game->map_max_x)
// 		{
// 			screen_x = map_x * tile_width;
// 			screen_y = map_y * tile_height;
// 			if (game->map[map_y][map_x] == '1')
// 				color = 0xFF0000;
// 			else
// 				color = 0x000000;
// 			draw_rectangle(data, size_line, bpp, screen_x, screen_y, tile_width,
// 				tile_height, color,WINX,WINY);
// 			map_x++;
// 		}
// 		map_y++;
// 	}
// 	draw_arrow(game, bpp, size_line, data);
// }