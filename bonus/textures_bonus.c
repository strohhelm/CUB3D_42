/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:05:31 by pstrohal          #+#    #+#             */
/*   Updated: 2024/11/11 22:17:32 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	make_indi_tex(t_game *game, t_tex **t, t_texture *tex)
{
	int	x;
	int	y;
	int	arr[4];

	*t = (t_tex *)malloc(sizeof(t_tex));
	err_check(*t, "malloc fucked up!");
	y = tex->index / game->map.map_w;
	x = tex->index - y * game->map.map_w;
	fill_arr(&game->map, x, y, &arr);
	fill_text(*t, game->map.textures, &arr);
}

void	init_texhelp(t_game *game, t_texture *tex, int dir, t_texhelp *t)
{
	t->current = &game->map.indiv[tex->index]->side[dir];
	t->new = game->map.textures[BULLET];
	t->start_index = (tex->arr_pos - (long)t->new->height / 2 * 4
			* (long)t->current->width - (long)t->new->width / 2 * 4);
	t->max_index = (long)(t->current->width * t->current->height * 4);
}
void	draw_on_tex(t_game *game, t_texture *tex, int dir)
{
	uint		x;
	uint		y;
	t_texhelp	t;

	if (!game->map.indiv[tex->index])
		make_indi_tex(game, &game->map.indiv[tex->index], tex);
	init_texhelp(game, tex, dir, &t);
	y = 0;
	while (++y < t.new->height)
	{
		x = -1;
		while (++x < t.new->width)
		{
			t.arr_index = t.start_index +( y * t.current->width + x) * 4;
			t.new_tex_pos = &t.new->pixels[y * t.new->width * 4 + x * 4];
			if (t.arr_index > 0 && t.arr_index < t.max_index)
			{
				if (*((uint32_t *)t.new_tex_pos))
					*((uint32_t *)(&t.current->pixels[t.arr_index]))
					= *((uint32_t *)t.new_tex_pos);
			}
		}
	}
}

void	fill_text(t_tex *t, mlx_texture_t **tex, int (*arr)[4])
{
	int	i;
	size_t	nb;

	i = 0;
	while (i < CEILING)
	{
		if ((*arr)[i])
		{
			t->side[i].width = tex[i]->width;
			t->side[i].height = tex[i]->height;
			t->side[i].bytes_per_pixel = tex[i]->bytes_per_pixel;
			nb = sizeof(uint8_t) * t->side[i].width * t->side[i].height * 4;
			t->side[i].pixels = (uint8_t *)malloc(nb);
			if (!t->side[i].pixels)
				error_print("duuuude, get rekt malloc fucked up!");
			ft_memmove(t->side[i].pixels, tex[i]->pixels, nb);
		}
		else
			t->side[i].pixels = NULL;
		ft_memmove(&t->arr, arr, sizeof(int) * 4);
		i++;
	}
}

void	fill_arr(t_map *map, int x, int y, int (*arr)[4])
{
	(*arr)[NORTH] = 0;
	(*arr)[SOUTH] = 0;
	(*arr)[EAST] = 0;
	(*arr)[WEST] = 0;
	if (y == 0)
		(*arr)[NORTH] = 1;
	else if (y == map->map_h - 1)
		(*arr)[SOUTH] = 1;
	else if (x == 0)
		(*arr)[WEST] = 1;
	else if (x == map->map_w - 1)
		(*arr)[EAST] = 1;
	else
	{
		if (map->map[y - 1][x] != 1)
			(*arr)[SOUTH] = 1;
		if (map->map[y + 1][x] != 1)
			(*arr)[NORTH] = 1;
		if (map->map[y][x - 1] != 1)
			(*arr)[EAST] = 1;
		if (map->map[y][x + 1] != 1)
			(*arr)[WEST] = 1;
	}
	return ;

}


t_tex **allocate_textures(t_map *map)
{
	t_tex	**text_arr;
	int		i;
	int		x;
	int		y;
	
	text_arr = (t_tex **)malloc(sizeof(t_tex *) * map->map_h * map->map_w);
	err_check(text_arr, "bruuuh look at your shitty pc, cant even malloc!");
	i = 0;
	y = -1;
	while (++y < map->map_h)
	{
		x = -1;
		while (++x < map->map_w)
			text_arr[i++] = NULL;
	}
	return (text_arr);
}
