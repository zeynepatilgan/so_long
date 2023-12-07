/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checkers_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:42:32 by zeatilga          #+#    #+#             */
/*   Updated: 2023/12/06 20:30:27 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "so_long.h"
#include <fcntl.h>
#include <stdlib.h>

void	wall_checker(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.map_height)
	{
		x = 0;
		if (y == 0 || y == game->map.map_height - 1)
		{
			while (x < game->map.map_width)
				if (game->map.graph_map[y][x++] != '1')
					error_free_map(game,
						"ERROR: The map must be surrounded by walls!\n");
		}
		if (game->map.graph_map[y][0] != '1'
			|| game->map.graph_map[y][game->map.map_width - 1] != '1')
			error_free_map(game,
				"ERROR: The map must be surrounded by walls!\n");
		y++;
	}
}

static void	scan_tmp_map(t_game *game, int x, int y)
{
	if (game->map.graph_map[y][x] == 'P' || game->map.graph_map[y][x] == 'C')
		game->map.cnt_p_plus_c++;
	if (game->map.graph_map[y][x + 1] != '1' && game->map.tmp_map[y][x + 1] < 1)
	{
		game->map.tmp_map[y][x + 1] = game->map.tmp_map[y][x] + 1;
		scan_tmp_map(game, x + 1, y);
	}
	if (game->map.graph_map[y + 1][x] != '1' && game->map.tmp_map[y + 1][x] < 1)
	{
		game->map.tmp_map[y + 1][x] = game->map.tmp_map[y][x] + 1;
		scan_tmp_map(game, x, y + 1);
	}
	if (game->map.graph_map[y - 1][x] != '1' && game->map.tmp_map[y - 1][x] < 1)
	{
		game->map.tmp_map[y - 1][x] = game->map.tmp_map[y][x] + 1;
		scan_tmp_map(game, x, y - 1);
	}
	if (game->map.graph_map[y][x - 1] != '1' && game->map.tmp_map[y][x - 1] < 1)
	{
		game->map.tmp_map[y][x - 1] = game->map.tmp_map[y][x] + 1;
		scan_tmp_map(game, x - 1, y);
	}
}

void	free_map(int **map, int y)
{
	while (y--)
		free(map[y]);
	free(map);
}

void	create_tmp_map(t_game *game)
{
	int	y;

	y = 0;
	game->map.tmp_map = (int **)malloc(sizeof(int *) * game->map.map_width);
	if (!game->map.tmp_map)
		return (put_msg_exit("ERROR: failed to create tmp_map!\n"));
	while (y < game->map.map_height)
	{
		game->map.tmp_map[y] = ft_calloc(game->map.map_width, sizeof(int));
		if (!game->map.tmp_map[y])
		{
			free_map (game->map.tmp_map, game->map.map_height);
			error_free_map (game, "ERROR: Failed to create tmp_map!\n");
		}
		y++;
	}
	scan_tmp_map(game, game->map.exit_x, game->map.exit_y);
	if (game->map.cnt_player
		+ game->map.cnt_collectbl != game->map.cnt_p_plus_c)
	{
		free_map(game->map.tmp_map, game->map.map_height);
		error_free_map(game,
			"ERROR: Player could not access all collectibles and exit!\n");
	}
	free_map(game->map.tmp_map, game->map.map_height);
}

void	cnt_checker(t_game *game)
{
	if (game->map.cnt_collectbl < 1)
		error_free_map(game, "ERROR: Map must have at least 1 collectible!\n");
	if (game->map.cnt_exit != 1)
		error_free_map(game, "ERROR: Map must have 1 exit!\n");
	if (game->map.cnt_player != 1)
		error_free_map(game, "ERROR: Map must have 1 player!\n");
	if (game->map.cnt_unallowed_char > 0)
		error_free_map(game,
			"ERROR: The map must contain only {0,1,C,E,P} characters!\n");
}
