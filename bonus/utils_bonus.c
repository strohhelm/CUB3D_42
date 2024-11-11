/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/15 14:30:39 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/12 00:02:58 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

int	arr_len(char **arr)
{
	int	i;

	i = 0;
	if (arr)
	{
		while (arr[i])
			i++;
	}
	return (i);
}

int	mv_arr(char **src, char **dest)
{
	int	i;

	i = 0;
	if (src && dest)
	{
		while (src[i])
		{
			dest[i] = src[i];
			i++;
		}
		dest[i] = NULL;
	}
	return (i);
}

t_game	*game_pointer(int i, void *game)
{
	static t_game	*def_not_global;

	if (i == 1 && game)
	{
		def_not_global = (t_game *)game;
		return (NULL);
	}
	else
		return (def_not_global);
}

void free_sprites(t_game *game)
{
	int i;

	i = -1;
	mlx_delete_image(game->mlx, game->emg);
	mlx_delete_image(game->mlx, game->cmg);
	mlx_delete_image(game->mlx, game->player.gun_img);
	mlx_delete_image(game->mlx, game->hp);
	mlx_delete_image(game->mlx, game->w_img);
	mlx_delete_image(game->mlx, game->l_img);
	while(++i < 6)
		mlx_delete_texture(game->e->tex[ALIVE][i]);
	i = -1;
	while (++i < 8)
		mlx_delete_texture(game->e->tex[DYING][i]);
	i = -1;
	while (++i < 4)
		mlx_delete_texture(game->player.gun[i]);
}

void	free_indiv(t_tex *t)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (t->arr[i])
			mlx_delete_texture(&t->side[i]);
	}
}

void	free_textures(t_game *game)
{
	long	i;

	i = 0;
	while (i < TEX_COUNT)
	{
		mlx_delete_texture(game->map.textures[i]);
		game->map.textures[i] = NULL;
		i++;
	}
	i = game->map.map_h * game->map.map_w;
	while (--i > 0)
	{
		if (game->map.indiv[i])
		{
			free_indiv(game->map.indiv[i]);
			free(game->map.indiv[i]);
		}
		i--;
	}
	// free(game->map.indiv);

}

void	free_door(void *d)
{
	t_door *p;
	p = (t_door *)d;
	mlx_delete_texture(p->texture);
	free(p);
}


void	free_game_end(t_game *game)
{
	free_int_array(game->map.map, game->map.map_h);
	free_string_array(game->map.str_map);
	mlx_delete_image(game->mlx, game->img);
	mlx_set_cursor_mode(game->mlx, MLX_MOUSE_NORMAL);
	mlx_terminate(game->mlx);
	free_sprites(game);
	free_textures(game);
	ft_lstclear(&game->map.dstuff.doors, &free_door);
}

void	free_int_array(int **arr, int h)
{

	if (arr)
	{
		while (--h >= 0)
		{
			free(arr[h]);
		}
		free(arr);
	}
}
void	free_string_array(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i])
			free(str[i]);
		i++;
	}
	free(str);
}

int	left_or_right(t_point a, t_point b, t_point p)
{
	double	cross_product;
	t_point	b_vector;
	t_point	p_vector;

	b_vector = vector(a, b);
	p_vector = vector(a, p);
	cross_product = b_vector.x * p_vector.y - b_vector.y * p_vector.x;
	if (cross_product < 0 )
		return (LEFT);
	else
		return (RIGHT);
}
