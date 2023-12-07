/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:42:45 by zeatilga          #+#    #+#             */
/*   Updated: 2023/12/02 17:11:41 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../minilibx/mlx.h"

int	ft_key_hook(int key_code, t_game *game)
{
	if (key_code == ESC)
		success_exit_game(game, "Exit Successfully!!!\n");
	else if (key_code == A || key_code == S)
		move_and_put_image(key_code, game, -1);
	else if (key_code == W || key_code == D)
		move_and_put_image(key_code, game, 1);
	return (0);
}

int	ft_mouse_hook(t_game *game)
{
	success_exit_game(game, "Exit Successfully!!!\n");
	return (0);
}

void	ft_key_comb(t_game *game)
{
	mlx_hook(game->mlx.window, ON_KEYDOWN, 0, ft_key_hook, game);
	mlx_hook(game->mlx.window, ON_DESTROY, 0, ft_mouse_hook, game);
}
