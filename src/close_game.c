/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:43:00 by zeatilga          #+#    #+#             */
/*   Updated: 2023/12/06 17:05:29 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../libft/libft.h"
#include "../minilibx/mlx.h"
#include <stdlib.h>

void	put_msg_exit(char *msg)
{
	ft_printf("%s", msg);
	exit(0);
}

void	error_free_map(t_game *game, char *msg)
{
	int	y;

	y = -1;
	while (++y < game->map.map_height)
		free(game->map.graph_map[y]);
	free(game->map.graph_map);
	put_msg_exit(msg);
}

void	success_exit_game(t_game *game, char *msg)
{
	int	y;

	y = -1;
	while (++y < game->map.map_height)
		free(game->map.graph_map[y]);
	free(game->map.graph_map);
	mlx_destroy_image(game->mlx.mlx_ptr, game->img.space);
	mlx_destroy_image(game->mlx.mlx_ptr, game->img.collectable);
	mlx_destroy_image(game->mlx.mlx_ptr, game->img.exit);
	mlx_destroy_image(game->mlx.mlx_ptr, game->img.player);
	mlx_destroy_image(game->mlx.mlx_ptr, game->img.wall);
	mlx_destroy_window(game->mlx.mlx_ptr, game->mlx.window);
	put_msg_exit(msg);
}
