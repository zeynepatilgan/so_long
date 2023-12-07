/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_checkers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:42:03 by zeatilga          #+#    #+#             */
/*   Updated: 2023/12/06 15:57:36 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/libft.h"
#include "so_long.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	file_checker(int ac, char **av)
{
	int	i;

	if (ac != 2)
		put_msg_exit("ERROR: Argument count error! \n");
	i = 0;
	while (av[1][i])
		i++;
	if (av[1][i - 1] != 'r' && av[1][i - 2] != 'e' && av[1][i - 3] != 'b'
		&& av[1][i - 4] != '.')
		put_msg_exit("ERROR: File extension must be .ber ! \n");
}

void	map_checker(char **av, t_game *game)
{
	int		fd;

	game->paths.map_path = av[1];
	fd = open(game->paths.map_path, O_RDONLY);
	if (fd <= 0)
	{
		put_msg_exit("ERROR: Wrong map name!");
	}
	close(fd);
}

void	img_checher_0(t_game *game)
{
	int	fd;

	fd = open("./sprites/exit.xpm", O_RDONLY);
	if (fd <= 0)
		put_msg_exit("ERROR: Wrong exit path!");
	close(fd);
	fd = open("./sprites/collectable.xpm", O_RDONLY);
	if (fd <= 0)
		put_msg_exit("ERROR: Wrong collectable path!");
	close(fd);
	fd = open("./sprites/player.xpm", O_RDONLY);
	if (fd <= 0)
		put_msg_exit("ERROR: Wrong player path!");
	close(fd);
	game->paths.collectbl_path = "./sprites/collectable.xpm";
	game->paths.exit_path = "./sprites/exit.xpm";
	game->paths.player_path = "./sprites/player.xpm";
}

void	img_checker_1(t_game *game)
{
	int	fd;

	fd = open("./sprites/space.xpm", O_RDONLY);
	if (fd <= 0)
		put_msg_exit("ERROR: Wrong space path!");
	close(fd);
	fd = open("./sprites/wall.xpm", O_RDONLY);
	if (fd <= 0)
		put_msg_exit("ERROR: Wrong wall path!");
	close(fd);
	game->paths.space_path = "./sprites/space.xpm";
	game->paths.wall_path = "./sprites/wall.xpm";
}
