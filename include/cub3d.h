/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:09:44 by kasingh           #+#    #+#             */
/*   Updated: 2024/08/21 18:47:59 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/include/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define BLACK "\1\e[1;90m\2"
# define RED "\1\e[1;91m\2"
# define GREEN "\1\e[1;92m\2"
# define YELLOW "\1\e[1;93m\2"
# define BLUE "\1\033[38;5;117m\2"
# define PURPLE "\1\033[38;5;164m\2"
# define CYAN "\1\033[38;5;51m\2"
# define WHITE "\1\e[1;97m\2"
# define RESET "\1\e[0m\2"
# define BOLD "\1\e[1m\2"
# define GREY "\033[90m\2"
# define LILA "\1\033[38;5;147m\2"
# define O_BLUE "\1\033[38;5;24m\2"
# define TEAL "\1\033[38;5;44m\2"
# define LIGHT_GREEN "\1\033[38;5;120m\2"

# define E_MALLOC "Malloc failure!"
# define E_DIR "Wrong argument: Directory"
# define E_SPACE "Invalid whitespace characters"

typedef struct s_game
{
	char	**map;
	int		pos_x;
	int		pos_y;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*ceiling;
	char	*floor;
}			t_game;

t_game		*parsing(char *file);
void		read_file(char *file, t_game *game);
void		free_exit(t_game *game, int line, char *file, char *error);
t_game		*init_game(void);
char		*get_texture_path(char *line, t_game *game);
void		print_struct(t_game *game);
void		print_tabsquare(char **tab);

#endif