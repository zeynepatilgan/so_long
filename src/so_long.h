/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zeatilga <zeatilga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:40:36 by zeatilga          #+#    #+#             */
/*   Updated: 2023/12/06 15:57:16 by zeatilga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define ON_KEYDOWN 2
# define ON_DESTROY 17
# define IMG_SIZE 64
# define W 13
# define A 0
# define S 1
# define D 2
# define ESC 53

typedef struct s_img
{
	void			*player;
	void			*exit;
	void			*collectable;
	void			*space;
	void			*wall;

	int				height;
	int				width;

}					t_img;
typedef struct s_paths
{
	char			*map_path;
	char			*player_path;
	char			*wall_path;
	char			*exit_path;
	char			*collectbl_path;
	char			*space_path;

}					t_paths;

typedef struct s_map
{
	char			**graph_map;

	int				**tmp_map;

	int				map_width;
	int				map_height;

	int				player_x;
	int				player_y;
	int				exit_x;
	int				exit_y;

	int				cnt_player;
	int				cnt_exit;
	int				cnt_collectbl;
	int				cnt_unallowed_char;
	int				cnt_p_plus_c;
	int				collected_cnt;
	int				step_cnt;

}					t_map;

typedef struct s_mlx
{
	void			*window;
	void			*mlx_ptr;

}					t_mlx;

typedef struct s_game
{
	t_paths	paths;
	t_mlx	mlx;
	t_img	img;
	t_map	map;

}					t_game;

void				success_exit_game(t_game *game, char *msg);
void				error_free_map(t_game *game, char *msg);
void				put_msg_exit(char *msg);
void				file_checker(int ac, char **av);
void				map_checker(char **av, t_game *game);
void				img_checher_0(t_game *game);
void				img_checker_1(t_game *game);
void				map_requirements(t_game *game);
void				cnt_checker(t_game *game);
void				wall_checker(t_game *game);
void				create_tmp_map(t_game *game);
void				free_map(int **map, int y);
void				minilibx__create(t_game *game);
void				start_mlx(t_game *game);
void				move_and_put_image(int key_code, t_game *game, int i);
int					ft_key_hook(int key_code, t_game *game);
int					ft_mouse_hook(t_game *game);
void				ft_key_comb(t_game *game);
int					move_and_check(int y, int x, t_game *game);

#endif
