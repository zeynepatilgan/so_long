/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_create.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:42:12 by zeatilga          #+#    #+#             */
/*   Updated: 2023/12/06 19:26:54 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minilibx/mlx.h"
#include "so_long.h"
#include <unistd.h>

static void	start_mlx_2(t_game *game)
{
	if (!game->img.exit)
	{
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.player);
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.collectable);
		error_free_map(game, "ERROR: Image could not be created!\n");
	}
	game->img.wall = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			game->paths.wall_path, &game->img.width, &game->img.height);
	if (!game->img.wall)
	{
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.exit);
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.player);
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.collectable);
		error_free_map(game, "ERROR: Image could not be created!\n");
	}
	game->img.space = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			game->paths.space_path, &game->img.width, &game->img.height);
	if (!game->img.space)
	{
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.wall);
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.exit);
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.player);
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.collectable);
		error_free_map(game, "ERROR: Image could not be created!\n");
	}
}

void	start_mlx(t_game *game)
{
	game->mlx.mlx_ptr = mlx_init();
	if (game->mlx.mlx_ptr == NULL)
		return (error_free_map(game,
				"ERROR: Minilibx could not be created!\n"));
	game->mlx.window = mlx_new_window(game->mlx.mlx_ptr, game->map.map_width
			* IMG_SIZE, game->map.map_height * IMG_SIZE, " #SO_LONG# ");
	if (game->mlx.window == NULL)
		return (error_free_map(game, "ERROR: Window could not be created!\n"));
	game->img.collectable = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			game->paths.collectbl_path, &game->img.height, &game->img.width);
	if (!game->img.collectable)
		error_free_map(game, "ERROR: Image could not be created!\n");
	game->img.player = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			game->paths.player_path, &game->img.width, &game->img.height);
	if (!game->img.player)
	{
		mlx_destroy_image(game->mlx.mlx_ptr, game->img.collectable);
		error_free_map(game, "ERROR: Image could not be created!\n");
	}
	game->img.exit = mlx_xpm_file_to_image(game->mlx.mlx_ptr,
			game->paths.exit_path, &game->img.width, &game->img.height);
	start_mlx_2(game);
}

static void	put_img_to_map_mlx_1(t_game *game, int x, int y, int p)
{
	if (game->map.graph_map[y][x] == 'C')
		p = mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.window,
				game->img.collectable, x * IMG_SIZE, y * IMG_SIZE);
	else if (game->map.graph_map[y][x] == 'E')
		p = mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.window,
				game->img.exit, x * IMG_SIZE, y * IMG_SIZE);
	else if (game->map.graph_map[y][x] == 'P')
		p = mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.window,
				game->img.player, x * IMG_SIZE, y * IMG_SIZE);
	else if (game->map.graph_map[y][x] == '1')
		p = mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.window,
				game->img.wall, x * IMG_SIZE, y * IMG_SIZE);
	if (p == -1)
		success_exit_game(game, "ERROR: image could not be printed!\n");
}

void	put_img_to_map_mlx_0(t_game *game)
{
	int	x;
	int	y;
	int	p;

	p = 0;
	y = 0;
	while (y < game->map.map_height)
	{
		x = 0;
		while (x < game->map.map_width)
		{
			p = mlx_put_image_to_window(game->mlx.mlx_ptr, game->mlx.window,
					game->img.space, x * IMG_SIZE, y * IMG_SIZE);
			if (p == -1)
				error_free_map(game, "ERROR: image could not be printed!\n");
			put_img_to_map_mlx_1(game, x, y, p);
			x++;
		}
		y++;
	}
}

void	minilibx__create(t_game *game)
{
	start_mlx(game);
	put_img_to_map_mlx_0(game);
}
