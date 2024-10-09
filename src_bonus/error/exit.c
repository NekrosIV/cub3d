/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kasingh <kasingh@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:18:57 by kasingh           #+#    #+#             */
/*   Updated: 2024/10/09 17:54:36 by kasingh          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	free_taboftab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	free_wall_texture(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->wall[i].img)
			mlx_destroy_image(game->mlx->mlx_ptr, game->wall[i].img);
		i++;
	}
}
void	free_mlx(t_game *game, t_mlx *mlx)
{
	if (mlx->mlx_ptr)
	{
		free_wall_texture(game);
		if (game->pic.img)
			mlx_destroy_image(mlx->mlx_ptr, game->pic.img);
		if (mlx->mlx_win)
			mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
	}
	free(mlx);
}
void	free_texture_path(t_game *game)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (game->wall_path[i])
			free(game->wall_path[i]);
		i++;
	}
}
void	stop_and_cleanup_sound(t_sound *sound)
{
	ALint	state;

	// Arrêter le son s'il est en cours de lecture
	alGetSourcei(sound->source, AL_SOURCE_STATE, &state);
	if (state == AL_PLAYING)
		alSourceStop(sound->source);
	// Supprimer la source et le buffer associés
	alDeleteSources(1, &sound->source);
	alDeleteBuffers(1, &sound->buffer);
}

void	free_everything(t_game *game)
{
	free_texture_path(game);
	if (game->map)
		free_taboftab(game->map);
	if (game->cpy_map)
		free_taboftab(game->cpy_map);
	if (game->mlx)
		free_mlx(game, game->mlx);
	// if (game->context || game->device)
	// {
	// 	stop_and_cleanup_sound(&game->[]);
	// 	close_openal(game);
	// }
	free(game);
}

void	free_exit(t_game *game, int line, char *file, char *error)
{
	if (game)
		free_everything(game);
	if (error)
	{
		if (ft_strncmp(error, "EOG", 3))
		{
			ft_putstr_fd(RED "Error: ", 2);
			ft_putendl_fd(error, 2);
			if (file)
			{
				ft_putstr_fd("In file: ", 2);
				ft_putstr_fd(file, 2);
				if (line > 0)
				{
					ft_putstr_fd(":", 2);
					ft_putnbr_fd(line, 2);
				}
				ft_putstr_fd("\n" RESET, 2);
			}
			exit(1);
		}
		else
			ft_putstr_fd(GREEN "End of the game\n" RESET, 1);
	}
	exit(0);
}

int	india(t_game *game)
{
	free_exit(game, 0, NULL, "EOG");
	return (0);
}
