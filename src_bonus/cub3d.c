/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:09:12 by kasingh           #+#    #+#             */
/*   Updated: 2024/12/23 17:16:06 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	update_ceiling_animation(t_game *game)
{
	double	current_time;

	current_time = get_current_time();
	if (current_time - game->ceiling->last_time >= game->ceiling->frame_delay)
	{
		game->ceiling->frame += 1;
		if (game->ceiling->frame > 63)
		{
			game->ceiling->frame = 0;
			game->ceiling->animating = 0;
		}
		game->ceiling->last_time = current_time;
	}
}

void update_doors(t_game *game)
{
	double	current_time;
	current_time = get_current_time();
	// double speed = 1.0 / 0.5;
    for (int i = 0; i < game->nb_door; i++)
    {
        t_door *door = &game->door[i];
        if (door->state == IS_OPENING && current_time - door->last_time >=  0.06)
        {
            // door->open_state += speed * deltaTime;
			door->frame++;
            if (door->frame == 11) {
                door->open_state = 1.0;
                door->state = IS_OPEN;
				game->map[door->map_y][door->map_x] = '0';
                // La porte est pleinement ouverte
            }
			door->last_time = current_time;
        }
        else if (door->state == IS_CLOSING && current_time - door->last_time >=  0.06)
        {
            // door->open_state -= speed * deltaTime;
			door->frame--;
            if (door->frame == 5) {
                door->open_state = 0.0;
                door->state = IS_CLOSE;
				game->map[door->map_y][door->map_x] = '1';
                // La porte est pleinement fermée
            }
			door->last_time = current_time;
        }
    }
}


// void update_doors(t_game *game)
// {
// 	double deltaTime = get_current_time() - game->door->last_time;
// 	game->door->last_time = get_current_time();
// 	double speed = 1.0 / 0.5;
//     for (int i = 0; i < game->nb_door; i++)
//     {
//         t_door *door = &game->door[i];
//         if (door->state == IS_OPENING)
//         {
// 			printf("door == opening\nopen_state = %f\n",door->open_state);
//             door->open_state += speed * deltaTime;
//             if (door->open_state >= 1.0) {
//                 door->open_state = 1.0;
//                 door->state = IS_OPEN;
// 				game->map[door->map_y][door->map_x] = '0';
//                 // La porte est pleinement ouverte
//             }
//         }
//         else if (door->state == IS_CLOSING)
//         {
// 			printf("door == closing\nopen_state = %f\n",door->open_state);
//             door->open_state -= speed * deltaTime;
//             if (door->open_state <= 0.0) {
//                 door->open_state = 0.0;
//                 door->state = IS_CLOSE;
// 				game->map[door->map_y][door->map_x] = '1';
//                 // La porte est pleinement fermée
//             }
//         }
//     }
// }


int	loop_hook(t_game *game)
{
	void		*img_ptr;
	char		*datax;
	t_texture	*texture;

	texture = &game->pic;
	if (game->menu == false)
	{
		(check_moves(game), check_door(game), update_doors(game));
		update_ceiling_animation(game);
		(draw_arrow(game, texture), mini_draw_map(game, texture));
		(drawallbot(game, texture->data), checkbotmoves(game));
		draw_crosshair(texture, game, CROSSHAIR);
		(update_gun_animation(game), draw_gun(game, texture->data));
		(bot_attack(game, texture), draw_health(game, texture));
	}
	else
		draw_good_state_menu(game, texture);
	mlx_put_image_to_window(game->mlx->mlx_ptr, game->mlx->mlx_win,
		texture->img, 0, 0);
	if (game->player.hp <= 0)
	{
		ft_printf(RED "YOU DIED *rip*\n" RESET);
		free_exit(game, 0, NULL, "EOG");
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	if (ac != 2)
		return (1);
	parsing(av[1], &game);
	init_player(&game);
	init_mlx(&game);
	init_sound(&game);
	mlx_loop_hook(game.mlx->mlx_ptr, loop_hook, &game);
	mlx_hook(game.mlx->mlx_win, 17, 0, india, &game);
	mlx_hook(game.mlx->mlx_win, 02, (1L << 0), key_hook, &game);
	mlx_hook(game.mlx->mlx_win, 03, (1L << 1), key_release, &game);
	mlx_hook(game.mlx->mlx_win, 6, (1L << 6), mouse_move, &game);
	mlx_hook(game.mlx->mlx_win, 04, (1L << 2), mouse_press, &game);
	mlx_loop(game.mlx->mlx_ptr);
	return (0);
}
