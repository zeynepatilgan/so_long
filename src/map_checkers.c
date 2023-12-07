/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checkers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:42:23 by zeatilga          #+#    #+#             */
/*   Updated: 2023/12/07 17:50:32 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "so_long.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	rectangular_checker(t_game *game, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
		put_msg_exit("ERROR: get_next_line is faulty!\n");
	game->map.map_width = (int)ft_strlen(line) - 1;
	while (1)
	{
		free(line);
		game->map.map_height++;
		line = get_next_line(fd);
		if (!line)
			break ;
		if (game->map.map_width != (int)ft_strlen(line) - 1)
		{
			free(line);
			put_msg_exit("ERROR: The map must be rectangular !\n");
		}
	}
	if (line)
		free(line);
	close(fd);
}

void	create_new_map(t_game *game, int x, int y)
{
	int		fd;
	char	*line;

	fd = open(game->paths.map_path, O_RDONLY);
	game->map.graph_map = (char **)malloc(sizeof(char *)
			* game->map.map_height);
	if (!game->map.graph_map)
		return (put_msg_exit("ERROR: Failed to create graph_map\n"));
	while (++y < game->map.map_height)
	{
		x = -1;
		line = get_next_line(fd);
		game->map.graph_map[y] = (char *)malloc(sizeof(char)
				* game->map.map_width);
		if (!game->map.graph_map[y])
			return (error_free_map(game,
					"ERROR: Failed to create graph_map!\n"));
		if (!line)
			break ;
		while (++x < game->map.map_width)
			game->map.graph_map[y][x] = line[x];
		game->map.graph_map[y][x] = '\0';
		free(line);
	}
}

void	data_start_must_be_zero(t_game *game)
{
	game->map.cnt_collectbl = 0;
	game->map.cnt_exit = 0;
	game->map.cnt_player = 0;
	game->map.cnt_unallowed_char = 0;
	game->map.cnt_p_plus_c = 0;
	game->map.collected_cnt = 0;
	game->map.step_cnt = 0;
}

void	scan_the_map(t_game *game, int x, int y)
{
	while (++y < game->map.map_height)
	{
		x = -1;
		while (++x < game->map.map_width)
		{
			if (game->map.graph_map[y][x] == 'C')
				game->map.cnt_collectbl++;
			else if (game->map.graph_map[y][x] == 'P')
			{
				game->map.cnt_player++;
				game->map.player_x = x;
				game->map.player_y = y;
			}
			else if (game->map.graph_map[y][x] == 'E')
			{
				game->map.cnt_exit++;
				game->map.exit_x = x;
				game->map.exit_y = y;
			}
			else if (game->map.graph_map[y][x] != '0' &&
				game->map.graph_map[y][x] != '1')
				game->map.cnt_unallowed_char++;
		}
	}
}

void	map_requirements(t_game *game)
{
	int	x;
	int	y;
	int	fd;

	x = -1;
	y = -1;
	fd = open(game->paths.map_path, O_RDONLY);
	if (fd <= 0)
	{
		close(fd);
		put_msg_exit("ERROR: Map file could not be opened!\n");
	}
	game->map.map_height = 0;
	rectangular_checker(game, fd);
	create_new_map(game, x, y);
	data_start_must_be_zero(game);
	scan_the_map(game, x, y);
	cnt_checker(game);
	wall_checker(game);
	create_tmp_map(game);
}
