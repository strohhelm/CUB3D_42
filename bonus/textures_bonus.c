/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pstrohal <pstrohal@42.heilbronn.de>        #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-10 12:05:31 by pstrohal          #+#    #+#             */
/*   Updated: 2024-10-10 12:05:31 by pstrohal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub_bonus.h"

void	fill_text(t_tex *t, mlx_texture_t **textures)
{
	int	i;

	i = 0;
	while (i < CEILING)
	{
		ft_memmove(&t->side[i], &textures[i], sizeof(mlx_texture_t));
		i++;
	}
}

t_tex **allocate_textures(int height, int width, mlx_texture_t **tex)
{
	t_tex	**text_arr;
	int				i;
	int				x;

	text_arr = (t_tex **)malloc(sizerof(t_tex *) * height * width);
	if (!text_arr)
		error_print("bruuuh look at your shitty pc, cant even malloc!");
	y = -1;
	while (i < with * height)
	{
		text_arr[i] = (t_tex *)malloc(sizeof(t_tex));
		if (!text_arr[i])
			error_print("bruuuh look at your shitty pc, cant even malloc!");
		fill_text(text_arr[i], tex);
	}
	return (text_arr);
}
