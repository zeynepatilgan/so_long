/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:42:39 by zeatilga          #+#    #+#             */
/*   Updated: 2023/12/02 14:42:42 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "../minilibx/mlx.h"

int	main(int ac, char **av)
{
	t_game	game;

	file_checker(ac, av);
	map_checker(av, &game);
	img_checher_0(&game);
	img_checker_1(&game);
	map_requirements(&game);
	minilibx__create(&game);
	ft_key_comb(&game);
	mlx_loop(game.mlx.mlx_ptr);
}
