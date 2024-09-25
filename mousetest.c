/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mousetest.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pscala <pscala@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 19:52:23 by pscala            #+#    #+#             */
/*   Updated: 2024/09/25 20:22:45 by pscala           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx/mlx.h"
#include <stdio.h>

typedef struct s_game {
    void *mlx_ptr;
    void *mlx_win;
} t_game;

int mouse_move(int x, int y, t_game *game) {
    printf("Mouse moved to: %d, %d\n", x, y);
    return (0);
}

int main(void) {
    t_game game;

    game.mlx_ptr = mlx_init();
    game.mlx_win = mlx_new_window(game.mlx_ptr, 800, 600, "Mouse Move Test");
    mlx_hook(game.mlx_win, 6, 0, mouse_move, &game); 

    mlx_loop(game.mlx_ptr);
    return (0);
}
